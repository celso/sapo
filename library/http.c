#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
# include <unistd.h>
/* # include <sys/select.h> */
# include <sys/time.h>

#include "protos.h"
#include "http.h"
#define FALSE 0
#define TRUE  1

#ifndef errno
extern int errno;
#endif

/* Variables shared by bindport and acceptport: */
static int msock = -1;
static struct sockaddr *addr;

    struct hostent *
ngethostbyname (const char *name)
{
    struct hostent *hp;
    unsigned long addr;

    addr = (unsigned long)inet_addr (name);
    if ((int)addr != -1)
        hp = gethostbyaddr ((char *)&addr, sizeof (addr), AF_INET);
    else
        hp = gethostbyname (name);
    return hp;
}

/* Wait for file descriptor FD to be readable, MAXTIME being the
   timeout in seconds.  If WRITEP is non-zero, checks for FD being
   writable instead.

   Returns 1 if FD is accessible, 0 for timeout and -1 for error in
   select().  */
    static int
select_fd (int fd, int maxtime, int writep)
{
    fd_set fds, exceptfds;
    struct timeval timeout;

    FD_ZERO (&fds);
    FD_SET (fd, &fds);
    FD_ZERO (&exceptfds);
    FD_SET (fd, &exceptfds);
    timeout.tv_sec = maxtime;
    timeout.tv_usec = 0;
    /* HPUX reportedly warns here.  What is the correct incantation?  */
    return select (fd + 1, writep ? NULL : &fds, writep ? &fds : NULL,
            &exceptfds, &timeout);
}

uerr_t make_connection (int *sock, char *hostname, unsigned short port)
{
    struct hostent *hptr;
    struct sockaddr_in sock_name;

    if (!(hptr = ngethostbyname (hostname)))
        return HOSTERR;
    /* Copy the address of the host to socket description.  */
    memcpy (&sock_name.sin_addr, hptr->h_addr, hptr->h_length);
    /* Set port and protocol */
    sock_name.sin_family = AF_INET;
    sock_name.sin_port = htons (port);
    /* Make an internet socket, stream type.  */
    if ((*sock = socket (AF_INET, SOCK_STREAM, 0)) == -1)
        return CONSOCKERR;
    /* Connect the socket to the remote host.  */
    if (connect (*sock, (struct sockaddr *) &sock_name, sizeof (sock_name)))
    {
        if (errno == ECONNREFUSED)
            return CONREFUSED;
        else
            return CONERROR;
    }
    return NOCONERROR;
}

    int
iread (int fd, char *buf, int len)
{
    int res;

    do
    {
        do
        {
            res = select_fd (fd, CON_TIMEOUT, 0);
        } while (res == -1 && errno == EINTR);
        if (res <= 0)
        {
            /* Set errno to ETIMEDOUT on timeout.  */
            if (res == 0)
                /* #### Potentially evil!  */
                errno = ETIMEDOUT;
            return -1;
        }
        res = READ (fd, buf, len);
    } while (res == -1 && errno == EINTR);

    return res;
}

/* Bind the local port PORT.  This does all the necessary work, which
   is creating a socket, setting SO_REUSEADDR option on it, then
   calling bind() and listen().  If *PORT is 0, a random port is
   chosen by the system, and its value is stored to *PORT.  The
   internal variable MPORT is set to the value of the ensuing master
   socket.  Call acceptport() to block for and accept a connection.  */
    uerr_t
bindport (unsigned short *port)
{
    int optval = 1;
    static struct sockaddr_in srv;

    msock = -1;
    addr = (struct sockaddr *) &srv;
    if ((msock = socket (AF_INET, SOCK_STREAM, 0)) < 0)
        return CONSOCKERR;
    if (setsockopt (msock, SOL_SOCKET, SO_REUSEADDR,
                (char *)&optval, sizeof (optval)) < 0)
        return CONSOCKERR;
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = htonl (INADDR_ANY);
    srv.sin_port = htons (*port);
    if (bind (msock, addr, sizeof (struct sockaddr_in)) < 0)
    {
        CLOSE (msock);
        msock = -1;
        return BINDERR;
    }
    if (!*port)
    {
        size_t addrlen = sizeof (struct sockaddr_in);
        if (getsockname (msock, addr, (int *)&addrlen) < 0)
        {
            CLOSE (msock);
            msock = -1;
            return CONPORTERR;
        }
        *port = ntohs (srv.sin_port);
    }
    if (listen (msock, 1) < 0)
    {
        CLOSE (msock);
        msock = -1;
        return LISTENERR;
    }
    return BINDOK;
}

/* Call accept() on MSOCK and store the result to *SOCK.  This assumes
   that bindport() has been used to initialize MSOCK to a correct
   value.  It blocks the caller until a connection is established.  If
   no connection is established for OPT.TIMEOUT seconds, the function
   exits with an error status.  */
    uerr_t
acceptport (int *sock)
{
    int addrlen = sizeof (struct sockaddr_in);

    if (select_fd (msock, CON_TIMEOUT, 0) <= 0)
        return ACCEPTERR;
    if ((*sock = accept (msock, addr, &addrlen)) < 0)
        return ACCEPTERR;
    return ACCEPTOK;
}

/* Close SOCK, as well as the most recently remembered MSOCK, created
   via bindport().  If SOCK is -1, close MSOCK only.  */
    void
closeport (int sock)
{
    /*shutdown (sock, 2);*/
    if (sock != -1)
        CLOSE (sock);
    if (msock != -1)
        CLOSE (msock);
    msock = -1;
}

/* Return the local IP address associated with the connection on FD.
   It is returned in a static buffer.  */
    unsigned char *
conaddr (int fd)
{
    static unsigned char res[4];
    struct sockaddr_in mysrv;
    struct sockaddr *myaddr;
    size_t addrlen = sizeof (mysrv);

    myaddr = (struct sockaddr *) (&mysrv);
    if (getsockname (fd, myaddr, (int *)&addrlen) < 0)
        return NULL;
    memcpy (res, &mysrv.sin_addr, 4);
    return res;
}

/* Write LEN bytes from BUF to FD.  This is similar to iread(), but
   doesn't bother with select().  Unlike iread(), it makes sure that
   all of BUF is actually written to FD, so callers needn't bother
   with checking that the return value equals to LEN.  Instead, you
   should simply check for -1.  */
    int
iwrite (int fd, char *buf, int len)
{
    int res = 0;

    /* `write' may write less than LEN bytes, thus the outward loop
       keeps trying it until all was written, or an error occurred.  The
       inner loop is reserved for the usual EINTR f*kage, and the
       innermost loop deals with the same during select().  */
    while (len > 0)
    {
        do
        {
            do
            {
                res = select_fd (fd, CON_TIMEOUT, 1);
            }
            while (res == -1 && errno == EINTR);
            if (res <= 0)
            {
                /* Set errno to ETIMEDOUT on timeout.  */
                if (res == 0)
                    /* #### Potentially evil!  */
                    errno = ETIMEDOUT;
                return -1;
            }
            res = WRITE (fd, buf, len);
        }
        while (res == -1 && errno == EINTR);
        if (res <= 0)
            break;
        buf += res;
        len -= res;
    }
    return res;
}

make_request(char *request,char *command)
{
    sprintf (request, "\
            %s HTTP/1.0\r\n\
            User-Agent: %s\r\n\
            Host: %s:%d\r\n\
            Accept: %s\r\n\
            %s%s%s%s%s%s\r\n",
            command, "SAPO Crawler 1.0b3", "www.sapo.pt", 0, HTTP_ACCEPT,
            "", "", "", "", "Pragma: no-cache\r\n", "");
}

int get_status(char *host,int port,char *command)
{
    uerr_t err;
    int sock,num_written,rn;
    char request[2048];
    char rbuf[100];
    char *ptr;

    err = make_connection (&sock, host, port);
    switch(err)
    {
        case CONREFUSED:
            CLOSE (sock);
            errno=CONREFUSED;
            return(0);
        case NOCONERROR:
            /* Everything is fine!  */
            break;
        case HOSTERR:
            errno=HOSTERR;
            return(0);
        default:
            CLOSE (sock);
            return(0);
            break;
    }

    make_request(request,command);
    num_written = iwrite (sock, request, strlen (request));
    if (num_written < 0 ) {
        CLOSE(sock);
        return(0);
    }
    /* Só quero o header */
    rn=iread(sock,rbuf,sizeof(rbuf));
    CLOSE (sock);
    if(rn != -1) {
        ptr=strchr(rbuf,' ');
        if(ptr) {
            ptr++;
            return(atoi(ptr));
        } else return(0);
    }
    else
    {
        return(0);
    }
}


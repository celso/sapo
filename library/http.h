#define HTTP_ACCEPT "*/*"

#define uerr_t int

#define HOSTERR		1<<0L
#define CONSOCKERR	1<<1L
#define CONREFUSED	1<<3L
#define CONERROR	1<<4L
#define NOCONERROR	1<<5L
#define BINDERR		1<<6L
#define CONPORTERR	1<<7L
#define LISTENERR	1<<8L
#define BINDOK		1<<9L
#define ACCEPTERR	1<<10L
#define ACCEPTOK	1<<11L

#define READ(fd, buf, cnt) read ((fd), (buf), (cnt))
#define WRITE(fd, buf, cnt) write ((fd), (buf), (cnt))
#define REALCLOSE(x) close (x)

#define CLOSE(x)                                \
    do {                                            \
        REALCLOSE (x);                                \
    } while (0)

#define CON_TIMEOUT	10

/* HTTP/1.0 status codes from RFC1945, provided for reference.  */
/* Successful 2xx.  */
#define HTTP_STATUS_OK                  200
#define HTTP_STATUS_CREATED             201
#define HTTP_STATUS_ACCEPTED            202
#define HTTP_STATUS_NO_CONTENT          204
#define HTTP_STATUS_PARTIAL_CONTENTS    206

/* Redirection 3xx.  */
#define HTTP_STATUS_MULTIPLE_CHOICES    300
#define HTTP_STATUS_MOVED_PERMANENTLY   301
#define HTTP_STATUS_MOVED_TEMPORARILY   302
#define HTTP_STATUS_NOT_MODIFIED        304

/* Client error 4xx.  */
#define HTTP_STATUS_BAD_REQUEST         400
#define HTTP_STATUS_UNAUTHORIZED        401
#define HTTP_STATUS_FORBIDDEN           403
#define HTTP_STATUS_NOT_FOUND           404

/* Server errors 5xx.  */
#define HTTP_STATUS_INTERNAL            500
#define HTTP_STATUS_NOT_IMPLEMENTED     501
#define HTTP_STATUS_BAD_GATEWAY         502
#define HTTP_STATUS_UNAVAILABLE         503


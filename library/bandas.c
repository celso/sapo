/*
 * Program       : bandas.c
 * Author        : Celso Martinho (celso@ua.pt)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <time.h>
#include "logs.h"
#include "protos.h"
#include "queries.h"
#include "bandas.h"
#include "dbwrapper.h"
#include <defines.h>
#define FALSE 0
#define TRUE  1

#undef NULL
#define NULL 0

/*
 * Library includes
 */

#include "../library/args.h"

#define MSQL_DIR 1
#define MSQL_FILE 2

#define BUFSIZE 8096

#define ERROR(c) puts(c)

int showbd(int grid,int flags,int r)
{
    char months[][4]={"Jan\0","Feb\0","Mar\0","Apr\0","May\0","Jun\0","Jul\0","Aug\0","Sep\0","Oct\0","Nov\0","Dec\0"};
    int i;
    char buf[2000];
    char lbuf[9];
    int offset;
    int fd;
    int len;
    int bd;
    int items=0;
    FILE *fp;
    char *ptr,*ptr2;
    time_t t;

    if(grid==0) grid=1;
    sprintf(buf,"%d",grid);

    if(fd=open("/home/sapo/cdbs/bandas.cdb",O_RDONLY)) {
        if(cdb_seek(fd,buf,strlen(buf),&len)) {
            if(len<=sizeof(buf)) {
                len=read(fd,buf,len);
            } else { len=read(fd,buf,sizeof(buf)); }
            buf[len]=0;

            /* Contar numero de items do bitmap */
            ptr=buf;
            while(ptr<(buf+strlen(buf))) {
                sprintf(lbuf,"%.8s",ptr);
                lbuf[9]=0;
                if(atoi(lbuf)) items++;
                ptr+=8;
            }
            /**/

            time(&t);
            if(!r) srand(t<<getpid());
            offset=1+(int) ((float)(items)*rand()/(RAND_MAX+1.0)); 

            /* Contar numero de items do bitmap */
            ptr=buf;
            items=0;
            while(ptr<(buf+strlen(buf))) {
                sprintf(lbuf,"%.8s",ptr);
                lbuf[9]=0;
                if(atoi(lbuf)) {
                    items++;
                    if(items==offset) {
                        bd=atoi(lbuf);
                        if(bd>1000000) {
                            bd=showbd(atoi(&lbuf[1]),flags,1);
                        }
                    }
                }
                ptr+=8;
            }
            /**/

        }
        close(fd);
    }
    /*
       if(!r) {
       sprintf(buf,LOG_DIR"publicidade/%d.log",bd);
       if(fp=fopen(buf,"a")) {
       struct tm *date;
       time(&t);
       date=localtime(&t);
       fprintf(fp,"%s - - [%.2d/%s/%d:%.2d:%.2d:%.2d +0100] \"GET http://%s%s HTTP/1.1\" 200 1 \"%s\" \"%s\"\n",getenv("REMOTE_ADDR"),date->tm_mday,months[date->tm_mon],date->tm_year+1900,date->tm_hour,date->tm_min,date->tm_sec,getenv("HTTP_HOST"),getenv("REQUEST_URI"),getenv("HTTP_REFERER"),getenv("HTTP_USER_AGENT"));
       fclose(fp);
       }
       }
       */
    return(bd);
}

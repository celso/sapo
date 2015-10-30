#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
# include <unistd.h>
/* # include <sys/select.h> */
# include <sys/time.h>

#include "protos.h"
#include "http.h"
#include "dbwrapper.h"
#include <defines.h>
#define FALSE 0
#define TRUE  1
#define DESTACADO 1
#define SIMPLES   2
#define START     3                       

#ifndef errno
extern int errno;
#endif
/*
 * Faz a mioleira para o lado esquerdo
 */

get_miolo(char *out,char *euri,int maxnews)
{
    char buf[16000];
    char query[1000];
    DBHANDLER dbase;
    DBRESULT *result;
    DBROW row;
    DBRESULT *result2;
    DBROW row2;
    int offset;
    int mm=maxnews;
    int first=1;

    if(CONNECT(&dbase,"sun.sl.pt","root","","noticias")) {
        while(mm>0) {
            QUERY(&dbase,"SELECT id,nome,leftbar,random FROM categorias WHERE leftbar=1 ORDER BY random");
            if(result=STORERESULT(&dbase)) {
                while(row=FETCHROW(result)) {

                    sprintf(buf,"%d",getpid()*rand());
                    offset=(atoi(&buf[strlen(buf)-1])/2)+1;

                    sprintf(query,"SELECT id,titulo FROM miolo WHERE tipo=%s ORDER BY id DESC LIMIT %d,1",row[0],offset);
                    QUERY(&dbase,query);
                    if(result2=STORERESULT(&dbase)) {
                        while((row2=FETCHROW(result2))&&(mm>0)) {

                            if(first) {
                                first=0;
                            }
                            else
                            {
                                strcat(out,"<br>");
                            }

                            sprintf(buf,"<font color=\"#FF0000\">%s</font><br>%s<a href=\"http://noticias.sapo.pt/cgi/news?sec=show&id=%s&back=0&ctg=%s\">»»</a><br>",row[1],row2[1],row2[0],row[0]);
                            strcat(out,buf);

                            mm--;
                        }
                        FREERESULT(result2);
                    }
                }
                FREERESULT(result);
            }
        }
        DBCLOSE(&dbase);
    }

}

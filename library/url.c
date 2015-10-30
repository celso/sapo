/*
 * URL parsing routines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include "protos.h"
#include "http.h"
#include "url.h"
#include "macros.h"
#define FALSE 0
#define TRUE  1

#define UBUFSIZE	2000

void init_url(struct urlinfo *ust)
{
    ust->url=0;
    ust->host=0;
    ust->user=0;
    ust->passwd=0;
    ust->port=80;
    ust->protocol=URL_UNKNOWN;
}

void end_url(struct urlinfo *ust)
{
    if(ust->url) free(ust->url);
    if(ust->host) free(ust->host);
    if(ust->user) free(ust->user);
    if(ust->passwd) free(ust->passwd);
}

int parse_url(struct urlinfo *ust,char *url)
{
    char proto[8];
    char tmpurl[UBUFSIZE];
    char *ptr1,*ptr2;
    int hashost=0;

    memset(tmpurl,0,UBUFSIZE);
    if(strlen(url)<UBUFSIZE) strncpy(tmpurl,url,strlen(url));
    else strncpy(tmpurl,url,UBUFSIZE);

    if(strlen(tmpurl)<8) return(0);

    strncpy(proto,tmpurl,7);
    proto[7]=0;
    lower(proto);
    ust->protocol=URL_UNKNOWN;
    if(!strstr(proto,"://")) return(0);

    if(!strcmp(proto,"http://")) ust->protocol=URL_HTTP;
    if(!strcmp(proto,"ftp://")) ust->protocol=URL_FTP;
    ptr1=strchr(tmpurl,'/');
    if(ptr1)
    {
        ptr1++;
        ptr1++;
        if(ptr2=strchr(ptr1,':')) {
            /* Has alt port */
            *ptr2=0;
            ust->host=malloc(strlen(ptr1));
            strcpy(ust->host,ptr1);
            ptr2++;
            ust->port=atoi(ptr2);
            hashost=1;
        } else ptr2=ptr1;

        if(ptr1=strchr(ptr2,'/')) {
            if(!hashost) {
                ust->host=calloc(1,ptr1-ptr2);
                strncpy(ust->host,ptr2,ptr1-ptr2);
            }
            ust->url=malloc(strlen(ptr1));
            strcpy(ust->url,ptr1);
        }
        else
        {
            if(!hashost) {
                ust->host=malloc(strlen(ptr2));
                strcpy(ust->host,ptr2);
            }
            ust->url=malloc(1);
            strcpy(ust->url,"/");
        }
    }
    else return(1);

}

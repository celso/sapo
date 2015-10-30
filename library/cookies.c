#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "protos.h"
#define FALSE 0
#define TRUE  1

char days[][4]={"Sun\0","Mon\0","Tue\0","Wed\0","Thu\0","Fri\0","Sat\0"};
char months[][4]={"Jan\0","Feb\0","Mar\0","Apr\0","May\0","Jun\0","Jul\0","Aug\0","Sep\0","Oct\0","Nov\0","Dec\0"};

int get_cookie(char *key,char *out)
{
    char format[80];
    char *ptr,*ptr2;

    if(getenv("HTTP_COOKIE")) {
        snprintf(format,sizeof(format),"%s=",key);
        if(ptr=strstr(getenv("HTTP_COOKIE"),format)) {
            ptr+=strlen(format);
            ptr2=strchr(ptr,';');
            if(ptr2) {
                *ptr2=0;
                strcpy(out,ptr);
                return(1);
            }
            else
            {
                strcpy(out,ptr);
            }
        }
        else return(0);
    }
    else return(0);
}

int set_cookie(time_t expire,char *key,char *value,char *domain)
{
    struct tm date;
    time_t crtime;
    char sexpire[80];
    char path[80];

    tocgi(key);
    if(expire) memcpy(&date,localtime(&expire),sizeof(struct tm));
    else {
        time(&crtime); crtime+=60*60*24*90; /* Default is 90 days for expiration */
        memcpy(&date,localtime(&crtime),sizeof(struct tm));
    }
    sprintf(sexpire,"expires=%s, %.2d-%s-19%.2d %.2d:%.2d:%.2d GMT",days[date.tm_wday],date.tm_mday,months[date.tm_mon],date.tm_year,date.tm_hour,date.tm_min,date.tm_sec);
    /*
       if(getenv("SERVER_NAME")) sprintf(domain,"%s",getenv("SERVER_NAME"));
       else domain[0]=0;
       */
    sprintf(path,"/");

    printf("Set-Cookie: %s=%s; %s; path=%s; domain=%s\n",key,value,sexpire,path,domain);
    return(1);
}

int delete_cookie(char *key)
{
    char domain[80];
    char path[80];

    tocgi(key);
    if(getenv("SERVER_NAME")) sprintf(domain,"%s",getenv("SERVER_NAME"));
    else domain[0]=0;
    sprintf(path,"/");

    printf("Set-Cookie: %s=; expires=Thu, 01-Jan-1970 00:00:00 GMT; path=%s; domain=%s\n",key,path,domain);
    return(1);
}

/*
 * Program       : time.c
 * Author        : Celso Martinho (celso@ua.pt)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logs.h"
#include "protos.h"
#include <defines.h>
#define FALSE 0
#define TRUE  1

time_t tx2date (char *date)
{
    int day=0;
    int month=0;
    int year=0;
    char *ptr;
    time_t event;
    struct tm date_tm;

    if(strlen(date)<2) return(0);
    day=atoi(date);
    if(ptr=strchr(date,'/')) {
        ptr++;
        month=atoi(ptr);
        if(ptr=strchr(ptr,'/')) {
            ptr++;
            year=atoi(ptr);
        }
    }
    printf("dia: %d mes: %d ano: %d\n",day,month,year);
    memset(&date_tm,0,sizeof(struct tm));
    date_tm.tm_mday=day;
    date_tm.tm_mon=month-1;
    date_tm.tm_year=year;
    date_tm.tm_isdst=1;
    event=mktime(&date_tm);

    return(event);
}

date2tx(char *out,time_t *in)
{
    struct tm *curr_date;

    curr_date=localtime(in);
    sprintf(out,"%.2d/%.2d/%.2d",curr_date->tm_mday,curr_date->tm_mon+1,curr_date->tm_year);
    return;
}

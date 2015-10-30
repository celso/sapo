/*
 * Program       : logs.c
 * Author        : Celso Martinho (celso@ua.pt)
 * Last Modified : 13-Feb-1995
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

#define SLOGFILE "s_actions_log"

s_log(char *action)
{
    FILE *fp;
    time_t secs,current;
    struct tm *date;
    struct tm *curr_date;

    time(&current);
    curr_date=localtime(&current);

    if(fp=fopen(SLOGS_DIR""SLOGFILE,"a")) {
        fprintf(fp,"%.2d/%.2d/%.2d|%.2d:%.2d:%.2d|%s|%s|%s\n",curr_date->tm_mday,curr_date->tm_mon+1,curr_date->tm_year,curr_date->tm_hour,curr_date->tm_min,curr_date->tm_sec,getenv("REMOTE_USER"),getenv("REMOTE_HOST"),action);
        fclose(fp);
    } else printf("ERROR: s_log() Can't open logfile for writing\n");
}
void s_lastlog(void)
{
    FILE *fp;
    char buf[256];
    char *ptr;

    if(fp=fopen(SLOGS_DIR"s_actions_log","r")) {
        fseek(fp,-600,SEEK_END);
        fgets(buf,sizeof(buf),fp);
        while(fgets(buf,sizeof(buf),fp)) {
            printf("%s",buf);
        }
        fclose(fp);
    }
}

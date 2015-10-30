/*
 *
 * Program       : crypt.c
 * Author        : Celso Martinho (celso@ua.pt)
 * Last Modified : 13-Feb-1995
 * Version       : 0.90
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protos.h"
#define FALSE 0
#define TRUE  1

char *getserver_id(char *url)
{
    static char id_server[256];
    char *tp,*tp2;

    memset(id_server,0,sizeof(id_server));

    if(strstr(url,"http://")) {
        tp=strchr(url,'/');
        tp++;
        tp++;
        if(tp2=strchr(tp,'/')) strncpy(id_server,tp,tp2-tp);
        else strcpy(id_server,tp);
    } else strcpy(id_server,"special scheme");
    return(id_server);
}

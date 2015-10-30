/*
 * Author        : Celso Martinho (celso@ua.pt)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logs.h"
#include "protos.h"
#include "queries.h"
#include <defines.h>
#define FALSE 0
#define TRUE  1

#undef NULL
#define NULL 0

/*
 * Library includes
 */

#include "../library/args.h"

/*
 * MSQL stuff...
 */

#include "../library/dbwrapper.h"

#define MSQL_DIR 1
#define MSQL_FILE 2

#define BUFSIZE 8096

#define ERROR(c) puts(c)

/*
 * id must be DIR
 */

int subdirs(int id)
{
    char querybuf[HUGE_BUFFER];
    int query_id;
    FILE *main_f;
    char buf[256];
    DBRESULT *result1;
    DBROW row1;
    int mat=0;
    DBHANDLER dbsocket;

    CONNECT(&dbsocket,"localhost","root","","sapo");

    sprintf(querybuf,NSELECT30,id);
    QUERY(&dbsocket,querybuf);
    result1=STORERESULT(&dbsocket);
    if(row1=FETCHROW(result1)) {
        sprintf(buf,"%s",row1[0]);
    }
    FREERESULT(result1);
    sprintf(querybuf,NSELECT31,buf);
    QUERY(&dbsocket,querybuf);
    mat=MATCHES(&dbsocket);
    DBCLOSE(&dbsocket);
    return(mat);
}

int subptrs(int id)
{
    char querybuf[HUGE_BUFFER];
    int query_id;
    FILE *main_f;
    char buf[256];
    DBRESULT *result1;
    DBROW row1;
    int mat=0;
    DBHANDLER dbsocket;

    CONNECT(&dbsocket,"localhost","root","","sapo");

    sprintf(querybuf,NSELECT32,id);
    QUERY(&dbsocket,querybuf);
    result1=STORERESULT(&dbsocket);
    if(row1=FETCHROW(result1)) {
        sprintf(buf,"%s",row1[0]);
    }
    FREERESULT(result1);
    sprintf(querybuf,NSELECT33,buf);
    QUERY(&dbsocket,querybuf);
    mat=MATCHES(&dbsocket);
    DBCLOSE(&dbsocket);
    return(mat);
}

char *get_title(int id)
{
    char querybuf[HUGE_BUFFER];
    int query_id;
    FILE *main_f;
    DBRESULT *result1;
    DBROW row1;
    int mat=0;
    DBHANDLER dbsocket;

    CONNECT(&dbsocket,"localhost","root","","sapo");

    sprintf(querybuf,NSELECT34,id);
    QUERY(&dbsocket,querybuf);
    result1=STORERESULT(&dbsocket);
    if(row1=FETCHROW(result1)) {
        sprintf(ret,"%s",row1[0]);
    }
    FREERESULT(result1);
    DBCLOSE(&dbsocket);
    return(ret);
}

char *get_location(int id)
{
    char querybuf[HUGE_BUFFER];
    int query_id;
    FILE *main_f;
    DBRESULT *result1;
    DBROW row1;
    int mat=0;
    DBHANDLER dbsocket;

    CONNECT(&dbsocket,"localhost","root","","sapo");
    ret[0]=NULL;
    sprintf(querybuf,NSELECT35,id);
    QUERY(&dbsocket,querybuf);
    result1=STORERESULT(&dbsocket);
    if(row1=FETCHROW(result1)) {
        sprintf(ret,"%s",row1[0]);
    }
    FREERESULT(result1);
    DBCLOSE(&dbsocket);
    return(ret);
}

char *get_area(int id)
{
    char querybuf[HUGE_BUFFER];
    int query_id;
    FILE *main_f;
    DBRESULT *result1;
    DBROW row1;
    int mat=0;
    DBHANDLER dbsocket;

    CONNECT(&dbsocket,"localhost","root","","sapo");

    sprintf(querybuf,NSELECT36,id);
    QUERY(&dbsocket,querybuf);
    result1=STORERESULT(&dbsocket);
    if(row1=FETCHROW(result1)) {
        sprintf(ret,"%s",row1[0]);
    }
    FREERESULT(result1);
    DBCLOSE(&dbsocket);
    return(ret);
}

char *get_desc(int id)
{
    char querybuf[HUGE_BUFFER];
    int query_id;
    FILE *main_f;
    DBRESULT *result1;
    DBROW row1;
    int mat=0;
    DBHANDLER dbsocket;

    CONNECT(&dbsocket,"localhost","root","","sapo");

    sprintf(querybuf,NSELECT37,id);
    QUERY(&dbsocket,querybuf);
    result1=STORERESULT(&dbsocket);
    if(row1=FETCHROW(result1)) {
        sprintf(ret,"%s",row1[0]);
    }
    FREERESULT(result1);
    DBCLOSE(&dbsocket);
    return(ret);
}

char *get_email(int id)
{
    char querybuf[HUGE_BUFFER];
    int query_id;
    FILE *main_f;
    DBRESULT *result1;
    DBROW row1;
    int mat=0;
    DBHANDLER dbsocket;

    CONNECT(&dbsocket,"localhost","root","","sapo");

    sprintf(querybuf,NSELECT38,id);
    QUERY(&dbsocket,querybuf);
    result1=STORERESULT(&dbsocket);
    if(row1=FETCHROW(result1)) {
        sprintf(ret,"%s",row1[0]);
    }
    FREERESULT(result1);
    DBCLOSE(&dbsocket);
    return(ret);
}

/*
int get_type(int id)
{
    char querybuf[HUGE_BUFFER];
    int query_id;
    FILE *main_f;
    DBRESULT *result1;
    DBROW row1;
    int type=0;
    DBHANDLER dbsocket;

    CONNECT(&dbsocket,"localhost","root","","sapo");

    sprintf(querybuf,NSELECT39,id);
    QUERY(&dbsocket,querybuf);
    result1=STORERESULT(&dbsocket);
    if(row1=FETCHROW(result1)) {
        type=atoi(row1[0]);
    }
    FREERESULT(result1);
    DBCLOSE(&dbsocket);
    return(type);
}
*/

int get_depth(int id)
{
    char querybuf[HUGE_BUFFER];
    int query_id;
    FILE *main_f;
    DBRESULT *result1;
    DBROW row1;
    int type=0;
    DBHANDLER dbsocket;

    CONNECT(&dbsocket,"localhost","root","","sapo");

    sprintf(querybuf,NSELECT40,id);
    QUERY(&dbsocket,querybuf);
    result1=STORERESULT(&dbsocket);
    if(row1=FETCHROW(result1)) {
        type=atoi(row1[0]);
    }
    FREERESULT(result1);
    DBCLOSE(&dbsocket);
    return(type);
}

void gencode(char *output,int seed,DBHANDLER *dbsocket)
{
    char querybuf[HUGE_BUFFER];
    DBRESULT *result1;
    DBROW row1;
    char tmp[40];
    int done=0;
    time_t t_seed;
    char *ptr;

    while(!done) {
        seed++;
        time(&t_seed);
        srand(t_seed);
        sprintf(tmp,"%d",(abs(seed*rand()))/10000);
        ptr=tmp;
        while(*ptr) { *ptr=*ptr-'0'+'a'; ptr++; }
        sprintf(querybuf,"SELECT code FROM new WHERE code like '%s'",tmp);
        QUERY(dbsocket,querybuf);
        result1=STORERESULT(dbsocket);
        if(row1=FETCHROW(result1)) {
            done=0;
        } else done=1;
        FREERESULT(result1);
    }
    strcpy(output,tmp);
}

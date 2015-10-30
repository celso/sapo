#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbwrapper.h"

char output[16000];

/*
 * Connect Databases
 */

DBHANDLER *CONNECT(DBHANDLER *handler, const char *host, const char *user, const char *passwd,char *dbname) {
#ifdef USE_MYSQL
    DBHANDLER *ret;

    memset(handler,0,sizeof(DBHANDLER));
    ret=mysql_connect(handler,host,user,passwd);
    if(ret) mysql_select_db(ret,dbname);
    return(ret);
}
#endif
#ifdef USE_MSQL
if((*handler=msqlConnect((char *)host)) == -1) {
    puts("Can't connect Database\n");
    exit(0);
}
if(msqlSelectDB(*handler,dbname) == -1 ) {
    printf("Couldn't select database\nERROR: %s\n",msqlErrMsg);
    msqlClose(*handler);
    exit(0);
}
return(handler);
}
#endif

/*
 * Close databases
 */

void DBCLOSE(DBHANDLER *handler) {
#ifdef USE_MYSQL
    mysql_close(handler);
}
#endif
#ifdef USE_MSQL
if(*handler) msqlClose(*handler);
return;
}
#endif

/*
 * Query databases
 */

int QUERY(DBHANDLER *handler,char *query) {
#ifdef USE_MYSQL
    return(mysql_query(handler,query));
}
#endif
#ifdef USE_MSQL
if(msqlQuery(*handler,query) == -1) {
    printf("ERROR: %s\nQUERY: %s\n",msqlErrMsg,query);
    return(0);
} else return(1);
}
#endif


/*
 * Store Result
 */
DBRESULT *STORERESULT(DBHANDLER *handler) {
#ifdef USE_MYSQL
    return(mysql_store_result(handler));
}
#endif
#ifdef USE_MSQL
return(msqlStoreResult());
}
#endif

/*
 * Fetch Row
 */
DBROW FETCHROW(DBRESULT *result) {
#ifdef USE_MYSQL
    return(mysql_fetch_row(result));
}
#endif
#ifdef USE_MSQL
return(msqlFetchRow(result));
}
#endif

/*
 * Free Result
 */
void FREERESULT(DBRESULT *result) {
#ifdef USE_MYSQL
    mysql_free_result(result);
}
#endif
#ifdef USE_MSQL
msqlFreeResult(result);
}
#endif


/*
 * NumRows
 */
int NUMROWS(DBRESULT *result) {
#ifdef USE_MYSQL
    return(mysql_num_rows(result));
}
#endif
#ifdef USE_MSQL
return(msqlNumRows(result));
}
#endif

ROW_OFFSET ROW_TELL(DBRESULT *result) {
#ifdef USE_MYSQL
    return(mysql_row_tell(result));
#endif
}

void DATA_SEEK(DBRESULT *result, unsigned long offset) {
#ifdef USE_MYSQL
    return(mysql_data_seek(result,offset));
#endif
}




/*
 * Matches
 */
int MATCHES(DBHANDLER *handler) {
    DBRESULT *result;
#ifdef USE_MYSQL
    result=mysql_store_result(handler);
    return(mysql_num_rows(result));
}
#endif
#ifdef USE_MSQL
result=msqlStoreResult();
return(msqlNumRows(result));
}
#endif

char *PRINTFIELD(char *host,char *dbase,char *table,char *field,char *filter)
{
    DBHANDLER dbsocket;
    DBRESULT *result;
    DBROW row;

    if(CONNECT(&dbsocket,host,"root","",dbase)) { 
        sprintf(output,"SELECT %s FROM %s WHERE %s",field,table,filter);
        QUERY(&dbsocket,output);
        if(result=STORERESULT(&dbsocket)) {
            if(row=FETCHROW(result)) {
                strcpy(output,row[0]);
            } else strcpy(output,"");
            FREERESULT(result);
        } else return(0);
        DBCLOSE(&dbsocket);
    }
    return(output);
}


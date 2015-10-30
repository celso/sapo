#define              USE_MYSQL       1 
/* #define         USE_MSQL        1   */

/*
 * Wrapper for MySQL
 */
#ifdef USE_MYSQL
#include <mysql/mysql.h>
#define DBHANDLER MYSQL
#define DBRESULT MYSQL_RES
#define DBROW MYSQL_ROW
#define ROW_OFFSET MYSQL_ROW_OFFSET

#endif
/*
 * Wrapper for mSQL
 */
#ifdef USE_MSQL
#include <msql.h>
#define DBHANDLER int
#define DBRESULT m_result
#define DBROW m_row
#define ROW_OFFSET int
#endif

/*
 * Prototypes
 */

DBHANDLER *CONNECT(DBHANDLER *handler, const char *host, const char *user, const char *passwd,char *dbname);
void DBCLOSE(DBHANDLER *handler);
int QUERY(DBHANDLER *handler,char *query);
DBRESULT *STORERESULT(DBHANDLER *handler);
DBROW FETCHROW(DBRESULT *result);
int NUMROWS(DBRESULT *result);
ROW_OFFSET ROW_TELL(DBRESULT *result);
void DATA_SEEK(DBRESULT *result, unsigned long offset);
int MATCHES(DBHANDLER *handler);
char *PRINTFIELD(char *host,char *dbase,char *table,char *field,char *filter);

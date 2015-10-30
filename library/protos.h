/*
 * Author        : Celso Martinho (celso@ua.pt)
 *
 */

#include <time.h>

/* #define DEBUG */

/* args.c */

char *tohidden_ptr(char *args);

/* text.c */

char *runwhite(char *start);
char *getwhite(char *start);
char *fget_field(FILE *fp,long offset,long column);
char *getserver_id(char *url);
int get_counter();
char *strdupdelim (const char *beg, const char *end);

/* templates.c */

struct List *init_template(void);
void get_value(struct List *list,char *title,char *value);
void print_template(struct List *list,char *file);
void fprint_template(struct List *list,FILE *fp,char *file);

/* queries.c */
char *get_location(int id);
char *get_area(int id);
char *get_email(int id);
char *get_desc(int id);
char *get_title(int id);
// void gencode(char *output,int seed,DBHANDLER *dbsocket);

/* templates.h */
int search_first_tag(char *line,char **start);

/* soundex.c */
char *soundex(char *arg);

/* bandas.c */
void logview(int id);

time_t tx2date (char *date);

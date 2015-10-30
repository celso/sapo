/*
 * Program       : pesquisa (Versão com CDB's e QSORT ROX!
 * Author        : Celso Martinho (celso@sl.pt)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <dirent.h>
#include <cgic.h>
#include <cdb.h>
#define FALSE 0
#define TRUE  1
#include "../include/defines.h"
#include "../library/protos.h"
#include "../library/file.h"

#undef NULL
#define NULL 0

#undef DEBUG

#define DESTACADO 1
#define SIMPLES   2
#define START     3                       

#define MAX_RESULTS 800

#define P_WORD		1
#define P_WORD_NOT	2
#define P_AND		3
#define P_AND_DEAD	4
#define P_OR		5
#define P_NOT		6
#define P_OPEN_BRACKET	7
#define P_CLOSE_BRACKET	8

#define HASH_LIMIT 20000

/*
 * Library includes
 */

#include "../library/queries.h"
#include "../library/lists.h"
#include "../library/args.h"

#define DAYS_NEW 15
#define MAX_ENTRIES 400

#define KEY_LENGTH 100

#define AND 0
#define OR 4

#define	CDBS_DIR	"/home/sapo/cdbs/"
// #define	CDBS_DIR	"/servers/cdbs/"
#define	CACHE_DIR	"/servers/cache/pesquisa/"

extern char output[];

char typenames[]="AND\0OR\0";
char months[][4]={"Jan\0","Feb\0","Mar\0","Apr\0","May\0","Jun\0","Jul\0","Aug\0","Sep\0","Oct\0","Nov\0","Dec\0"};

#define ERROR(c) puts(c)
#define METHOD "get"

int get_destaqueid(char *);
int sh_cdb_obj(int offset,char *output,int sizeof_output,int fd);
void fprint_field(FILE *output,char *out,int match,int weight,struct List *list,int maxweight,int term);
void print_heading(FILE *fp,char *title);
// struct match_key *check_offset(struct match_key *start,struct match_key *del);
struct match_key *check_offset_ng(struct match_key *start,struct match_key *del);
struct match_key *check_offset(struct List *list,struct match_key *del);
void cleanup(void);

struct key_node {
    struct Node k_node;
    char k_name[KEY_LENGTH];
    int k_type;
    int k_spell;
    int k_altweight;
    int k_has_altweight;
};

struct match_key {
    struct Node mt_node;
    struct key_node *mt_kn;
    int mt_offset;
    int mt_weight;
    int mt_term;
    int mt_type;
};

struct apontador {
    int tipo;
    char *titulo;
    char *url;
    char *descricao;
    char *data;
    char *html;
};

int cmp_peso(struct match_key *c1,struct match_key *c2);
int cmp_tipo(struct match_key *c1,struct match_key *c2);
int cmp_rep(struct match_key *c1,struct match_key *c2);

int mmatches;
int do_exact;
int do_titulo;
int do_desc;
int do_url;
int do_email;
int do_mac; /* joaop */
int type,lmatches,fs,printit,needoperator;
int flags;
int state;
int jump2google=0;
int time1,time2;
int needul,hasoutput;
int feeling_lucky;
struct List *keywords_list;
struct match_key *mk_node;
struct key_node *node;
struct key_node *node2;
struct key_node *node3;
time_t start,end,current;
char tmpoutput[512];
struct List *template1;
char querybuf[4096];
int ffluck=1;
int preference=0;
char luckybuf[10000];
char cdb_file1[200];
char cdb_file2[200];
char cache_name[200];
char skey[5];
int cdb_mode=0;
int eliminar_or=1;
int nterms=0;
char tkeys[1024];
int have_template=0;

cgiMain(int argc, char *argv[])
{
    char keyword[256];
    char tree[2048];
    char buffer[4096];
    char banda[256];
    char value[80];
    char burl[256];
    char bdbuf[2024];
    char bdesc[1024];
    char word[100];
    char server[SMALL_BUFFER];
    char *ptr,*new,*tp,*tp2,*left,*right;
    struct tm *date;
    int i,nkeys=0;
    struct key_node *mynode;
    struct key_node *mynext;
    FILE *logs;
    int nnews=0;
    char cbuf[16000];
    int altgroup;
    int bandaid=0;
    char sugestao[1024];
    int stword=1;
    char sword[200];
    char mediabooks[500];
    int bd,len;
    char templ[30];

    feeling_lucky=0;
    altgroup=0;
    nnews=0;
    nkeys=0;
    needul=0;
    hasoutput=0;
    mmatches=0;
    do_exact=0;
    do_titulo=0;
    do_desc=0;
    do_url=0;
    type=0;
    lmatches=0;
    needoperator=0;

    time(&start);
    template1=init_template();
    new_var(template1,"max",str(MAX_ENTRIES));

    if(cgiFormString("action",buffer,sizeof(buffer))==cgiFormSuccess) {
        if(strstr(buffer,"Rapidinha")) { feeling_lucky=1; }
        memset(luckybuf,0,sizeof(luckybuf));
    }

    if(cgiFormString("template",templ,sizeof(templ))==cgiFormSuccess) {
        have_template=1;
    }

    if(cgiFormString("strict",buffer,sizeof(buffer))==cgiFormSuccess) {
        if(strstr(buffer,"1")) eliminar_or=1;
        else eliminar_or=0;
    }


    if((cgiFormString("selsearch",buffer,sizeof(buffer))==cgiFormSuccess)||
            (cgiFormString("selsearch2",buffer,sizeof(buffer))==cgiFormSuccess)) {

        i=atoi(buffer);
        if(i==0) jump2google=1;
        if(i==6) { i=0; buffer[0]='0'; }
        snprintf(cdb_file1,sizeof(cdb_file1),CDBS_DIR"/ptr_30_%d.cdb",i);
        snprintf(skey,sizeof(skey),"%d",i);
        cdb_mode=4;
        switch (buffer[0]) {
            case '5':
                memset(keyword,0,sizeof(keyword));
                cgiFormString("kw",keyword,sizeof(keyword));
                ptr=keyword;
                while(*ptr) { if(*ptr==' ') *ptr='+'; ptr++; }
                printf("Location: http://mundial.sapo.pt/cgi/google?kw=%s\n\n",keyword);
                exit(0);
                break;
            case '0':
                strcpy(cdb_file1,CDBS_DIR"/ptr_0.cdb");
                strcpy(cdb_file2,CDBS_DIR"/pesq_0.cdb");
                cdb_mode=0;
                break;
            case '1':
                strcpy(cdb_file1,CDBS_DIR"/ptr_10.cdb");
                strcpy(cdb_file2,CDBS_DIR"/pesq_10.cdb");
                cdb_mode=1;
                break;
            case '3':
                strcpy(cdb_file1,CDBS_DIR"/ptr_40.cdb");
                strcpy(cdb_file2,CDBS_DIR"/pesq_40.cdb");
                cdb_mode=3;
                break;
            case '4':
                strcpy(cdb_file1,CDBS_DIR"/ptr_30.cdb");
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                cdb_mode=4;
                break;
            case 'q':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(cdb_file1,sizeof(cdb_file1),CDBS_DIR"/ptr_30_4.cdb");
                snprintf(sword,sizeof(sword),"<option value=q selected>tek\n");
                new_var(template1,"extra",sword);
                break;
            case 'a':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(sword,sizeof(sword),"<option value=a selected>família\n");
                new_var(template1,"extra",sword);
                break;
            case 'M':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(sword,sizeof(sword),"<option value=M selected>educação\n");
                new_var(template1,"extra",sword);
                break;
            case 'f':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(sword,sizeof(sword),"<option value=f selected>finanças\n");
                new_var(template1,"extra",sword);
                break;
            case 'k':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(sword,sizeof(sword),"<option value=k selected>lazer\n");
                new_var(template1,"extra",sword);
                break;
            case 'g':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(sword,sizeof(sword),"<option value=g selected>medicina\n");
                new_var(template1,"extra",sword);
                break;
            case 'o':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(sword,sizeof(sword),"<option value=o selected>milénio\n");
                new_var(template1,"extra",sword);
                break;
            case 'd':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(sword,sizeof(sword),"<option value=d selected>tecnologia\n");
                new_var(template1,"extra",sword);
                break;
            case 'J':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(cdb_file1,sizeof(cdb_file1),CDBS_DIR"/ptr_30_J.cdb");
                snprintf(sword,sizeof(sword),"<option value=J selected>mulheres\n");
                new_var(template1,"extra",sword);
                break;
            case '7': // mesma coisa netfeminina
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(cdb_file1,sizeof(cdb_file1),CDBS_DIR"/ptr_30_J.cdb");
                snprintf(sword,sizeof(sword),"<option value=J selected>mulheres\n");
                new_var(template1,"extra",sword);
                break;
            case 'w':
                strcpy(cdb_file2,CDBS_DIR"/pesq_30.cdb");
                snprintf(cdb_file1,sizeof(cdb_file1),CDBS_DIR"/ptr_30_w.cdb");
                snprintf(sword,sizeof(sword),"<option value=w selected>gameover\n");
                new_var(template1,"extra",sword);
                break;
        }
    }
    else
    {
        strcpy(cdb_file1,CDBS_DIR"/ptr_0.cdb");
        strcpy(cdb_file2,CDBS_DIR"/pesq_0.cdb");
        cdb_mode=0;
    }
    /*
     * Por defeito faz pesquisa no titulo e descricao
     */

    do_titulo = 1;
    do_desc = 1;
    if((cgiFormString("tt",buffer,sizeof(buffer))==cgiFormSuccess)&&(!strcmp(buffer,"on"))) do_titulo=1; else do_titulo=0;
    if((cgiFormString("ds",buffer,sizeof(buffer))==cgiFormSuccess)&&(!strcmp(buffer,"on"))) do_desc=1; else do_desc=0;
    if((cgiFormString("ur",buffer,sizeof(buffer))==cgiFormSuccess)&&(!strcmp(buffer,"on"))) do_url=1; else do_url=0;
    if((cgiFormString("em",buffer,sizeof(buffer))==cgiFormSuccess)&&(!strcmp(buffer,"on"))) do_email=1; else do_email=0;
    if((cgiFormString("mac",buffer,sizeof(buffer))==cgiFormSuccess)&&(!strcmp(buffer,"on"))) do_mac=1; else do_mac=0; /* joaop */

    /*
     * NAO ESQUECER ISTO!
     */

    memset(tree,0,sizeof(tree));
    memset(keyword,0,sizeof(keyword));

    cgiFormString("kw",keyword,sizeof(keyword));
    substitute(keyword,"'","\\'");
    cgiFormString("fs",buffer,sizeof(buffer));
    if(strlen(buffer)) fs=atol(buffer); else fs=0;
    if(fs>MAX_RESULTS) fs=MAX_RESULTS;
    cgiFormString("ar",buffer,sizeof(buffer));

    // debug celso

    if(strlen(buffer)) {
        ptr=buffer;
        while(*ptr=='-'&&*ptr) ptr++;
        strcpy(tree,ptr);
        ptr=tree+strlen(tree)-1;
        while(*ptr=='-'&&*ptr) { *ptr=0; ptr--; }
        ptr=tree; while(*ptr) { if(*ptr=='-') *ptr='/'; ptr++; }
    }

    if(strlen(keyword)<2 || (!do_titulo && !do_desc && !do_url && !do_email)) new_var(template1,"generica","1"); else new_var(template1,"generica","0");

    lower(keyword);
    win2iso(keyword);
    strip2ascii(keyword);

    /*
     * Tira +s e ' 's iniciais.
     */

    ptr=keyword;
    while(*ptr&&(*ptr==' '||*ptr=='+')) ptr++;
    memcpy(keyword,ptr,strlen(ptr)+1);

    /*
     * PARSER
     *
     * Vamos ver se foi utilizada a notacao <<key1+key2>> ou <<key1 key2>>
     */

    ptr=keyword;
    while(*ptr) {
        if(*ptr=='+') { *ptr=' '; eliminar_or=0; }
        if((*ptr=='/')||(*ptr==';')||(*ptr==',')||(*ptr=='.')) *ptr=' ';
        ptr++;
    }

    txpack(keyword);

    /* END PARSER */

    /*
     * parser da pesquisa
     */
    if(keywords_list=(struct List *)calloc(sizeof(struct List),1)) {
        NewList(keywords_list);
        ptr=keyword;
        left=keyword;
        do {
            if(*ptr=='(') {
                node=(struct key_node *)calloc(sizeof(struct key_node),1);
                node->k_type=P_OPEN_BRACKET;
                AddTail(keywords_list,(struct Node *)node);
                if(*ptr==' ') ptr++; left=ptr;
            }
            else
                if(*ptr==')') {
                    node=(struct key_node *)calloc(sizeof(struct key_node),1);
                    node->k_type=P_CLOSE_BRACKET;
                    AddTail(keywords_list,(struct Node *)node);
                    ptr++;
                }
                else
                    if(!strncmp(ptr,"not ",4)) {
                        ptr+=3;
                        node=(struct key_node *)calloc(sizeof(struct key_node),1);
                        node->k_type=P_NOT;
                        AddTail(keywords_list,(struct Node *)node);
                    } 
                    else
                        if(!strncmp(ptr,":exact ",7)) {
                            ptr+=6;
                            do_exact=1;
                        } 
                        else
                            if(!strncmp(ptr,":-url ",6)) {
                                ptr+=5;
                                do_url=0;
                            } 
                            else
                                if(!strncmp(ptr,"not(",4)) {
                                    ptr+=4;
                                    node=(struct key_node *)calloc(sizeof(struct key_node),1);
                                    node->k_type=P_NOT;
                                    AddTail(keywords_list,(struct Node *)node);
                                    node=(struct key_node *)calloc(sizeof(struct key_node),1);
                                    node->k_type=P_OPEN_BRACKET;
                                    AddTail(keywords_list,(struct Node *)node);
                                } 
                                else
                                    if(!strncmp(ptr,"and ",4)) {
                                        ptr+=3;
                                        node=(struct key_node *)calloc(sizeof(struct key_node),1);
                                        node->k_type=P_AND;
                                        AddTail(keywords_list,(struct Node *)node);
                                        needoperator=0;
                                    } 
                                    else
                                        if(!strncmp(ptr,"and(",4)) {
                                            ptr+=4;
                                            node=(struct key_node *)calloc(sizeof(struct key_node),1);
                                            node->k_type=P_AND;
                                            AddTail(keywords_list,(struct Node *)node);
                                            node=(struct key_node *)calloc(sizeof(struct key_node),1);
                                            node->k_type=P_OPEN_BRACKET;
                                            AddTail(keywords_list,(struct Node *)node);
                                            needoperator=0;
                                        } 
                                        else
                                            if(!strncmp(ptr,"or ",3)) {
                                                ptr+=2;
                                                node=(struct key_node *)calloc(sizeof(struct key_node),1);
                                                node->k_type=P_OR;
                                                eliminar_or=0;
                                                AddTail(keywords_list,(struct Node *)node);
                                                left=ptr;
                                                needoperator=0;
                                            } 
                                            else
                                                if(!strncmp(ptr,"or(",3)) {
                                                    ptr+=3;
                                                    node=(struct key_node *)calloc(sizeof(struct key_node),1);
                                                    node->k_type=P_OR;
                                                    eliminar_or=0;
                                                    AddTail(keywords_list,(struct Node *)node);
                                                    node=(struct key_node *)calloc(sizeof(struct key_node),1);
                                                    node->k_type=P_OPEN_BRACKET;
                                                    AddTail(keywords_list,(struct Node *)node);
                                                    left=ptr;
                                                    needoperator=0;
                                                } 
                                                else 
                                                    if((right=strchr(ptr,' '))||(right=ptr+strlen(ptr))) {
                                                        memset(word,0,sizeof(word));
                                                        node=(struct key_node *)calloc(sizeof(struct key_node),1);
                                                        if(*ptr=='-') { left=ptr+1; node->k_type=P_WORD_NOT; }
                                                        else if(*ptr=='+') { left=ptr+1; node->k_type=P_WORD; }
                                                        else { left=ptr; node->k_type=P_WORD; }
                                                        if(*left=='"') {
                                                            left++;
                                                            if(ptr=strchr(left,'"')) {
                                                                strncpy(word,left,ptr-left);
                                                                right=ptr+1;
                                                            }
                                                        } else strncpy(word,left,right-left);
                                                        if((strlen(word)>2)&&(strcmp(word,"http"))&&(strcmp(word,"www"))&&(strcmp(word,"html"))) {
                                                            node2=NULL;
                                                            if(word[strlen(word)-1]==')') {
                                                                node2=(struct key_node *)calloc(sizeof(struct key_node),1);
                                                                node2->k_type=P_CLOSE_BRACKET;
                                                                word[strlen(word)-1]=0;
                                                            }
                                                            substitute(word,"'"," ");
                                                            strcpy(node->k_name,word);
                                                            if(needoperator) {
                                                                node3=(struct key_node *)calloc(sizeof(struct key_node),1);
                                                                node3->k_type=P_AND_DEAD;
                                                                AddTail(keywords_list,(struct Node *)node3);
                                                            }
                                                            nkeys++; AddTail(keywords_list,(struct Node *)node); needoperator=1;
                                                            if(stword) { strcpy(sword,node->k_name); stword=0; }
                                                            if(node2) AddTail(keywords_list,(struct Node *)node2);
                                                        }
                                                        ptr=right;
                                                    } 

            if(*ptr) ptr++;

        } while (*ptr);
    } else exit(-1);

    /*
     * Mostra banda
     */

    cbuf[0]=0; i=0;
    if(nkeys>0) {
        int error=0;

        //    new_var(template1,"tipo",&typenames[type]);
        memset(tkeys,0,sizeof(tkeys));
        if(do_exact) strcat(tkeys,":exact ");

        if(mynode=(struct key_node *)keywords_list->lh_Head)
            do {

                if(mynode->k_type==P_WORD) {
                    if(i) strcat(cbuf,"+"); else i=1;
                    strcat(cbuf,mynode->k_name);
                    /*
                     * Loga a palavra
                     */
                    time(&current);
                    date=localtime(&current);
                    if(logs=fopen(LOGS_DIR"pesquisa_access_log.00000000","a")) {
                        fprintf(logs,"%s - - [%d/%s/%d:%.2d:%.2d:%.2d +0100] \"GET %s HTTP/1.1\" 200 1 \"%s\" \"%s\"\n",getenv("REMOTE_ADDR"),date->tm_mday,months[date->tm_mon],date->tm_year+1900,date->tm_hour,date->tm_min,date->tm_sec,mynode->k_name,getenv("HTTP_REFERER"),getenv("HTTP_USER_AGENT"));
                        fclose(logs);
                    }

                    if(strchr(mynode->k_name,' ')) { sprintf(buffer,"&quot;%s&quot;",mynode->k_name); } else strcat(tkeys,mynode->k_name);

                }

                if(mynode->k_type==P_WORD_NOT) {
                    if(strchr(mynode->k_name,' ')) { sprintf(buffer,"-&quot;%s&quot;",mynode->k_name); strcat(tkeys,buffer); }
                    else { strcat(tkeys,"-"); strcat(tkeys,mynode->k_name); }
                }
                if(mynode->k_type==P_AND) strcat(tkeys," AND ");
                if(mynode->k_type==P_AND_DEAD) strcat(tkeys," ");
                if(mynode->k_type==P_OR) strcat(tkeys," OR ");
                if(mynode->k_type==P_NOT) strcat(tkeys," NOT ");
                if(mynode->k_type==P_OPEN_BRACKET) strcat(tkeys,"(");
                if(mynode->k_type==P_CLOSE_BRACKET) strcat(tkeys,")");
                error++;
            } while((mynode=(struct key_node *)mynode->k_node.ln_Succ)&&(error<100));
        new_var(template1,"keywords",tkeys);
    }

    new_var(template1,"kw",cbuf);

    if(nkeys>0) bool_search_idx(tree,keywords_list);
    new_var(template1,"ocorrencias",str(mmatches));
    if(jump2google&&(mmatches==0)) {
        memset(keyword,0,sizeof(keyword));
        cgiFormString("kw",keyword,sizeof(keyword));
        ptr=keyword;
        while(*ptr) { if(*ptr==' ') *ptr='+'; ptr++; }
        printf("Location: http://mundial.sapo.pt/cgi/google?kw=%s\n\n",keyword);
        exit(0);
    }

    new_var(template1,"time",str(end-start));
    if(mmatches) {
        new_var(template1,"smatch",str(fs+1));
        if(fs+20 >= mmatches) {
            new_var(template1,"ematch",str(mmatches));
        }
        else
        {
            new_var(template1,"ematch",str(fs+20));
        }
    }


    /*
     *  * Faz a mioleira para o lado esquerdo
     *   */

    if(mmatches<20) nnews=floor(mmatches/3);
    else nnews=6;
    if(nnews==0) nnews=1;

    if(strlen(sword)>20) { sword[15]=0; strcat(sword,"..."); }

    sprintf(bdbuf,"http://www.mediabooks.pt/cgi-bin/procura.cgi?TipoPesquisa=Titulo&Pesquisa=%s",sword);
    new_var(template1,"pesq_mediabooks",bdbuf);
    new_var(template1,"words",sword);

    cgiFormString("kw",buffer,sizeof(buffer));
    ptr=buffer;
    while(*ptr) { if(*ptr==' ') *ptr='+'; ptr++; }
    sprintf(bdbuf,"http://mundial.sapo.pt/cgi/google?kw=%s",buffer);
    new_var(template1,"pesq_google",bdbuf);
    sprintf(bdbuf,"<a href=\"http://mundial.sapo.pt/cgi/google?kw=%s\"><img src=\"/images/botao_mundial.gif\" border=0></a>",buffer);
    new_var(template1,"google",bdbuf);

    /*
     * Reconstroi a sintaxe do CGI-BIN
     */

    memset(buffer,0,sizeof(buffer));
    tocgi(tkeys);

    if(eliminar_or&&(nkeys>1)) {
        sprintf(buffer,"/cgi/pesquisa?kw=%s&ar=%s&selsearch=%s&strict=0",tkeys,tree,skey);
        new_var(template1,"nonstrict",buffer);
    }

    sprintf(buffer,"/cgi/pesquisa?kw=%s&ar=%s&selsearch=%s&strict=%d",tkeys,tree,skey,eliminar_or);
    if(do_titulo) strcat(buffer,"&tt=on");
    if(do_desc) strcat(buffer,"&ds=on");
    if(do_email) strcat(buffer,"&em=on");
    if(do_url) strcat(buffer,"&ur=on");
    if(have_template) { strcat(buffer,"&template="); strcat(buffer,templ); }

    /*
     * Imprime barra de scroll entre as varias paginas
     */

    if(cdb_mode==0) { 
        new_var(template1,"selected0","SELECTED");
    }
    if(cdb_mode==1) {
        new_var(template1,"selected1","SELECTED");
    }
    if(cdb_mode==2) {
        new_var(template1,"selected2","SELECTED");
    }
    if(cdb_mode==3) {
        new_var(template1,"selected3","SELECTED");
    }
    if(cdb_mode==4) {
        new_var(template1,"selected4","SELECTED");
    }

    if(mmatches) {
        char scroll[20000];
        char scrollbuf[5000];
        char hidden[4096];

        memset(scroll,0,sizeof(scroll));

        strcpy(hidden,buffer);

        if(fs>=20) {
            sprintf(scrollbuf,"<a href=\"%s&fs=%d\">Anterior</a> \n",hidden,fs-20);
            strcat(scroll,scrollbuf);
        }
        for(i=0;i<((mmatches/20)+1);i++) {
            if(((fs+20)>i*20) && (fs<=i*20)) {
                sprintf(scrollbuf," | <strong>%d</strong>",i+1);
                strcat(scroll,scrollbuf);
            }
            else
            {
                sprintf(scrollbuf," | <a href=\"%s&fs=%d\">%d</a>\n",hidden,i*20,i+1);
                strcat(scroll,scrollbuf);
            }
        }
        if((fs+20)<mmatches) {
            sprintf(scrollbuf," | <a href=\"%s&fs=%d\">Seguinte</a>\n",hidden,fs+20);
            strcat(scroll,scrollbuf);
        }
        new_var(template1,"barra",scroll);
    }

    if((!feeling_lucky)||(mmatches==0)) printf("Content-type: text/html\n\n");

    time(&end);

    if(feeling_lucky&&mmatches) {
        char *z;
        printf("Content-type: text/html\n\n");
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"<option>----------------------------\n<option value=http://wwwwww.sapo.pt/cgi/pesquisa\%3Fkw=%s",tkeys);
        if(do_titulo) strcat(buffer,"\%26tt=on");
        if(do_desc) strcat(buffer,"\%26ds=on");
        if(do_url) strcat(buffer,"\%26ur=on");
        strcat(buffer,">Pesquisar Normalmente");
        strcat(luckybuf,buffer);
        z=luckybuf; while(*z) { if(*z==' ') *z='+'; z++; }
        z=luckybuf; while(*z) { if(*z=='&') *z='e'; z++; }
        z=luckybuf; while(*z) { if(*z=='?') *z='+'; z++; }
        new_var(template1,"luckstuff",luckybuf);
        print_template(template1,TEMPLATES_DIR"pesquisa/frames.html");
        cleanup();
        exit(0);
    }
    else
    {
        cbuf[0]=0;
        i=0;
        if(node=(struct key_node *)keywords_list->lh_Head)
            do {
                int len;
                if(node->k_type==P_WORD) {
                    if((strlen(cbuf)+strlen(node->k_name)+3)<sizeof(cbuf)) {
                        if(i) strcat(cbuf,"<br>");
                        else i=1;
                        strcat(cbuf,node->k_name); 
                    }
                }
            } while(node=(struct key_node *)node->k_node.ln_Succ);
        new_var(template1,"palavras",cbuf);
        if(!have_template) print_template(template1,TEMPLATES_DIR"pesquisa/header2.html"); else {
            snprintf(buffer,sizeof(buffer),TEMPLATES_DIR"pesquisa/%s_header.html",templ);
            print_template(template1,buffer);
        }

        if(hasoutput) {
            print_file(tmpoutput);
            memset(keyword,0,sizeof(keyword));
            cgiFormString("kw",keyword,sizeof(keyword));
            ptr=keyword;
            while(*ptr) { if(*ptr==' ') *ptr='+'; ptr++; }
            printf("<p align=right><img src=\"/images/seta.gif\"> <b>Experimente a <a href=\"http://mundial.sapo.pt/cgi/google?kw=%s\">Pesquisa Mundial</a> do SAPO</b><br>",keyword);
            if(eliminar_or&&(nkeys>1)) {
                printf("<img src=\"/images/seta.gif\"> <b>Experimente a mesma <a href=\"/cgi/pesquisa?kw=%s&ar=%s&selsearch=%s&strict=0\">pesquisa do SAPO em modo OR</a></b><br>(menos restrita)",tkeys,tree,skey);
            }
            unlink(tmpoutput);
        }

        if(!have_template) print_template(template1,TEMPLATES_DIR"pesquisa/footer2.html"); else {
            snprintf(buffer,sizeof(buffer),TEMPLATES_DIR"pesquisa/%s_footer.html",templ);
            print_template(template1,buffer);
        }
        end_template(template1);
    }

    cleanup();
    exit(0);
}

bool_search_idx(char *tree,struct List *list)
{
    FILE *output;
    char buf[HUGE_BUFFER];
    char cdb[HUGE_BUFFER*5];
    char table[8];
    int b1,b2,b3,b4;
    char oper[10];
    char *keyword,*my_keyword;
    long loc_offset=-1;
    int done=0,error;
    int hit=0;
    int has_sec=0;
    int size_of_key;
    int items,needcomma=0;
    int gerror,needoper=0;
    int troid = 1;
    int contagem = 0;
    int len,i,z;
    int weight;
    int notrequired;
    char *ptr2,*ptr3;
    struct List *match_list;
    struct match_key *mt_node;
    struct match_key *mt_start;
    struct match_key *tmp_node;
    struct match_key *next_node;
    struct match_key buffer_node;
    int fd;
    int maxweight=0;
    struct key_node *node;
    struct key_node *new_node;
    char *ptr;
    int lastdir;
    int shown=0;
    int found=0;
    int recursive;
    int ordered;
    int nl,nt,cs,m,ln;
    int have_cache=0;
    FILE *cache;
    struct Node *pred,*castnode; 
    char *array,*dst;
    char *array_rep;

    sprintf(tmpoutput,"/tmp/%d.sout",(int)getpid());
    if(!(output=fopen(tmpoutput,"w"))) return(0);
    hasoutput=1;
    state=START;
    needul=1;

    /* CDB queries */

    /* Aqui vamos adicionar às palavras que temos, as variantes das mesmas */


    node=(struct key_node *)list->lh_Head;

#ifdef DEBUG
    time(&current); printf("%d segundos passaram - hipoteses.cdb <br>",current-start);
#endif


    if(!do_exact&&(fd=open(CDBS_DIR"/hipoteses.cdb",O_RDONLY))) {
        do {
            int len;
            if((node->k_type==P_WORD)||(node->k_type==P_WORD_NOT)) {
                // printf("procura por: %s\n",node->k_name);
                if(cdb_seek(fd,node->k_name,strlen(node->k_name),&len)) {
                    if(len<=sizeof(cdb)) {
                        len=read(fd,cdb,len);
                    } else { fprintf(output,"<!-- overflow 1-->"); len=read(fd,cdb,sizeof(cdb)); }
                    cdb[len]=0;
                    ptr2=cdb;
                    recursive=0;
                    do {
                        if(ptr=strchr(ptr2,' ')) *ptr=0;
                        new_node=(struct key_node *)calloc(sizeof(struct key_node),1);
                        if(ptr3=strchr(ptr2,':')) {
                            *ptr3=0;
                            node->k_altweight=atoi(ptr2);
                            node->k_has_altweight=1;
                            new_node->k_altweight=atoi(ptr2);
                            new_node->k_has_altweight=1;
                            ptr2=ptr3+1;
                            //            printf("<!-- ALTWEIGHT: %s %d -->\n",node->k_name,node->k_altweight);
                        } else { new_node->k_has_altweight=0; node->k_has_altweight=0; }
                        snprintf(new_node->k_name,KEY_LENGTH,"%s",ptr2);
                        new_node->k_type=node->k_type;
                        new_node->k_spell=1;
                        AddTail(list,(struct Node *)new_node);
                        ptr2=ptr+1;
                        recursive++;
                    } while(ptr&&(recursive<5)); /* nao mais do que 5 variantes por key */
                }
            }
        } while((node=(struct key_node *)node->k_node.ln_Succ)&&(node->k_spell!=1));
        close(fd);
    }

    /* Aqui vamos apagar as palavras repetidas num é burdade?
     * NOTs também
     */

    if(node=(struct key_node *)list->lh_Head)
        do {
            if(node->k_type==P_WORD) {
                if(!node->k_spell) nterms++;
                if(check_words(list,node->k_name)>=2) {
                    Remove(node,list); if(!node->k_spell) nterms--;
                    node=(struct key_node *)list->lh_Head; /* volta ao inicio */
                }
            }
        } while(node=(struct key_node *)node->k_node.ln_Succ);

    if(node=(struct key_node *)list->lh_Head)
        do {
            if(node->k_type==P_WORD_NOT) {
                if(check_words(list,node->k_name)>=2) {
                    Remove(node,list);
                    node=(struct key_node *)list->lh_Head; /* volta ao inicio */
                }
            }
        } while(node=(struct key_node *)node->k_node.ln_Succ);

    /* Constroi nome do cache */
    nl=0; nt=0; cs=0;
    if(node=(struct key_node *)list->lh_Head)
        do {
            if(node->k_type==P_WORD) {
                m=0;
                nl+=strlen(node->k_name);
                nt++;
                ptr=node->k_name;
                ln=0;
                while(*ptr) { ln++; m+=(*ptr*ln); ptr++; }
                cs+=m;
            }
        } while(node=(struct key_node *)node->k_node.ln_Succ);
    snprintf(cache_name,sizeof(cache_name),CACHE_DIR"/%d_%s_%d_%d_%s.cache",eliminar_or,skey,nl,nt,tkeys);
    /* end cache */

    /*
     * Vamos ver isto já está em cache... Se sim, vamos ler e passar à impressao
     * dos resultados. No cdbs, no sorting, no nothing...
     */ 

    if(cache=fopen(cache_name,"r")) {
        if(match_list=(struct List *)calloc(sizeof(struct List),1)) {
            fread((void *)&maxweight,sizeof(int),1,cache);
            NewList(match_list);
            do
            {
                mt_node=(struct match_key *)calloc(sizeof(struct match_key),1);
                if(fread((void *)mt_node,sizeof(struct match_key),1,cache)) {
                    AddTail(match_list,(struct Node *)mt_node);
                    found++;
                }
            } while(!feof(cache));
            fclose(cache);

            if(array=calloc(sizeof(struct match_key),found)) {
                dst=array;
                if(mt_node=(struct match_key *)match_list->lh_Head)
                    do {
                        memcpy((void *)dst,(void *)mt_node,sizeof(struct match_key));
                        dst+=sizeof(struct match_key);
                    } while(mt_node=(struct match_key *)mt_node->mt_node.ln_Succ);
            }
            have_cache=1;
        }
    }

    /*
     * Bolas! Nao temos cache disto... Let's go to work then...
     * E aqui vamos sacar o tutano aos nossos queridos e rápidos cdbs
     */

    if(!have_cache) {
        if(match_list=(struct List *)calloc(sizeof(struct List),1)) {
            int len;
            NewList(match_list);
            node=(struct key_node *)list->lh_Head;

            /* celso */
            // printf("Content-type: text/html\n\n");
            // 
            // 
#ifdef DEBUG
            time(&current); printf("%d segundos passaram - cdb_file1 <br>",current-start);
#endif

            if(fd=open(cdb_file1,O_RDONLY)) {
                do {
                    if((node->k_type==P_WORD)||(node->k_type==P_WORD_NOT)) {
                        if(cdb_seek(fd,node->k_name,strlen(node->k_name),&len)) {
                            // printf("Content type: text/html\n\n len: %d cdb: %d word: %s\n",len,sizeof(cdb),node->k_name);
                            if(len<=sizeof(cdb)) {
                                len=read(fd,cdb,len);
                                //              printf("Content type: text/html\n\n<!-- ok : %s-->\n",cdb); 
                            } else { 
                                fprintf(output,"<!-- overflow 2-->");
                                len=read(fd,cdb,sizeof(cdb)-1);
                            }
                            cdb[len]=0;
                            ptr2=cdb;
                            recursive=0;
                            do {
                                if(ptr=strchr(ptr2,'|')) *ptr=0;
                                mt_node=(struct match_key *)calloc(sizeof(struct match_key),1);
                                mt_node->mt_kn=node;
                                mt_node->mt_term=1;
                                mt_node->mt_offset=atoi(ptr2);
                                found++;
                                AddTail(match_list,(struct Node *)mt_node);
                                if(*ptr2 && (ptr2=strchr(ptr2,'^'))) {
                                    ptr2++;
                                    if(node->k_type==P_WORD) {
                                        if(node->k_has_altweight) weight=node->k_altweight;
                                        else weight=atoi(ptr2);
                                        if((node->k_spell==1)&&(node->k_name[strlen(node->k_name)-1]!='s')) add_weight(match_list,mt_node->mt_offset,weight/2);
                                        else add_weight(match_list,mt_node->mt_offset,weight);
                                    }
                                }
                                if(*ptr2 && (ptr2=strchr(ptr2,'^'))) {
                                    ptr2++;
                                    mt_node->mt_type=atoi(ptr2);
                                } else mt_node->mt_type=0;
                                ptr2=ptr+1;
                                recursive++;
                            } while(ptr&&(recursive<HASH_LIMIT));
                            /* */
                        }

                    }
                } while(node=(struct key_node *)node->k_node.ln_Succ);
                close(fd);
            } else printf("Content-type: text/html\n\nerror 1\n");

            if(found) {
                /* Retira as NOT_WORDs da lista */
                if(node=(struct key_node *)list->lh_Head)
                    do {
                        if(node->k_type==P_WORD_NOT) {
                            // printf("DEBUG DELETING %s<br>",node->k_name);
                            del_word(match_list,node->k_name);
                        }
                    } while(node=(struct key_node *)node->k_node.ln_Succ);
                /* end retira */

                time(&end); time1=end-start;

                /* Aqui vamos apagar quem se repete nos resultados, deixando sempre o
                 * que o tem maior pontuação na lista e somando-lhe o que foi apagado
                 */

                if(array_rep=calloc(sizeof(struct match_key),found)) {
                    dst=array_rep;
                    if(mt_node=(struct match_key *)match_list->lh_Head)
                        do {
                            memcpy((void *)dst,(void *)mt_node,sizeof(struct match_key));
                            dst+=sizeof(struct match_key);
                        } while(mt_node=(struct match_key *)mt_node->mt_node.ln_Succ);
                }

                qsort((void *)array_rep,found,sizeof(struct match_key),(void *)cmp_rep);

                NewList(match_list);
                dst=array_rep;
                i=found;
                z=0;
                while(i--) {
                    tmp_node=(struct match_key *)dst;
                    if((i>2)&&(next_node=(struct match_key *)(dst+sizeof(struct match_key)))) 
                    {
                        if(tmp_node->mt_offset==next_node->mt_offset) {
                            if((tmp_node->mt_kn!=next_node->mt_kn)&&(next_node->mt_kn->k_spell==0))           {
                                next_node->mt_term+=tmp_node->mt_term;
                            }
                            next_node->mt_weight+=tmp_node->mt_weight*next_node->mt_term;
                        } else { AddTail(match_list,(struct Node *)tmp_node); }
                    } else { AddTail(match_list,(struct Node *)tmp_node); }
                    dst+=sizeof(struct match_key);
                }


                /*
                 * Aqui vamos eliminar as ocorrências que não tenham todas as chaves
                 * AND EXCLUSIVO
                 * , se selcionado
                 */

                found=0;
                if(mt_node=(struct match_key *)match_list->lh_Head)
                    do {
                        next_node=(struct match_key *)mt_node->mt_node.ln_Succ;
                        if(eliminar_or&&(mt_node->mt_term<nterms)) {
                            Remove(mt_node,match_list);
                        } else found++;
                    } while(mt_node=next_node);

                /* Aqui vamos ver se há preferencia por primeiro apontador e dar-lhe um
                 * peso do car&/%$/... hint: Texto Editora
                 */
                if(found) {
                    if((mt_node=(struct match_key *)match_list->lh_Head)&&preference)
                        recursive=0;
                    do {
                        if(mt_node->mt_offset==preference) add_weight(match_list,mt_node->mt_offset,500);
                        recursive++;
                    } while(mt_node=(struct match_key *)mt_node->mt_node.ln_Succ);


                    /* Vamos meter a lista num array para poder ordenar */
                    if(array=calloc(sizeof(struct match_key),found)) {
                        dst=array;
                        if(mt_node=(struct match_key *)match_list->lh_Head)
                            do {
                                if((mt_node->mt_weight)>maxweight) maxweight=mt_node->mt_weight;
                                memcpy((void *)dst,(void *)mt_node,sizeof(struct match_key));
                                dst+=sizeof(struct match_key);
                            } while(mt_node=(struct match_key *)mt_node->mt_node.ln_Succ);
                    }

                    /* E agora ordenar a lista por ordem de PESO */
                    qsort((void *)array,found,sizeof(struct match_key),(void *)cmp_peso);
                    /* E agora ordenar a lista por ordem de TIPO */
                    if(cdb_mode==0) {
                        qsort((void *)array,found,sizeof(struct match_key),(void *)cmp_tipo);
                    }
                }
                /* end ordenar */
            }
            /*
             * Save cache
             */

            if(cache=fopen(cache_name,"w")) {
                fwrite((void *)&maxweight,sizeof(int),1,cache);
                if(found) fwrite((void *)array,sizeof(struct match_key),found,cache);
                fclose(cache);
            }

            /* END nao temos cache vamos trabalhar */
        }
    }

    /* Imprime resultados */
    i=0;
    mmatches=0;
    if(found&&(fd=open(cdb_file2,O_RDONLY))) {
        dst=array;
        do {
            // fprintf(output,"%d<br>\n",found);
            found--;
            mt_node=(struct match_key *)dst;
            mmatches++;
            if((fs<=shown)&&(shown<(fs+20))) {
                len=sh_cdb_obj(mt_node->mt_offset,buf,sizeof(buf),fd);
                buf[len]=0;
                if(i!=mt_node->mt_type) {
                    i=mt_node->mt_type; 
                    if(mt_node->mt_type==10) print_heading(output,"Secções do directório relacionados");
                    if(mt_node->mt_type==20) print_heading(output,"Apontadores relacionados");
                    if(mt_node->mt_type==30) print_heading(output,"Artigos relacionados");
                    if(mt_node->mt_type==40) print_heading(output,"Notícias relacionadas");
                }
                fprint_field(output,buf,mmatches,mt_node->mt_weight,list,maxweight,mt_node->mt_term);
            }
            shown++;
            dst+=sizeof(struct match_key);
        } while(found);
        close(fd);
        /* CDB end */
    } 
    /* end imprime */

    if(mmatches>MAX_RESULTS) mmatches=MAX_RESULTS; 
    /* Não há cá mais do que MAX_RESULTS matches */

    time(&end); time2=end-start-time1;

    if(output) fclose(output);

#ifdef DEBUG
    time(&current); printf("%d segundos passaram - fechei o output file <br>",current-start);
#endif
}

//------------------------------------------------------------------------------

int sh_cdb_obj(int offset,char *output,int sizeof_output,int fd)
{
    int len;
    static char fbuf[40];

    snprintf(fbuf,sizeof(fbuf),"%d",offset);
    if(cdb_seek(fd,fbuf,strlen(fbuf),&len)) {
        if(len<=sizeof_output) return(read(fd,output,len));
        else return(read(fd,output,sizeof_output));
    }
}

void fprint_field(FILE *output,char *out,int match,int weight,struct List *list,int maxweight,int term)
{
    char *ptr2,*ptr3;
    struct apontador aptd;
    int i=0,width;
    struct key_node *node;
    static char headbuf[500];

    memset(&aptd,0,sizeof(aptd));

    ptr2=out;
    do {
        if(ptr3=strchr(ptr2,'\t')) *ptr3=0;
        if(i==0) aptd.tipo=atoi(ptr2);
        if(i==1) aptd.data=ptr2;
        if(i==2) aptd.titulo=ptr2;
        if(i==3) aptd.url=ptr2;
        if(i==4) aptd.descricao=ptr2;
        if(i==5) aptd.html=ptr2;
        if(ptr3) ptr2=ptr3+1;
        i++;
    } while(ptr3);

    if(aptd.url) {
        if(feeling_lucky) {
            if(ffluck) {
                ffluck=0;
                if((aptd.tipo==3)||(aptd.tipo==4)) snprintf(headbuf,sizeof(headbuf),"\n%s",aptd.url);
                else snprintf(headbuf,sizeof(headbuf),"\n/cgi/getid?id=%s",aptd.url);
                new_var(template1,"lucky",headbuf);
            }
            if(aptd.titulo) snprintf(headbuf,sizeof(headbuf),"<option value=%s>%.50s\n",aptd.url,aptd.titulo);
            strcat(luckybuf,headbuf);

            /*
               printf("Location: http://www.sapo.pt/cgi/getid?id=%s\n\n",aptd.url);
               cleanup();
               exit(0);
               */
        } else {
            if (do_mac == 1) fprintf(output,"\n<!-- b -->\n"); /* joaop */
            if((aptd.tipo==30)||(aptd.tipo==40)||(aptd.tipo==10)) fprintf(output,"<a href=\"%s\">",aptd.url);
            else fprintf(output,"<a href=\"/cgi/getid?id=%s\" target=%d%d>",aptd.url,getpid(),match);
        }
    }

    if(!feeling_lucky) {
        if(aptd.titulo&&strlen(aptd.titulo)) { snprintf(headbuf,sizeof(headbuf)-20,"%s",aptd.titulo);
            expand_entities(headbuf);
            if(node=(struct key_node *)list->lh_Head)
                do {
                    if(node->k_type==P_WORD) {
                        htboldng(headbuf,node->k_name);
                    }
                } while(node=(struct key_node *)node->k_node.ln_Succ);
            fprintf(output,"%s</a><br>\n",headbuf);
        }
        else
        {
            fprintf(output,"<i>Sem título</i></a><br>\n");
        }

        switch (aptd.tipo) {
            case 10:
                sprintf(headbuf,"Directório");
                break;
            case 20:
                sprintf(headbuf,"Apontador catalogado");
                break;
            case 30:
                sprintf(headbuf,"Canal Temático");
                break;
            case 40:
                sprintf(headbuf,"Notícia");
                break;
            case 50:
                sprintf(headbuf,"Apontador Indexado");
                break;
        }


        if(aptd.html) {
            //    fprintf(output,"%d <font size=1>%s</font><br>\n",term,aptd.html);
            fprintf(output,"<font size=1>%s</font><br>\n",aptd.html);
            width=(int)((float)((float)weight/(float)maxweight)*(float)50);
            fprintf(output,"<font size=1><img src=\"/images/red2.gif\" height=6 width=%d alt=\"rel %d, %d t\"><img src=\"/images/white.gif\" height=6 width=%d alt=\"score %d\">&nbsp;&nbsp;<i>(%s",width,weight,term,53-width,weight,headbuf);
            if((aptd.tipo==40)) fprintf(output," de %s)</i></font><br>\n",aptd.data);
            else fprintf(output,")</i></font><br>");
        }

        if(aptd.descricao&&(strlen(aptd.descricao))) {
            snprintf(headbuf,sizeof(headbuf)-20,"%s",aptd.descricao);
            expand_entities(headbuf);
            if(node=(struct key_node *)list->lh_Head)
                do {
                    if(node->k_type==P_WORD) htboldng(headbuf,node->k_name);
                } while(node=(struct key_node *)node->k_node.ln_Succ);
            if((aptd.tipo==30)||(aptd.tipo==40)) fprintf(output,"%s (<a href=\"%s\">...</a>)<br>\n",headbuf,aptd.url);
            else fprintf(output,"%s<br>\n",headbuf);
        }
        if(aptd.url) fprintf(output,"<br>\n");
        if (do_mac == 1) fprintf(output,"\n<!-- e -->\n"); /* joaop */
    }

}

del_word(struct List *list,char *word)
{
    struct match_key *node;
    struct match_key *node2;

    if(node=(struct match_key *)list->lh_Head)
        do {
            if(!strcmp(node->mt_kn->k_name,word)) {
                /* apaga todos os nodes com o mesmo offset */
                if(node2=(struct match_key *)list->lh_Head)
                    do {
                        if(node->mt_offset==node2->mt_offset) {
                            Remove(node2,list);
                        }
                    } while(node2=(struct match_key *)node2->mt_node.ln_Succ);
            }
        } while(node=(struct match_key *)node->mt_node.ln_Succ);
}

add_weight(struct List *list,int offset,int weight)
{
    struct match_key *node;

    if(node=(struct match_key *)list->lh_Head)
        do {
            if(node->mt_offset==offset) node->mt_weight+=weight;
        } while(node=(struct match_key *)node->mt_node.ln_Succ);
}

int check_words(struct List *list,char *del)
{
    int mt=0;

    if(node=(struct key_node *)list->lh_Head)
        do {
            if((node->k_type==P_WORD)||(node->k_type==P_WORD_NOT)) {
                if(!strcmp(node->k_name,del)) mt++;
            }
        } while(node=(struct key_node *)node->k_node.ln_Succ);
    return(mt);
}

/* new */
/*
   struct match_key *check_offset(struct match_key *start,struct match_key *del)
   {
   static struct match_key *tmp;
   static struct match_key *run;
   static int mt=0;

   run=start;
   do {
   if(run->mt_offset==del->mt_offset) {
   if(run->mt_weight>del->mt_weight) tmp=del;
   else tmp=mk_node;
   mt++;
   }
   } while(mt<2&&(run=(struct match_key *)run->mt_node.ln_Succ));
   if(mt>=2) return(tmp);
   else return(NULL);
   }
   */

struct match_key *check_offset(struct List *list,struct match_key *del)
{
    struct match_key *tmp;
    int mt=0;

    if(mk_node=(struct match_key *)list->lh_Head)
        do {
            if(mk_node->mt_offset==del->mt_offset) {
                if(mk_node->mt_weight>del->mt_weight) tmp=del;
                else tmp=mk_node;
                mt++;
            }
        } while(mk_node=(struct match_key *)mk_node->mt_node.ln_Succ);
    if(mt>=2) return(tmp);
    else return(NULL);
}

void cleanup(void)
{
}


void print_heading(FILE *fp,char *title)
{
    if(!have_template) {
        fprintf(fp,"<table width=\"300\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=left>");
        fprintf(fp,"<tr><td valign=top align=right>");
        fprintf(fp,"<table border=\"0\" cellpadding=\"2\" cellspacing=\"0\" align=left>");
        fprintf(fp,"<tr>");
        fprintf(fp,"<td width=\"14\" align=\"center\" valign=\"middle\" bgcolor=\"black\">");
        fprintf(fp,"<font size=\"1\" face=\"Arial,Helvetica,Geneva,Swiss,SunSans-Regular\"><span class=\"whitelink\">&gt;&gt;</span></font></td>");
        fprintf(fp,"<td align=\"center\" valign=\"middle\" bgcolor=\"#6699cc\">");
        fprintf(fp,"<center>");
        fprintf(fp,"<font size=\"1\">&nbsp;&nbsp;</font><font color=\"black\" size=\"2\"><b>");
        fprintf(fp,"%s",title);
        fprintf(fp,"</b></font><font size=\"1\">&nbsp;&nbsp;</font>");
        fprintf(fp,"</center>");
        fprintf(fp,"</td>");
        fprintf(fp,"</tr>");
        fprintf(fp,"</table>");
        fprintf(fp,"</td></tr>");
        fprintf(fp,"<tr>");
        fprintf(fp,"<td valign=\"top\" bgcolor=\"black\" width=100%><img height=\"1\" width=\"1\" src=\"/images/pixel_transp.gif\" border=\"0\"></td>");
        fprintf(fp,"</tr>");
        fprintf(fp,"</table><br><br><p align=left><font size=2 face=\"arial,helvetica\">");
    }
    else
    {
        fprintf(fp,"<span class=\"titulobold\">%s</span><br>",title);
        fprintf(fp,"<table width=\"300\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=left>");
        fprintf(fp,"<tr>");
        fprintf(fp,"<td valign=\"top\" bgcolor=\"black\" width=100%><img height=\"1\" width=\"1\" src=\"/images/pixel_transp.gif\" border=\"0\"></td>");
        fprintf(fp,"</tr></table><br>");
    }

}

int cmp_peso(struct match_key *c1,struct match_key *c2)
{
    if(c1->mt_weight < c2->mt_weight) return(1);
    else if(c1->mt_weight == c2->mt_weight) return(0);
    else return(-1);
}

int cmp_tipo(struct match_key *c1,struct match_key *c2)
{
    if(c1->mt_type > c2->mt_type) return(1);
    else if(c1->mt_type == c2->mt_type) return(0);
    else return(-1);
}

int cmp_rep(struct match_key *c1,struct match_key *c2)
{
    if(c1->mt_offset > c2->mt_offset) return(1);
    else if(c1->mt_offset == c2->mt_offset) return(0);
    else return(-1);
}

struct match_key *check_offset_ng(struct match_key *start,struct match_key *del) {
    static struct match_key *tmp;
    static struct match_key *run;
    static int mt=0;

    run=start;
    do {
        if(run->mt_offset==del->mt_offset) {
            if(run->mt_weight>del->mt_weight) tmp=del;
            else tmp=mk_node;
            mt++;
        }
    } while(mt<2&&(run=(struct match_key *)run->mt_node.ln_Succ));
    if(mt>=2) return(tmp);
    else return(NULL);
}


/*
 * Program       : template routines
 * Author        : Celso Martinho (celso@ua.pt)
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
#define FALSE 0
#define TRUE  1
#include <defines.h>
#include "protos.h"
#include "lists.h"
#include "templates.h"
#include "text.h"

struct List *init_template(void)
{
    static struct List *list;
    if(list=(struct List *)calloc(sizeof(struct List),1)) {
        NewList(list);
        return(list);
    }
    return(0);
}

void print_template(struct List *list,char *file)
{
    fprint_template(list,stdout,file);
}

void sprint_template(struct List *list,char *output,char *file)
{
    FILE *fp;
    char buf[2048];
    char buf2[16000];
    char value[VAR_VALUE];
    char *ptr,*oldptr2,*ptr2,*beg;
    int tagopen=0;
    int tag,n;
    int iftable=0;
    char ifarray[MAX_IF_LOOPS];

    ptr=0; ptr2=0; beg=0;
    memset(buf,0,sizeof(buf));
    memset(value,0,sizeof(buf));

    if(fp=fopen(file,"r")) {

        /*
         * Le^ linha por linha
         */

        ifarray[iftable]=1;
        while(fgets(buf,sizeof(buf),fp)) {
            n=strlen(buf);
            if(n>2&&buf[n-2]=='\\') buf[n-2]=0;
            beg=buf;

            /*
             * Se ha' uma tag aberta e aparece "fechar" nesta linha, vamos fechar
             */

            if(tagopen && (ptr=strstr(beg,"-->"))) {
                tagopen=0;
                beg=ptr+3;
            }
            while((tag=search_first_tag(beg,&ptr))&&(!tagopen)) {

                if(tag==TAG_CAT) {
                    tagopen=1;
                    *ptr=0;
                    if(ifarray[iftable]==1) { sprintf(buf2,"%s",beg); strcat(output,buf2); }
                    ptr+=8; /* <!-- VAR length */
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=ptr; while(*ptr2&&strncmp(ptr2,"-->",3)) ptr2++;
                    if(ptr2) { *ptr2=0; ptr2++; }
                    {
                        uid_t olduid;
#define NOBODY 65534
                        FILE *fp;
                        char buf[1024];

                        if(ifarray[iftable]==1) {
                            if(fp=fopen(ptr,"r")) {
                                olduid=getuid();
                                setuid(NOBODY);
                                while(fgets(buf,sizeof(buf),fp)) {
                                    sprintf(buf2,"%s",buf); strcat(output,buf2);
                                }
                                setuid(olduid);
                                fclose(fp);
                            }
                        }
                    }
                    ptr=strchr(ptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                    } else beg=ptr2; /* Malformed line */
                }
                if(tag==TAG_EXEC) {
                    tagopen=1;
                    *ptr=0;
                    if(ifarray[iftable]==1) { sprintf(buf2,"%s",beg); strcat(output,buf2); }
                    ptr+=8; /* <!-- VAR length */
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=ptr; while(*ptr2&&strncmp(ptr2,"-->",3)) ptr2++;
                    if(ptr2) { *ptr2=0; ptr2++; }
                    {
                        uid_t olduid;
#define NOBODY 65534
                        char command[1024];

                        if(ifarray[iftable]==1) {
                            olduid=getuid();
                            setuid(NOBODY);
                            fflush(stdout);
                            system(ptr);
                            setuid(olduid);
                        }
                    }
                    ptr=strchr(ptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                    } else beg=ptr2; /* Malformed line */
                }
                if((tag==TAG_VAR||tag==TAG_REM)) {
                    tagopen=1;
                    *ptr=0;
                    if(ifarray[iftable]==1) { sprintf(buf2,"%s",beg); strcat(output,buf2); }
                    ptr+=7; /* <!-- VAR length */
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=getwhite_or_dash(ptr);
                    if(ptr2) { *ptr2=0; ptr2++; }
                    if(!strstr(beg,"<!--REM")) {
                        get_value(list,ptr,value);
                        if(ifarray[iftable]==1) { sprintf(buf2,"%s",value); strcat(output,buf2); }
                    }
                    ptr=strchr(ptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                    } else beg=ptr2; /* Malformed line */
                }
                if(tag==TAG_IF) {
                    tagopen=1;
                    *ptr=0;
                    if(ifarray[iftable]==1) { sprintf(buf2,"%s",beg); strcat(output,buf2); }
                    ptr+=6;
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=ptr; while(*ptr2!='-'&&*ptr2) ptr2++;
                    if(ptr2) { *ptr2=0; ptr2++; }
                    oldptr2=ptr2;

                    /*
                     * Analizar condicao aqui. iftable++ SE TRUE
                     */
                    {
                        char var[256];
                        char tbuf[256];
                        int operator,len,val_type,nvar,nval;
                        char value[256];
                        int result=0;

                        txpack(ptr);
                        memset(tbuf,0,sizeof(tbuf));

                        /* var */
                        ptr2=ptr; while(*ptr2!='<'&&*ptr2!='>'&&*ptr2!='='&&*ptr2!='!'&&*ptr2!=' '&&*ptr2) ptr2++;
                        strncpy(tbuf,ptr,ptr2-ptr);
                        get_value(list,tbuf,var);
                        if(*ptr2==' ') ptr2++;

                        /* operator */
                        ptr2++;
                        if(*ptr2=='=') len=2; else len=1;
                        ptr2--;
                        operator=HIGHER_THAN;
                        if((len==1)&&(!strncmp(ptr2,">",len))) operator=HIGHER_THAN;
                        if((len==1)&&(!strncmp(ptr2,"<",len))) operator=LOWER_THAN;
                        if((len==1)&&(!strncmp(ptr2,"=",len))) operator=EQUAL;
                        if((len==2)&&(!strncmp(ptr2,"==",len))) operator=EQUAL;
                        if((len==2)&&(!strncmp(ptr2,"!=",len))) operator=DIFERENT;
                        if((len==2)&&(!strncmp(ptr2,">=",len))) operator=HIGHER_EQUAL;
                        if((len==2)&&(!strncmp(ptr2,"<=",len))) operator=LOWER_EQUAL;

                        /* value */
                        ptr2+=len;
                        if(*ptr2==' ') ptr2++;
                        if(*ptr2=='"') {
                            val_type=TEXT;
                            ptr2++;
                            if(ptr=strchr(ptr2,'"')) *ptr=0;
                            else { ptr=getwhite_or_dash(ptr2); if(ptr) *ptr=0; }
                        }
                        else
                        {
                            val_type=NUMERICAL;
                            ptr=getwhite_or_dash(ptr2);
                            if(ptr) *ptr=0;
                        }
                        strcpy(value,ptr2);

                        if(val_type==NUMERICAL) {
                            nval=atoi(value);
                            nvar=atoi(var);
                            if(operator==HIGHER_THAN&&(nvar>nval)) result=1;
                            if(operator==LOWER_THAN&&(nvar<nval)) result=1;
                            if(operator==EQUAL&&(nvar==nval)) result=1;
                            if(operator==DIFERENT&&(nvar!=nval)) result=1;
                            if(operator==HIGHER_EQUAL&&(nvar>=nval)) result=1;
                            if(operator==LOWER_EQUAL&&(nvar<=nval)) result=1;
                        }
                        else
                        {
                            if(operator==EQUAL&&(!strcmp(var,value))) result=1;
                            if(operator==DIFERENT&&(strcmp(var,value))) result=1;
                        }

                        iftable++;
                        if(iftable>=MAX_IF_LOOPS) { printf("FATAL ERROR: TOO MANY IF/ENDIFs\n\n\n"); exit(0); }
                        if(!result) ifarray[iftable]=0;
                        else if(ifarray[iftable-1]!=0) ifarray[iftable]=1;
                    }
                    /*
                     * End ana'lise
                     */

                    ptr=strchr(oldptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                    } else beg=oldptr2; /* Malformed line */
                }

                if(tag==TAG_ENDIF) {
                    tagopen=1;
                    *ptr=0;
                    ptr+=6;
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=getwhite_or_dash(ptr);
                    if(ptr2) { *ptr2=0; ptr2++; }
                    ptr=strchr(ptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                        if(iftable>0) iftable--; /* So' decrementa se estiver aberto */
                    } else beg=ptr2; /* Malformed line */
                }

            }

            /*
             * Se nao ha' TAG e se os TAGs estao todos fechados, imprime a linha AS IS
             */

            if((!tagopen)&&(ifarray[iftable]==1)) { sprintf(buf2,"%s",beg); strcat(output,buf2); }
        }
        fclose(fp);
    }
    tagopen=0;
}

void fprint_template(struct List *list,FILE *fptr,char *file)
{
    FILE *fp;
    char buf[2048];
    char value[VAR_VALUE];
    char *ptr,*oldptr2,*ptr2,*beg;
    int tagopen=0;
    int tag,n;
    int iftable=0;
    char ifarray[MAX_IF_LOOPS];

    ptr=0; ptr2=0; beg=0;
    memset(buf,0,sizeof(buf));
    memset(value,0,sizeof(buf));

    if(fp=fopen(file,"r")) {

        /*
         * Le^ linha por linha
         */

        ifarray[iftable]=1;
        while(fgets(buf,sizeof(buf),fp)) {
            n=strlen(buf);
            if(n>2&&buf[n-2]=='\\') buf[n-2]=0;
            beg=buf;

            /*
             * Se ha' uma tag aberta e aparece "fechar" nesta linha, vamos fechar
             */

            if(tagopen && (ptr=strstr(beg,"-->"))) {
                tagopen=0;
                beg=ptr+3;
            }
            while((tag=search_first_tag(beg,&ptr))&&(!tagopen)) {

                if(tag==TAG_CAT) {
                    tagopen=1;
                    *ptr=0;
                    if(ifarray[iftable]==1) fprintf(fptr,"%s",beg);
                    ptr+=8; /* <!-- VAR length */
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=ptr; while(*ptr2&&strncmp(ptr2,"-->",3)) ptr2++;
                    if(ptr2) { *ptr2=0; ptr2++; }
                    {
                        uid_t olduid;
#define NOBODY 65534
                        FILE *fp;
                        char buf[1024];

                        if(ifarray[iftable]==1) {
                            if(fp=fopen(ptr,"r")) {
                                olduid=getuid();
                                setuid(NOBODY);
                                while(fgets(buf,sizeof(buf),fp)) {
                                    fprintf(fptr,"%s",buf);
                                }
                                setuid(olduid);
                                fclose(fp);
                            }
                        }
                    }
                    ptr=strchr(ptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                    } else beg=ptr2; /* Malformed line */
                }
                if(tag==TAG_EXEC) {
                    tagopen=1;
                    *ptr=0;
                    if(ifarray[iftable]==1) fprintf(fptr,"%s",beg);
                    ptr+=8; /* <!-- VAR length */
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=ptr; while(*ptr2&&strncmp(ptr2,"-->",3)) ptr2++;
                    if(ptr2) { *ptr2=0; ptr2++; }
                    {
                        uid_t olduid;
#define NOBODY 65534
                        char command[1024];

                        if(ifarray[iftable]==1) {
                            olduid=getuid();
                            setuid(NOBODY);
                            fflush(stdout);
                            system(ptr);
                            setuid(olduid);
                        }
                    }
                    ptr=strchr(ptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                    } else beg=ptr2; /* Malformed line */
                }
                if((tag==TAG_VAR||tag==TAG_REM)) {
                    tagopen=1;
                    *ptr=0;
                    if(ifarray[iftable]==1) fprintf(fptr,"%s",beg);
                    ptr+=7; /* <!-- VAR length */
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=getwhite_or_dash(ptr);
                    if(ptr2) { *ptr2=0; ptr2++; }
                    if(!strstr(beg,"<!--REM")) {
                        get_value(list,ptr,value);
                        if(ifarray[iftable]==1) fprintf(fptr,"%s",value);
                    }
                    ptr=strchr(ptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                    } else beg=ptr2; /* Malformed line */
                }
                if(tag==TAG_IF) {
                    tagopen=1;
                    *ptr=0;
                    if(ifarray[iftable]==1) fprintf(fptr,"%s",beg);
                    ptr+=6;
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=ptr; while(*ptr2!='-'&&*ptr2) ptr2++;
                    if(ptr2) { *ptr2=0; ptr2++; }
                    oldptr2=ptr2;

                    /*
                     * Analizar condicao aqui. iftable++ SE TRUE
                     */
                    {
                        char var[256];
                        char tbuf[256];
                        int operator,len,val_type,nvar,nval;
                        char value[256];
                        int result=0;

                        txpack(ptr);
                        memset(tbuf,0,sizeof(tbuf));

                        /* var */
                        ptr2=ptr; while(*ptr2!='<'&&*ptr2!='>'&&*ptr2!='='&&*ptr2!='!'&&*ptr2!=' '&&*ptr2) ptr2++;
                        strncpy(tbuf,ptr,ptr2-ptr);
                        get_value(list,tbuf,var);
                        if(*ptr2==' ') ptr2++;

                        /* operator */
                        ptr2++;
                        if(*ptr2=='=') len=2; else len=1;
                        ptr2--;
                        operator=HIGHER_THAN;
                        if((len==1)&&(!strncmp(ptr2,">",len))) operator=HIGHER_THAN;
                        if((len==1)&&(!strncmp(ptr2,"<",len))) operator=LOWER_THAN;
                        if((len==1)&&(!strncmp(ptr2,"=",len))) operator=EQUAL;
                        if((len==2)&&(!strncmp(ptr2,"==",len))) operator=EQUAL;
                        if((len==2)&&(!strncmp(ptr2,"!=",len))) operator=DIFERENT;
                        if((len==2)&&(!strncmp(ptr2,">=",len))) operator=HIGHER_EQUAL;
                        if((len==2)&&(!strncmp(ptr2,"<=",len))) operator=LOWER_EQUAL;

                        /* value */
                        ptr2+=len;
                        if(*ptr2==' ') ptr2++;
                        if(*ptr2=='"') {
                            val_type=TEXT;
                            ptr2++;
                            if(ptr=strchr(ptr2,'"')) *ptr=0;
                            else { ptr=getwhite_or_dash(ptr2); if(ptr) *ptr=0; }
                        }
                        else
                        {
                            val_type=NUMERICAL;
                            ptr=getwhite_or_dash(ptr2);
                            if(ptr) *ptr=0;
                        }
                        strcpy(value,ptr2);

                        if(val_type==NUMERICAL) {
                            nval=atoi(value);
                            nvar=atoi(var);
                            if(operator==HIGHER_THAN&&(nvar>nval)) result=1;
                            if(operator==LOWER_THAN&&(nvar<nval)) result=1;
                            if(operator==EQUAL&&(nvar==nval)) result=1;
                            if(operator==DIFERENT&&(nvar!=nval)) result=1;
                            if(operator==HIGHER_EQUAL&&(nvar>=nval)) result=1;
                            if(operator==LOWER_EQUAL&&(nvar<=nval)) result=1;
                        }
                        else
                        {
                            if(operator==EQUAL&&(!strcmp(var,value))) result=1;
                            if(operator==DIFERENT&&(strcmp(var,value))) result=1;
                        }

                        iftable++;
                        if(iftable>=MAX_IF_LOOPS) { printf("FATAL ERROR: TOO MANY IF/ENDIFs\n\n\n"); exit(0); }
                        if(!result) ifarray[iftable]=0;
                        else if(ifarray[iftable-1]!=0) ifarray[iftable]=1;
                    }
                    /*
                     * End ana'lise
                     */

                    ptr=strchr(oldptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                    } else beg=oldptr2; /* Malformed line */
                }

                if(tag==TAG_ENDIF) {
                    tagopen=1;
                    *ptr=0;
                    ptr+=6;
                    if(*ptr==' ') ptr=runwhite(ptr);
                    ptr2=getwhite_or_dash(ptr);
                    if(ptr2) { *ptr2=0; ptr2++; }
                    ptr=strchr(ptr2,'>');
                    if(ptr) {
                        tagopen=0;
                        ptr++;
                        beg=ptr;
                        if(iftable>0) iftable--; /* So' decrementa se estiver aberto */
                    } else beg=ptr2; /* Malformed line */
                }

            }

            /*
             * Se nao ha' TAG e se os TAGs estao todos fechados, imprime a linha AS IS
             */

            if((!tagopen)&&(ifarray[iftable]==1)) fprintf(fptr,"%s",beg);
        }
        fclose(fp);
    }
    tagopen=0;
}

void get_value(struct List *list,char *title,char *value)
{
    struct var_node *node;

    if(node=(struct var_node *)list->lh_Head) {
        *value=0;
        do {
            if(!strcmp(node->v_name,title)) {
                strcpy(value,node->v_value);
                return;
            }
        } while(node=(struct var_node *)node->v_node.ln_Succ);
    }
}

void end_template(struct List *list)
{
    struct var_node *node;
    struct var_node *pnode;

    if(node=(struct var_node *)list->lh_Head) {
        do {
            pnode=node;
            node=(struct var_node *)node->v_node.ln_Succ;
            free((void *)pnode);
        } while(node);
    }
    free(list);
}

void new_var(struct List *list,char *name,char *value)
{
    struct var_node *nod;
    nod=(struct var_node *)calloc(sizeof(struct var_node),1);
    strcpy(nod->v_name,name);
    strcpy(nod->v_value,value);
    AddTail(list,(struct Node *)nod);
}

int search_first_tag(char *line,char **start)
{
    char *ptr,*old;
    int ret=TAG_NONE;

    old=strstr(line,"<!--");
    if(!old) {
        *start=0;
        return(ret);
    }
    old+=4;
    if(!strncmp(old,"VAR",3)) ret=TAG_VAR;
    if(!strncmp(old,"REM",3)) ret=TAG_REM;
    if(!strncmp(old,"IF",2)) ret=TAG_IF;
    if(!strncmp(old,"ENDIF",5)) ret=TAG_ENDIF;
    if(!strncmp(old,"EXEC",4)) ret=TAG_EXEC;
    if(!strncmp(old,"CAT",3)) ret=TAG_CAT;
    *start=old-4;
    return(ret);
}

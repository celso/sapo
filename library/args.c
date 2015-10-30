/*
 *
 * Program       : args.c
 * Author        : Celso Martinho (celso@ua.pt)
 * Last Modified : 13-Feb-1995
 * Version       : 0.90
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "protos.h"
#include "args.h"
#define FALSE 0
#define TRUE  1

#undef NULL
#define NULL 0

char output[1000];

int getarg(char *ID,char *line,struct linearg *args)
{
    char *myptr;
    char Directive[20];

    memset(args,0,sizeof(struct linearg));
    memset(Directive,0,sizeof(Directive));

    if(strlen(line)<4) return(FALSE);
    if(*line=='#') return(FALSE);

    if(*line) {
        myptr=line;
        while(*line&&(*line!=' '&&*line!='\t'&&*line!='\n')) line++;
        *line=0;
        strncpy(Directive,myptr,line-myptr);
        line++;
        while(*line&&(*line=='\t'||*line==' ')) line++;
    }

#ifdef DEBUG
    printf("getarg(): Directive=[%s]\n",Directive);
#endif
    if(strcmp(ID,Directive)) return FALSE;

    if(*line) {
        line++;
        myptr=line;
        while(*line&&(*line!='\"')) line++;
        *line=NULL;
        strncpy(args->arg_1,myptr,line-myptr);
        line++;
        while(*line&&(*line=='\t'||*line==' ')) line++;
    }

#ifdef DEBUG
    printf("getarg(): arg_1=[%s]\n",args->arg_1);
#endif

    if(*line) {
        line++;
        myptr=line;
        while(*line&&(*line!='\"')) line++;
        *line=NULL;
        strncpy(args->arg_2,myptr,line-myptr);
        line++;
        while(*line&&(*line=='\t'||*line==' ')) line++;
    }

#ifdef DEBUG
    printf("getarg(): arg_2=[%s]\n",args->arg_2);
#endif

    if(*line) {
        line++;
        myptr=line;
        while(*line&&(*line!='\"')) line++;
        *line=NULL;
        strncpy(args->arg_3,myptr,line-myptr);
        line++;
        while(*line&&(*line=='\t'||*line==' ')) line++;
    }

#ifdef DEBUG
    printf("getarg(): arg_3=[%s]\n",args->arg_3);
#endif

    if(*line) {
        line++;
        myptr=line;
        while(*line&&(*line!='\"')) line++;
        *line=NULL;
        strncpy(args->arg_4,myptr,line-myptr);
        line++;
        while(*line&&(*line=='\t'||*line==' ')) line++;
    }

#ifdef DEBUG
    printf("getarg(): arg_4=[%s]\n",args->arg_4);
#endif

    if(*line) {
        line++;
        myptr=line;
        while(*line&&(*line!='\"')) line++;
        *line=NULL;
        strncpy(args->arg_5,myptr,line-myptr);
        line++;
        while(*line&&(*line=='\t'||*line==' ')) line++;
    }

#ifdef DEBUG
    printf("getarg(): arg_5=[%s]\n",args->arg_5);
#endif

    if(*line) {
        line++;
        myptr=line;
        while(*line&&(*line!='\"')) line++;
        *line=NULL;
        strncpy(args->arg_6,myptr,line-myptr);
        line++;
        while(*line&&(*line=='\t'||*line==' ')) line++;
    }

#ifdef DEBUG
    printf("getarg(): arg_6=[%s]\n",args->arg_6);
#endif

    if(*line) {
        line++;
        myptr=line;
        while(*line&&(*line!='\"')) line++;
        *line=NULL;
        strncpy(args->arg_7,myptr,line-myptr);
        line++;
        while(*line&&(*line=='\t'||*line==' ')) line++;
    }

#ifdef DEBUG
    printf("getarg(): arg_7=[%s]\n",args->arg_7);
#endif

    if(*line) {
        line++;
        myptr=line;
        while(*line&&(*line!='\"')) line++;
        *line=NULL;
        strncpy(args->arg_8,myptr,line-myptr);
        line++;
        while(*line&&(*line=='\t'||*line==' ')) line++;
    }

#ifdef DEBUG
    printf("getarg(): arg_8=[%s]\n",args->arg_8);
#endif

    return(TRUE);
}

int check_flag(char *flag,char *confname)
{
    FILE *conf;
    char buffer[4096];
    struct linearg args;

    if(conf=fopen(confname,"r")) {
        memset(buffer,0,sizeof(buffer));
        while(fgets(buffer,sizeof(buffer),conf)) {
            if(getarg(flag,buffer,&args)) { fclose(conf); return(TRUE); }
            memset(buffer,0,sizeof(buffer));
        }
        fclose(conf);
    }
    return(FALSE);
}

int get_flag(char *flag,char *confname,char *output)
{
    FILE *conf;
    char buffer[4096];
    static struct linearg args;

    if(conf=fopen(confname,"r")) {
        memset(buffer,0,sizeof(buffer));
        while(fgets(buffer,sizeof(buffer),conf)) {
            if(getarg(flag,buffer,&args)) {
                fclose(conf);
                strcpy(output,args.arg_1);
                return(TRUE);
            }
            memset(buffer,0,sizeof(buffer));
        }
        fclose(conf);
    } else printf("get_flag: Failed to open config file\n");
    return(FALSE);
}

int parse_htargs_hard(char *flag,char *value)
{
    char *ptr1;
    char *ptr2;
    char *ptr3;
    char buf[16034];
    char args[4096];
    int n;

    if(!getenv("REQUEST_METHOD")) return(0);
    if(!strcmp(getenv("REQUEST_METHOD"),"GET")) {
        strcpy(args,getenv("QUERY_STRING"));
    }
    else
        if(!strcmp(getenv("REQUEST_METHOD"),"POST")) {
            memset(args,0,sizeof(args));
            fseek(stdin,0,SEEK_SET);
            fread(args,1,(size_t)atoi(getenv("CONTENT_LENGTH")),stdin);
        }
        else return(0); /* Unknown/Unsupported request method */

    if(!args) return(0);
    strcpy(buf,args);
    ptr3=buf+strlen(buf);

    ptr1=buf;
    while(*ptr1) {
        if(*ptr1=='&') *ptr1=NULL;
        ptr1++;
    }

    ptr1=buf;
    n=1;
    while(n) {
        char tmp[256];

        memset(tmp,0,sizeof(tmp));
        strcpy(tmp,ptr1);
        ptr2=tmp;
        while(*ptr2) {
            if(*ptr2=='=') *ptr2=NULL;
            ptr2++;
        }

        if(!memcmp(tmp,flag,strlen(tmp))) {
            ptr2=tmp;
            while(*ptr2) ptr2++;
            ptr2++;
            strcpy(value,ptr2);
            /*    win2iso(value); */
            return(1);
        }

        while(*ptr1) ptr1++;
        if(ptr1==ptr3) return(0); else ptr1++;
    }
    return(0);
}

int parse_htargs(char *flag,char *value)
{
    char *ptr1;
    char *ptr2;
    char *ptr3;
    char buf[16034];
    char args[4096];
    char method[60];
    int n;

    if(!getenv("REQUEST_METHOD")) return(0);
    if(getenv("REQUEST_METHOD")) strcpy(method,getenv("REQUEST_METHOD"));
    else method[0]=0;

    if(!strcmp(method,"GET")) {
        strcpy(args,getenv("QUERY_STRING"));
    }
    else
        if(!strcmp(method,"POST")) {
            memset(args,0,sizeof(args));
            fseek(stdin,0,SEEK_SET);
            fread(args,1,(size_t)atoi(getenv("CONTENT_LENGTH")),stdin);
        }
        else {
            return(0); /* Unknown/Unsupported request method */
        }

    if(!args) {*value=0; return(0);}
    strcpy(buf,args);
    ptr3=buf+strlen(buf);

    ptr1=buf;
    while(*ptr1) {
        if(*ptr1=='&') *ptr1=NULL;
        ptr1++;
    }

    ptr1=buf;
    n=1;
    while(n) {
        char tmp[256];

        memset(tmp,0,sizeof(tmp));
        strcpy(tmp,ptr1);
        ptr2=tmp;
        while(*ptr2) {
            if(*ptr2=='=') *ptr2=NULL;
            ptr2++;
        }

        if(!memcmp(tmp,flag,strlen(tmp))) {
            ptr2=tmp;
            while(*ptr2) ptr2++;
            ptr2++;
            strcpy(value,ptr2);
            win2iso(value);
            return(1);
        }

        while(*ptr1) ptr1++;
        if(ptr1==ptr3) {*value=0; return(0);} else ptr1++;

    }
    return(0);
}

int check_htarg(char *flag,char *value)
{
    char buffer[256];

    memset(buffer,0,sizeof(buffer));
    parse_htargs(flag,buffer);
    if(!strlen(buffer)) return(0);
    if(!strcmp(buffer,value)) return (1); else return(0);
}

char *tohidden_ptr(char *args)
{
    char *ptr1;
    char *ptr2;
    char *ptr3;
    char buf[16034];
    char buf2[1000];
    char value[1024];
    int n;

    if(!args) return;
    strcpy(buf,args);
    ptr3=buf+strlen(buf);

    ptr1=buf;
    while(*ptr1) {
        if(*ptr1=='&') *ptr1=NULL;
        ptr1++;
    }

    ptr1=buf;
    n=1;

    memset(output,0,sizeof(output));

    while(n) {
        char tmp[256];

        memset(tmp,0,sizeof(tmp));
        strcpy(tmp,ptr1);
        ptr2=tmp;
        while(*ptr2) {
            if(*ptr2=='=') *ptr2=NULL;
            ptr2++;
        }

        ptr2=tmp;
        while(*ptr2) ptr2++;
        ptr2++;
        strcpy(value,ptr2);
        win2iso(value);
        sprintf(buf2,"<input type=hidden name=\"%s\" value=\"%s\">\n",tmp,value);
        strcat(output,buf2);

        while(*ptr1) ptr1++;
        if(ptr1==ptr3) return(output); else ptr1++;

    }
    return(output);
}

void tohidden(char *args)
{
    char *ptr1;
    char *ptr2;
    char *ptr3;
    char buf[16034];
    char value[1024];
    int n;

    if(!args) return;
    strcpy(buf,args);
    ptr3=buf+strlen(buf);

    ptr1=buf;
    while(*ptr1) {
        if(*ptr1=='&') *ptr1=NULL;
        ptr1++;
    }

    ptr1=buf;
    n=1;
    while(n) {
        char tmp[256];

        memset(tmp,0,sizeof(tmp));
        strcpy(tmp,ptr1);
        ptr2=tmp;
        while(*ptr2) {
            if(*ptr2=='=') *ptr2=NULL;
            ptr2++;
        }

        ptr2=tmp;
        while(*ptr2) ptr2++;
        ptr2++;
        strcpy(value,ptr2);
        win2iso(value);
        printf("<input type=hidden name=\"%s\" value=\"%s\">",tmp,value);

        while(*ptr1) ptr1++;
        if(ptr1==ptr3) return; else ptr1++;

    }
    return;
}


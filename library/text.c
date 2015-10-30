/*
 * Program       : text.c
 * Author        : Celso Martinho
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"
#include "protos.h"
#define FALSE 0
#define TRUE  1
#include "text.h"

#undef NULL
#define NULL 0

static char outstr[256];

format_text(char *str)
{
    static char old[TX_BUFSIZE];
    static char *ptr,*find;   
    static unsigned int wordsize;
    static unsigned int line;

    strcpy(old,str);
    ptr=old;
    memset(str,0,TX_BUFSIZE);
    line=0;

    strcat(str,"             ");
    while(strlen(ptr)) {
        if(find=strchr(ptr,' ')) {
            wordsize=find-ptr+1;
            strncat(str,ptr,wordsize);
            ptr+=wordsize;
            line+=wordsize;
            if(line>50) {
                line=0;
                find=str+strlen(str);
                find--;
                *find='\n';
                strcat(str," ");
            }
        } else { strcat(str,ptr); break; }
    }
}

void lower(char *str)
{
    while(*str) {
        *str=tolower(*str); 
        str++;
    }
}

void upper(char *str)
{
    while(*str) {
        *str=toupper(*str); 
        str++;
    }
}

char *runwhite(char *start)
{
    while(*start=='\t'||*start==' ') start++;
    return(start);
}

char *getwhite(char *start)
{
    while(*start!='\t'&&*start!=' '&&*start) start++;
    return(start);
}

char *getwhite_or_dash(char *start)
{
    while(*start!='\t'&&*start!=' '&&*start!='-'&&*start) start++;
    return(start);
}

/* Basa com os espacos, \ts e CRs a mais num buffer */

txpack(char *text)
{
    char *ptr1,*ptr2;

    while(*text) {
        ptr1=text+1;
        if(*ptr1&&((*text==' '||*text=='\t'||*text==0xa)&&(*ptr1==' '||*ptr1=='\t'||*ptr1==0xa))) {
            memcpy(text,ptr1,strlen(ptr1)+1);
        } else text++;
    }
}

substitute(char *buffer,char *arg1,char *arg2)
{
    char *ptr1,*ptr2;
    char tmp[TX_BUFSIZE];

    ptr2=buffer;
    while(ptr1=strstr(ptr2,arg1)) {
        ptr2=ptr1+strlen(arg1);
        strcpy(tmp,ptr2);
        memset(ptr1,0,strlen(arg2)+1);
        strcat(ptr1,arg2);
        ptr2=buffer+strlen(buffer);
        strcat(ptr1,tmp);
    }
}

print_fileq(char *file)
{
    FILE *fp;
    char buffer[16000];

    if(fp=fopen(file,"r")) {
        while(fgets(buffer,sizeof(buffer),fp)) {
            printf("%s",buffer);
        }
        fclose(fp);
    }
}

print_file(char *file)
{
    FILE *fp;
    char buffer[16000];

    if(fp=fopen(file,"r")) {
        while(fgets(buffer,sizeof(buffer),fp)) {
            printf("%s",buffer);
        }
        fclose(fp);
    } else printf("ERROR: couldn't open %s for reading.\n",file);
}

fprint_file(char *file,FILE *dest)
{
    FILE *fp;
    char buffer[16000];

    if(fp=fopen(file,"r")) {
        while(fgets(buffer,sizeof(buffer),fp)) {
            fprintf(dest,"%s",buffer);
        }
        fclose(fp);
    } else printf("ERROR: couldn't open %s for reading.\n",file);
}

char *str(int value)
{
    memset(outstr,0,sizeof(outstr));
    snprintf(outstr,sizeof(outstr),"%d",value);
    return(outstr);
}

void strip_crs(char *text)
{
    char *ptr;

    ptr=text;
    while(*ptr) {
        if(*ptr=='\n' || *ptr=='\r') *ptr=' ';
        ptr++;
    }
}

/* Copy the string formed by two pointers (one on the beginning, other
 *    on the char after the last char) to a new, malloc-ed location.
 *       0-terminate it.  */
    char *
strdupdelim (const char *beg, const char *end)
{
    char *res = (char *)malloc (end - beg + 1);
    memcpy (res, beg, end - beg);
    res[end - beg] = '\0';
    return res;
}

int allow_c(char *buf,char *chars)
{
    char *ptr1,*ptr2;
    int ret=0,ok;

    ptr1=buf;
    while(*ptr1) {
        ptr2=chars;
        ok=0;
        while(*ptr2) {
            if(*ptr1==*ptr2) ok=1;
            ptr2++;
        }
        if(ok==0) { ret=*ptr1; *ptr1='_'; }
        ptr1++;
    }
    return(ret);
}


void kill_c(char *buf,char *chars)
{
    char *ptr1,*ptr2;
    int ret=0,ok;

    ptr1=buf;
    while(*ptr1) {
        ptr2=chars;
        ok=0;
        while(*ptr2) {
            if(*ptr1==*ptr2) *ptr1='_';
            ptr2++;
        }
        if(!ok) 
            ptr1++;
    }
}


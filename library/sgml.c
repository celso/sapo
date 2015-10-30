/*
 *
 * Program       : sgml.c
 * Author        : Celso Martinho (celso@ua.pt)
 * Last Modified : 13-Feb-1995
 * Version       : 0.90
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protos.h"
#include "sgml.h"
#define FALSE 0
#define TRUE  1
char *strstrng(char *buffer,char *key,int len);

int strip2ascii(char *str)
{
    int a, ret=0;

    while(*str) {
        for(a=0;a<ISO_SIMBOLS;a++) {
            if(*str==isotable[a].iso) { *str=isotable[a].ascii; ret++; }
        }
        str++;
    }
    return(ret);
}

strip_html(char *str)
{
    int a;

    while(*str) {
        if(*str=='<') {
            while(*str && *str!='>') {
                memcpy(str,str+1,strlen(str));
            }
            memcpy(str,str+1,strlen(str));
        } else str++;
    }
}

expand_entities(char *str)
{
    char *tmp_ptr1,*tmp_ptr2;
    char entity[20];
    int a;

    while(tmp_ptr1=strchr(str,'&')) {
        if(tmp_ptr2=strchr(tmp_ptr1,';')) {
            memset(entity,0,20); /* Better this way... */
            if(tmp_ptr2-tmp_ptr1<=20) strncpy(entity,tmp_ptr1+1,tmp_ptr2-tmp_ptr1-1);
            for(a=0;a<HTML_ENTITIES;a++) {
                if(!strcmp(entities[a],entity)) {
                    strcpy(tmp_ptr1,ISO_Latin1[a]);
                    strcpy(tmp_ptr1+strlen(ISO_Latin1[a]),tmp_ptr2+1);
                    break;
                }
            }
        }
        str=tmp_ptr1+1;
    }
}

win2iso(char *str)
{
    char value;
    char *ptr;

    while(*str) {
        if(*str=='%') {
            ptr=str;
            ptr++;
            if(*ptr>='0'&&*ptr<='9') value=((*ptr-'0')<<4)&0xF0;
            else {
                *ptr=tolower(*ptr);
                value=((*ptr-'a'+10)<<4)&0xF0;
            }
            ptr++;
            if(*ptr>='0'&&*ptr<='9') value=((*ptr-'0')&0x0F)|value;
            else {
                *ptr=tolower(*ptr);
                value=((*ptr-'a'+10)&0x0F)|value;
            }
            *str=(char)value;
            strcpy(str+1,str+3);
        } else {
            if(*str=='+') *str=' ';
        }
        str++;
    }
}

dec2iso(char *str)
{
    char value;
    char *ptr,*in,*t;

    while(*str) {
        if(*str=='&') {
            in=str;
            str++;
            if(*str=='#') {
                str++;
                value=atoi(str);
                if(t=strchr(str,';')) {
                    memcpy(in,t,strlen(t)+1);
                    *in=value;
                }
            }
        }
        str++;
    }
}

iso2html(char *old,char *new)
{
    char *ptr;       
    char letra;
    int a;

    ptr=old; 
    while(*ptr) {
        *new=*ptr;
        for(a=0;a<HTML_ENTITIES;a++) {
            if(*ptr==ISO_Latin1_new[a]) {
                *new='&';
                new++;
                strcpy(new,entities[a]);
                new=new+strlen(entities[a]);
                *new=';';
                break;
            }
        }
        new++;
        ptr++;
    }
}


tocgi(char *str)
{
    while(*str) { if(*str==' ') *str='+'; str++; }
}

htboldng(char *buffer,char *key)
{
    char *ptr1,*ptr2;
    int offset;
    int len;

    len=strlen(key);
    if(ptr1=strstrng(buffer,key,strlen(buffer))) {
        ptr2=ptr1+len;
        if((*ptr2<'A'||(*ptr2>'Z'&&*ptr2<'a')||*ptr2>'z')||*ptr2==0) {
            memmove(ptr1+3,ptr1,strlen(ptr1)+1);
            *ptr1++='<';
            *ptr1++='b';
            *ptr1++='>';
            ptr1+=len;
            memmove(ptr1+4,ptr1,strlen(ptr1)+1);
            *ptr1++='<';
            *ptr1++='/';
            *ptr1++='b';
            *ptr1='>';
        }
    } 
    return;
}

char *strstrng(char *buffer,char *key,int len)
{
    static char *nb;
    char *ptr;
    static char *ret;
    int i;

    ret=NULL;
    if(nb=calloc(len+1,1)) {
        memcpy(nb,buffer,len+1);
        lower(nb);
        strip2ascii(nb);
        if(ptr=strstr(nb,key)) {
            ret=buffer+(ptr-nb);
        }
        free(nb);
    } 
    return(ret);
}



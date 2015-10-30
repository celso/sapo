/*
 * Program       : ftpweb.c
 * Author        : Celso Martinho (celso@ua.pt)
 */

#ifdef SUP_FTPWEB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ftpweb.h"
#include "protos.h"
#define FALSE 0
#define TRUE  1
#define SMALL_BUFFER 1024
#define BIG_BUFFER 1024*8

#undef NULL
#define NULL 0

int getfiledesc(char *path,char *desc)
{
    char dir[SMALL_BUFFER];
    char file[SMALL_BUFFER];
    char buffer[BIG_BUFFER];
    char *ptr1,*ptr2;
    FILE *descfile;

    memset(dir,0,sizeof(dir));
    memset(file,0,sizeof(file));
    if(!(ptr1=strchr(path,'/'))) strcpy(file,path); /* No dir supplied */
    else
    {
        ptr1++;
        while(ptr2=strchr(ptr1,'/')) { ptr2++; ptr1=ptr2; }
        strcpy(file,ptr1);
        strncpy(dir,path,ptr1-path);
    }
    if(chdir(dir)) { printf("ERROR: Couldn't change to directory %s\n",dir); return(0); }

    /* Winsock/Simtelnet mirrors */

    if(descfile=fopen("00_index.txt","r")) {
        while(fgets(buffer,sizeof(buffer),descfile)) {
            if(!strncmp(buffer,file,strlen(file))) {
                buffer[strlen(buffer)-1]=NULL;
                ptr1=buffer;
                ptr1=getwhite(ptr1);
                ptr1=runwhite(ptr1);
                ptr1=getwhite(ptr1);
                ptr1=runwhite(ptr1);
                ptr1=getwhite(ptr1);
                ptr1=runwhite(ptr1);
                ptr1=getwhite(ptr1);
                ptr1=runwhite(ptr1);
                strcpy(desc,ptr1);
                fclose(descfile);
                return(1);
            }
        }
        fclose(descfile);
    }

    /* OS2 mirrors */

    if(descfile=fopen("00-index","r")) {
        while(fgets(buffer,sizeof(buffer),descfile)) {
            if(!strncmp(buffer,file,strlen(file))) {
                buffer[strlen(buffer)-1]=NULL;
                ptr1=buffer;
                ptr1=getwhite(ptr1);
                ptr1=runwhite(ptr1);
                strcpy(desc,ptr1);
                fclose(descfile);
                return(1);
            }
        }
        fclose(descfile);
    }

    /* Aminet mirrors */

    if(descfile=fopen("INDEX","r")) {
        while(fgets(buffer,sizeof(buffer),descfile)) {
            if(!strncmp(buffer,file,strlen(file))) {
                buffer[strlen(buffer)-1]=NULL;
                strcpy(desc,&buffer[39]);
                fclose(descfile);
                return(1);
            }
        }
        fclose(descfile);
    }

    /* Mac mirrors */

    if(descfile=fopen("00index.txt","r")) {
        while(fgets(buffer,sizeof(buffer),descfile)) {
            if(strstr(buffer,file)&&strstr(buffer,"/mac/")) {
                fgets(buffer,sizeof(buffer),descfile);
                fgets(buffer,sizeof(buffer),descfile);
                fread(buffer,sizeof(buffer),1,descfile); 
                if(ptr1=strstr(buffer,"/mac/")) *ptr1=NULL;
                txpack(buffer);
                strcpy(desc,&buffer[1]);
                fclose(descfile);
                return(1);
            }
        }
        fclose(descfile);
    }

    /* HP48 mirrors */

    if(descfile=fopen("INDEX.txt","r")) {
        while(fgets(buffer,sizeof(buffer),descfile)) {
            if(!strncmp(buffer,file,strlen(file))) {
                fread(&buffer[strlen(buffer)],sizeof(buffer)-strlen(buffer),1,descfile); 
                ptr2=getwhite(buffer);
                ptr2=runwhite(ptr2);
                ptr2+=2;
                if(ptr1=strstr(ptr2,"\t- ")) {
                    while(*ptr1=='\t'||*ptr1==' ') ptr1--;
                    while(*ptr1!=0xa) ptr1--;
                    ptr1++;
                    *ptr1=NULL;
                }
                if(ptr1=strstr(buffer,"========")) *ptr1=NULL;
                txpack(buffer);
                ptr1=getwhite(buffer);
                ptr1=runwhite(ptr1);
                ptr1+=2;
                strcpy(desc,ptr1);
                fclose(descfile);
                if(strlen(desc)) return(1);
                else return(0);
            }
            memset(buffer,0,sizeof(buffer));
        }
        fclose(descfile);
    }

    /* Debian mirror */

    if(descfile=fopen("../Packages","r")) {
        while(fgets(buffer,sizeof(buffer),descfile)) {
            if(strstr(buffer,file)&&strstr(buffer,"filename: ")) {
                while(!strstr(buffer,"description:")) fgets(buffer,sizeof(buffer),descfile);
                fread(&buffer[strlen(buffer)],sizeof(buffer)-strlen(buffer),1,descfile); 
                if(ptr1=strstr(buffer,"architecture: ")) *ptr1=NULL;
                txpack(buffer);
                strcpy(desc,&buffer[13]);
                fclose(descfile);
                return(1);
            }
        }
        fclose(descfile);
    }
    return(0);
}

#endif /* SUP_FTPWEB */

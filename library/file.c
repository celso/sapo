/*
 * Program       : file.c
 * Author        : Celso Martinho (celso@ua.pt)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <fcntl.h>
#include <sys/param.h>
#include "file.h"
#include "protos.h"
#include <defines.h>
#define FALSE 0
#define TRUE  1

int isdirlink(char *file)
{
    int filedes;
    struct stat linfo;
    struct stat dinfo;
    int ret;

    ret=0;
    memset(&linfo,0,sizeof(struct stat));
    memset(&dinfo,0,sizeof(struct stat));
    if(!lstat(file,&linfo)) {
        stat(file,&dinfo);
        if((dinfo.st_mode & S_IFDIR) && (linfo.st_mode & S_IFLNK)) ret=1;
    } else printf("ERROR: Couldn't stat() %s\n",file);
    return(ret);
}

int fappend(char *dst,char *src)
{
    FILE *dst_fd,*src_fd;
    struct stat info;

#define FAP_BUFFER_SIZE 65535

    char fbuffer[FAP_BUFFER_SIZE];

    memset(&info,0,sizeof(struct stat));
    if(stat(src,&info)) { printf("ERROR: Couldn't stat() source file\n"); return(0); }
    if(src_fd=fopen(src,"r")) {
        if(dst_fd=fopen(dst,"a")) {


            fclose(dst_fd);
        } else printf("ERROR: Couldn't open destination file\n");
        fclose(src_fd);
    } else printf("ERROR: Couldn't open source file\n");
}

char *fget_field(FILE *fp,long offset,long column)
{
    static char buffer[10000];
    fseek(fp,offset,SEEK_SET);
    fgets(buffer,sizeof(buffer),fp);
    buffer[strlen(buffer)-1]=0;
    return(&buffer[column]);
}

getparentdir(char *old,char *new)
{
    char buf2[1024];
    char buf[MAXPATHLEN];
    char current[MAXPATHLEN];
    char newdir[MAXPATHLEN];
    char *ptr;

    getwd(current);

    sprintf(buf2,MKDIR_CMD" -p /tmp/%s",old);
    system(buf2);

    sprintf(buf,"/tmp/%s/../",old);
    chdir(buf);
    getwd(newdir);

    sprintf(buf2,"rm -fr /tmp/%s",old);
    system(buf2);
    ptr=strstr(newdir,"/tmp");
    ptr=ptr+4;
    strcpy(new,ptr);
    strcat(new,"/");

    chdir(current);
}

char *mktmpfile()
{
    time_t seed1;
    int seed2;
    static char ret[256];
    struct timeb tb;

    ftime(&tb);
    time(&seed1);
    seed2=rand();
    sprintf(ret,"/tmp/%d%d%d",seed1,seed2,tb.millitm);
    return(ret);
}

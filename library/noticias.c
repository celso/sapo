/*
 * URL parsing routines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include "protos.h"
#include "http.h"
#include "url.h"
#include "macros.h"
#define FALSE 0
#define TRUE  1

#define UBUFSIZE	2000

static char inb[200];

char *idnoticia(int id,int checksum)
{
    char *ptr;
    char fn1[500];
    char fn2[500];

    snprintf(fn1,sizeof(fn1),"%d",checksum+id);
    ptr=fn1; while(*ptr) { *ptr=*ptr-'0'+'a'; ptr++; }
    snprintf(fn2,sizeof(fn2),"%d",id);
    ptr=fn2; while(*ptr) { *ptr=*ptr-'0'+'A'; ptr++; }
    snprintf(inb,sizeof(inb),"%s,%s",fn2,fn1);
    return(inb);

}

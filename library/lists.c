/*
 * Program       : lists.c
 * Author        : Celso Martinho (celso@sapo.pt)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
#include "protos.h"
#define FALSE 0
#define TRUE  1

void NewList(struct List *list)
{
    list->lh_Head=NULL;
    list->lh_Tail=NULL;
}

void AddTail(struct List *list, struct Node *node)
{
    struct Node *pred;

    if(!list->lh_Head) list->lh_Head=node;
    if(pred=list->lh_Tail) {
        pred->ln_Succ=node;
        node->ln_Succ=NULL;
        node->ln_Pred=pred;
        list->lh_Tail=node;
    }
    else 
    {
        list->lh_Tail=node;
        node->ln_Succ=NULL;
        node->ln_Pred=NULL;
    }
}

void Remove(struct Node *node,struct List *list)
{
    struct Node *pred;
    struct Node *succ;
    pred=node->ln_Pred;
    succ=node->ln_Succ;
    if(succ&&pred) {
        pred->ln_Succ=succ;
        succ->ln_Pred=pred;
    }
    else if(pred&&(!succ)) {
        pred->ln_Succ=NULL;
    }
    else if((!pred)&&succ) {
        succ->ln_Pred=NULL;
        list->lh_Head=succ;
    }
}


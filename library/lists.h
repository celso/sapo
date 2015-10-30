/*
 * Program       : lists.h
 * Author        : Celso Martinho (celso@sapo.pt)
 */

struct List {
    struct  Node *lh_Head;
    struct  Node *lh_Tail;
};	/* word aligned */

struct Node {
    struct  Node *ln_Succ;	/* Pointer to next (successor) */
    struct  Node *ln_Pred;	/* Pointer to previous (predecessor) */
};	/* Note: word aligned */

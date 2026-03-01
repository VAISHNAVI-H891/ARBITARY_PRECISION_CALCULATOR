#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} Dlist;

#define SUCCESS 0
#define FAILURE -1

/* helper */
Dlist *create_node(int data);
int convert_to_list(const char *s, Dlist **head, Dlist **tail, int *sign); /* returns 0/1 sign via pointer */
void insert_front(Dlist **head, Dlist **tail, int data);
void insert_end(Dlist **head, Dlist **tail, int data);
void free_list(Dlist **head, Dlist **tail);
void print_list(Dlist *head);
void reverse_list(Dlist **head, Dlist **tail);
void copy_list(Dlist *src, Dlist **dstH, Dlist **dstT);
void remove_leading_zeros(Dlist **head, Dlist **tail);
int compare_lists(Dlist *h1, Dlist *h2); /* compares absolute values, 1 if h1>h2, 0 eq, -1 if h1<h2 */
int is_zero_list(Dlist *head);

/* arithmetic on absolute lists (no signs) */
int add_lists(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, Dlist **hR, Dlist **tR);
int subtract_lists(Dlist *hBig, Dlist *tBig, Dlist *hSmall, Dlist *tSmall, Dlist **hR, Dlist **tR); /* assumes big>=small */
int multiply_lists(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, Dlist **hR, Dlist **tR);
int divide_lists(Dlist *divH, Dlist *divT, Dlist *dH, Dlist *dT, Dlist **qH, Dlist **qT, Dlist **rH, Dlist **rT); /* quotient and remainder for abs values */

#endif


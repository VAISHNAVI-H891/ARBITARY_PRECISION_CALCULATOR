#include "apc.h"

/*******************************************************************************************************************************************************************
 * Title           : Create Node
 * Description     : Allocates memory for a new doubly linked list node and initializes it with the given digit.
 * Prototype       : Dlist *create_node(int data);
 * Input Parameters:
 *      data        : Single digit to store in the node.
 * Output          : Returns pointer to newly created node, or NULL if memory allocation fails.
 *******************************************************************************************************************************************************************/
Dlist *create_node(int data)
{
    // allocate memory for a new node
    Dlist *n = malloc(sizeof(Dlist));

    // return NULL if allocation failed
    if (!n) return NULL;

    // set node data
    n->data = data;

    // initialize prev and next pointers
    n->prev = n->next = NULL;

    // return pointer to node
    return n;
}

/*******************************************************************************************************************************************************************
 * Title           : Convert String to List
 * Description     : Converts a numeric string (with optional + or - sign) into a doubly linked list.
 *                   Also sets the sign (0 for positive, 1 for negative).
 * Prototype       : int convert_to_list(const char *s, Dlist **head, Dlist **tail, int *sign);
 * Input Parameters:
 *      s           : Input numeric string.
 *      head        : Pointer to head pointer of resulting list.
 *      tail        : Pointer to tail pointer of resulting list.
 *      sign        : Pointer to integer where sign will be stored (0 = positive, 1 = negative).
 * Output          : Returns SUCCESS if conversion is successful, FAILURE if string is invalid.
 *******************************************************************************************************************************************************************/
int convert_to_list(const char *s, Dlist **head, Dlist **tail, int *sign)
{
    // validate input pointers
    if (!s || !head || !tail || !sign) return FAILURE;

    // initialize head, tail, and sign
    *head = *tail = NULL;
    *sign = 0;

    // pointer to traverse string
    const char *p = s;

    // detect optional sign
    if (*p == '+') { *sign = 0; p++; }
    else if (*p == '-') { *sign = 1; p++; }

    // skip leading zeros
    while (*p == '0') p++;

    // if string ended after zeros, it's zero
    if (!*p) {
        // insert single 0 node
        insert_end(head, tail, 0);

        // zero is non-negative
        *sign = 0;

        // return success
        return SUCCESS;
    }

    // convert each character to digit and insert into list
    while (*p) {

        // check if character is digit
        if (!isdigit((unsigned char)*p)) return FAILURE;

        // insert digit at end
        insert_end(head, tail, *p - '0');

        // move to next character
        p++;
    }

    // conversion successful
    return SUCCESS;
}

/*******************************************************************************************************************************************************************
 * Title           : Insert Node at Front
 * Description     : Inserts a new node with given data at the front of a doubly linked list.
 * Prototype       : void insert_front(Dlist **head, Dlist **tail, int data);
 *******************************************************************************************************************************************************************/
void insert_front(Dlist **head, Dlist **tail, int data)
{
    // create new node
    Dlist *n = create_node(data);

    // return if memory allocation failed
    if (!n) return;

    // set new node next pointer to current head
    n->next = *head;

    // update previous pointer of current head if it exists
    if (*head) (*head)->prev = n;
    else *tail = n; // if list was empty, new node is also tail

    // update head to new node
    *head = n;
}

/*******************************************************************************************************************************************************************
 * Title           : Insert Node at End
 * Description     : Inserts a new node with given data at the end of a doubly linked list.
 * Prototype       : void insert_end(Dlist **head, Dlist **tail, int data);
 *******************************************************************************************************************************************************************/
void insert_end(Dlist **head, Dlist **tail, int data)
{
    // create new node
    Dlist *n = create_node(data);

    // return if memory allocation failed
    if (!n) return;

    // set new node previous pointer to current tail
    n->prev = *tail;

    // update next pointer of current tail if it exists
    if (*tail) (*tail)->next = n;
    else *head = n; // if list was empty, new node is also head

    // update tail to new node
    *tail = n;
}

/*******************************************************************************************************************************************************************
 * Title           : Free List
 * Description     : Frees all nodes of a doubly linked list and resets head and tail to NULL.
 * Prototype       : void free_list(Dlist **head, Dlist **tail);
 *******************************************************************************************************************************************************************/
void free_list(Dlist **head, Dlist **tail)
{
    // return if head is NULL
    if (!head || !*head) { if (tail) *tail = NULL; return; }

    // pointer to traverse list
    Dlist *p = *head;

    // free each node
    while (p) {
        Dlist *n = p->next;
        free(p);
        p = n;
    }

    // reset head and tail pointers
    *head = *tail = NULL;
}

/*******************************************************************************************************************************************************************
 * Title           : Print List
 * Description     : Prints the digits of a doubly linked list as a number.
 * Prototype       : void print_list(Dlist *head);
 *******************************************************************************************************************************************************************/
void print_list(Dlist *head)
{
    // if list is empty, print 0
    if (!head) { printf("0"); return; }

    // traverse and print each digit
    Dlist *p = head;
    while (p) {
        printf("%d", p->data);
        p = p->next;
    }
}

/*******************************************************************************************************************************************************************
 * Title           : Reverse List
 * Description     : Reverses a doubly linked list in place.
 * Prototype       : void reverse_list(Dlist **head, Dlist **tail);
 *******************************************************************************************************************************************************************/
void reverse_list(Dlist **head, Dlist **tail)
{
    // return if list is empty
    if (!head || !*head) return;

    // current pointer for traversal
    Dlist *cur = *head, *tmp = NULL;

    // tail will become current head
    *tail = *head;

    // swap prev and next for all nodes
    while (cur) {
        tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = cur->prev;
    }

    // update head pointer
    if (tmp) *head = tmp->prev;
}

/*******************************************************************************************************************************************************************
 * Title           : Copy List
 * Description     : Creates a copy of the given doubly linked list.
 * Prototype       : void copy_list(Dlist *src, Dlist **dstH, Dlist **dstT);
 *******************************************************************************************************************************************************************/
void copy_list(Dlist *src, Dlist **dstH, Dlist **dstT)
{
    // initialize destination list
    *dstH = *dstT = NULL;

    // traverse source list and insert each node at end
    while (src) {
        insert_end(dstH, dstT, src->data);
        src = src->next;
    }
}

/*******************************************************************************************************************************************************************
 * Title           : Remove Leading Zeros
 * Description     : Removes unnecessary leading zeros from a doubly linked list representing a number.
 * Prototype       : void remove_leading_zeros(Dlist **head, Dlist **tail);
 *******************************************************************************************************************************************************************/
void remove_leading_zeros(Dlist **head, Dlist **tail)
{
    // return if list is empty
    if (!head || !*head) return;

    // remove nodes while data is 0 and next exists
    while (*head && (*head)->data == 0 && (*head)->next) {
        Dlist *tmp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(tmp);
    }
}

/*******************************************************************************************************************************************************************
 * Title           : Compare Lists
 * Description     : Compares two doubly linked lists representing absolute numbers.
 *                   Returns 1 if first list > second, -1 if first < second, 0 if equal.
 * Prototype       : int compare_lists(Dlist *h1, Dlist *h2);
 *******************************************************************************************************************************************************************/
int compare_lists(Dlist *h1, Dlist *h2)
{
    // handle NULL lists
    if (!h1 && !h2) return 0;
    if (!h1) return -1;
    if (!h2) return 1;

    // count lengths
    int l1 = 0, l2 = 0;
    Dlist *p = h1, *q = h2;
    while (p) { l1++; p = p->next; }
    while (q) { l2++; q = q->next; }

    // compare lengths
    if (l1 > l2) return 1;
    if (l1 < l2) return -1;

    // compare digit by digit
    p = h1; q = h2;
    while (p && q) {
        if (p->data > q->data) return 1;
        if (p->data < q->data) return -1;
        p = p->next; q = q->next;
    }

    // lists are equal
    return 0;
}

/*******************************************************************************************************************************************************************
 * Title           : Check if List is Zero
 * Description     : Returns 1 if the list represents the number zero, else 0.
 * Prototype       : int is_zero_list(Dlist *head);
 *******************************************************************************************************************************************************************/
int is_zero_list(Dlist *head)
{
    // check if only node exists and its data is 0
    return (head && head->next == NULL && head->data == 0);
}

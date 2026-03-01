#include "apc.h"

/*******************************************************************************************************************************************************************
 * Title           : Add Absolute Lists
 * Description     : Adds two large numbers represented as doubly linked lists and stores the result in a resultant list.
 *                   Operates on absolute values only. Handles carry during addition.
 * Prototype       : int add_lists(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, Dlist **hR, Dlist **tR);
 * Input Parameters:
 *      h1          : Pointer to head of first number list.
 *      t1          : Pointer to tail of first number list.
 *      h2          : Pointer to head of second number list.
 *      t2          : Pointer to tail of second number list.
 *      hR          : Pointer to head pointer of resultant list (output).
 *      tR          : Pointer to tail pointer of resultant list (output).
 * Output          : Returns SUCCESS after storing the sum in the resultant list.
 *******************************************************************************************************************************************************************/
int add_lists(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, Dlist **hR, Dlist **tR)
{
    // initialize carry to 0
    int carry = 0;

    // pointers to traverse lists from tail (least significant digit)
    Dlist *p = t1, *q = t2;

    // traverse until both lists are fully processed
    while (p || q) {

        // get current digit from first list, 0 if NULL
        int d1 = (p ? p->data : 0);

        // get current digit from second list, 0 if NULL
        int d2 = (q ? q->data : 0);

        // sum digits plus carry
        int sum = d1 + d2 + carry;

        // insert last digit of sum at front of result list
        insert_front(hR, tR, sum % 10);

        // update carry for next iteration
        carry = sum / 10;

        // move to previous digit in first list
        if (p) p = p->prev;

        // move to previous digit in second list
        if (q) q = q->prev;
    }

    // if carry remains after loop, insert it at front
    if (carry) insert_front(hR, tR, carry);

    // remove leading zeros from result
    remove_leading_zeros(hR, tR);

    // addition successful
    return SUCCESS;
}

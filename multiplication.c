#include "apc.h"

/*******************************************************************************************************************************************************************
 * Title           : Multiplication
 * Description     : Performs multiplication of two large numbers represented as doubly linked lists.
 *                   Stores the result in a resultant list. Operates on absolute values only.
 * Prototype       : int multiply_lists(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, Dlist **hR, Dlist **tR);
 * Input Parameters:
 *      h1          : Pointer to head of first number list.
 *      t1          : Pointer to tail of first number list.
 *      h2          : Pointer to head of second number list.
 *      t2          : Pointer to tail of second number list.
 *      hR          : Pointer to head pointer of resultant list (output).
 *      tR          : Pointer to tail pointer of resultant list (output).
 * Output          : Returns SUCCESS after storing the product in the resultant list, FAILURE if memory allocation fails.
 *******************************************************************************************************************************************************************/
int multiply_lists(Dlist *h1, Dlist *t1, Dlist *h2, Dlist *t2, Dlist **hR, Dlist **tR)
{
    // count number of digits in first list
    int m = 0, n = 0;

    // pointer to traverse first list
    Dlist *p = h1;

    // pointer to traverse second list
    Dlist *q = h2;

    // count digits of first number
    while (p) { 
        m++; 
        p = p->next; 
    }

    // count digits of second number
    while (q) { 
        n++; 
        q = q->next; 
    }

    // total size of result = m + n
    int size = m + n;

    // allocate array to store multiplication result, initialized to 0
    int *res = calloc(size, sizeof(int));

    // check memory allocation
    if (!res) return FAILURE;

    // traverse first number from least significant digit
    int i = 0;
    for (p = t1; p; p = p->prev, i++) {

        // initialize carry for inner loop
        int carry = 0;

        // inner loop index for second number
        int j = 0;

        // traverse second number from least significant digit
        for (q = t2; q; q = q->prev, j++) {

            // compute position in result array
            int idx = i + j;

            // multiply digits and add existing value plus carry
            int prod = res[idx] + p->data * q->data + carry;

            // store last digit at current index
            res[idx] = prod % 10;

            // update carry
            carry = prod / 10;
        }

        // if carry remains after inner loop, add to next position
        if (carry) res[i + j] += carry;
    }

    // convert result array to linked list, skipping leading zeros
    int k = size - 1;

    // find first non-zero digit from most significant
    while (k > 0 && res[k] == 0) k--;

    // insert digits into result list from most significant to least
    for (; k >= 0; k--) insert_end(hR, tR, res[k]);

    // free temporary array
    free(res);

    // remove any leading zeros in final list
    remove_leading_zeros(hR, tR);

    // multiplication successful
    return SUCCESS;
}

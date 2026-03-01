/*******************************************************************************************************************************************************************
 * Title           : Subtract Absolute Lists
 * Description     : This function performs subtraction between two large numbers represented as doubly linked lists.
 *                   It assumes that the first number (big) is greater than or equal to the second number (small) in magnitude.
 *                   The subtraction is performed digit-by-digit from the least significant digit, handling borrow when required.
 *                   The final difference is stored in the resultant doubly linked list.
 *
 * Prototype       : int subtract_lists(Dlist *hBig, Dlist *tBig,
 *                                      Dlist *hSmall, Dlist *tSmall,
 *                                      Dlist **hR, Dlist **tR);
 *
 * Input Parameters:
 *      hBig    : Pointer to the head of the larger number list.
 *      tBig    : Pointer to the tail of the larger number list.
 *      hSmall  : Pointer to the head of the smaller number list.
 *      tSmall  : Pointer to the tail of the smaller number list.
 *      hR      : Pointer to the head pointer of the resultant list.
 *      tR      : Pointer to the tail pointer of the resultant list.
 *
 * Output         : Returns SUCCESS after storing the subtraction result in the resultant list.
 *                  Always succeeds because the function assumes hBig >= hSmall.
 *******************************************************************************************************************************************************************/

#include "apc.h"

/* subtract absolute lists: big - small (assumes big >= small) */
int subtract_lists(Dlist *hBig, Dlist *tBig, Dlist *hSmall, Dlist *tSmall, Dlist **hR, Dlist **tR)
{
    // pointer to big number's last digit (LSB)
    Dlist *p = tBig;

    // pointer to small number's last digit (LSB)
    Dlist *q = tSmall;

    // borrow flag used during subtraction
    int borrow = 0;

    // loop through all digits of big number
    while (p) {

        // subtract borrow from current big digit
        int d1 = p->data - borrow;

        // small digit if available, else 0
        int d2 = (q ? q->data : 0);

        // check if borrowing is needed
        if (d1 < d2) {

            // add 10 to current digit when borrowing
            d1 += 10;

            // set borrow for next digit
            borrow = 1;
        }
        else {
            // no borrow needed
            borrow = 0;
        }

        // insert resulting digit at front of result list
        insert_front(hR, tR, d1 - d2);

        // move to previous digit in big list
        p = p->prev;

        // move to previous digit in small list if available
        if (q) q = q->prev;
    }

    // remove leading zeros from result
    remove_leading_zeros(hR, tR);

    // indicate successful subtraction
    return SUCCESS;
}





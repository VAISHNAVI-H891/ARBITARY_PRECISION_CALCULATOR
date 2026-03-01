#include "apc.h"

/*******************************************************************************************************************************************************************
 * Title           : Division / Modulus of Two Lists
 * Description     : Performs division or modulus operation between two large numbers represented as doubly linked lists.
 *                   Computes the quotient and remainder using a long division algorithm on absolute values.
 *                   Sign of the result is handled externally (in main).
 * Prototype       : int divide_lists(Dlist *divH, Dlist *divT, Dlist *dH, Dlist *dT,
 *                                    Dlist **qH, Dlist **qT, Dlist **rH, Dlist **rT);
 * Input Parameters:
 *      divH       : Pointer to head of dividend list.
 *      divT       : Pointer to tail of dividend list.
 *      dH         : Pointer to head of divisor list.
 *      dT         : Pointer to tail of divisor list.
 *      qH         : Pointer to head pointer of quotient list (output).
 *      qT         : Pointer to tail pointer of quotient list (output).
 *      rH         : Pointer to head pointer of remainder list (output).
 *      rT         : Pointer to tail pointer of remainder list (output).
 * Output          : Returns SUCCESS if operation succeeds, FAILURE if division by zero occurs.
 *******************************************************************************************************************************************************************/
int divide_lists(Dlist *divH, Dlist *divT, Dlist *dH, Dlist *dT, Dlist **qH, Dlist **qT, Dlist **rH, Dlist **rT)
{
    // check for division by zero
    if (!dH) { 
        printf("ERROR: Division by zero\n"); 
        return FAILURE; 
    }

    // if dividend < divisor, quotient is 0
    if (compare_lists(divH, dH) < 0) {

        // insert 0 as quotient
        insert_end(qH, qT, 0);

        // remainder is the dividend itself
        copy_list(divH, rH, rT);

        // return success
        return SUCCESS;
    }

    // initialize remainder list pointers
    Dlist *remH = NULL, *remT = NULL;

    // pointer to traverse dividend
    Dlist *p = divH;

    // iterate through each digit of dividend
    while (p) {

        // append current digit to remainder
        insert_end(&remH, &remT, p->data);

        // remove leading zeros from remainder
        remove_leading_zeros(&remH, &remT);

        // counter for number of subtractions (quotient digit)
        int count = 0;

        // repeatedly subtract divisor from remainder until remainder < divisor
        while (remH && compare_lists(remH, dH) >= 0) {

            // temporary lists to store subtraction result
            Dlist *newH = NULL, *newT = NULL;

            // subtract remH - dH and store in new lists
            subtract_lists(remH, remT, dH, dT, &newH, &newT);

            // free old remainder list
            free_list(&remH, &remT);

            // update remainder to new result
            remH = newH;
            remT = newT;

            // remove leading zeros after subtraction
            remove_leading_zeros(&remH, &remT);

            // increment quotient digit counter
            count++;
        }

        // append quotient digit to quotient list
        insert_end(qH, qT, count);

        // move to next digit of dividend
        p = p->next;
    }

    // remove leading zeros from quotient list
    remove_leading_zeros(qH, qT);

    // remove leading zeros from remainder list
    remove_leading_zeros(&remH, &remT);

    // assign remainder to output pointers if provided
    if (rH) { 
        *rH = remH; 
        *rT = remT; 
    } else { 
        // free remainder list if not needed
        free_list(&remH, &remT); 
    }

    // operation successful
    return SUCCESS;
}

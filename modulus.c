#include "apc.h"

/*******************************************************************************************************************************************************************
 * Title           : Modulus of Two Lists
 * Description     : Computes the modulus (remainder) of division between two large numbers represented as doubly linked lists.
 *                   Uses divide_lists to perform long division and extracts the remainder.
 *                   Sign handling is done in main; this function only computes absolute remainder.
 * Prototype       : int modulus_lists(Dlist *divH, Dlist *divT, Dlist *dH, Dlist *dT, Dlist **rH, Dlist **rT);
 * Input Parameters:
 *      divH        : Pointer to head of dividend list.
 *      divT        : Pointer to tail of dividend list.
 *      dH          : Pointer to head of divisor list.
 *      dT          : Pointer to tail of divisor list.
 *      rH          : Pointer to head pointer of resultant remainder list.
 *      rT          : Pointer to tail pointer of resultant remainder list.
 * Output          : Returns SUCCESS if operation succeeds, FAILURE if division fails (e.g., division by zero).
 *******************************************************************************************************************************************************************/
int modulus_lists(Dlist *divH, Dlist *divT, Dlist *dH, Dlist *dT, Dlist **rH, Dlist **rT)
{
    // initialize temporary quotient list pointers
    Dlist *qH = NULL, *qT = NULL;

    // call divide_lists to compute quotient and remainder; discard quotient, store remainder in rH/rT
    return divide_lists(divH, divT, dH, dT, &qH, &qT, rH, rT);
}

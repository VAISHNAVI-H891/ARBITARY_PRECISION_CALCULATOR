/***********************************************************************************************
 * Title       : main function (Driver function)
 * Description : Driver for Arbitrary Precision Calculator (APC).
 *               Validates inputs, converts operands into doubly linked lists,
 *               performs arithmetic operations, and displays results in a formatted output.
 ***********************************************************************************************/
#include "apc.h"

/* prints vertical formatted output for two numbers and their result */
void print_vertical(const char *num1, char op, const char *num2, const char *result)
{
    // get lengths of operands and result
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int lenR = strlen(result);

    // determine width for alignment
    int width = len1;
    if (len2 + 1 > width) width = len2 + 1;   // space for operator
    if (lenR > width) width = lenR;

    // print first number right-aligned
    printf("%*s\n", width, num1);

    // print operator and second number
    printf("%c%*s\n", op, width - 1, num2);

    // print separator line
    for (int i = 0; i < width; i++) printf("-");
    printf("\n");

    // print result right-aligned
    printf("%*s\n", width, result);

    // print final separator line
    for (int i = 0; i < width; i++) printf("-");
    printf("\n");
}

int main(int argc, char *argv[])
{
    // check argument count
    if (argc != 4) {
        printf("Usage: %s <num1> <op> <num2>\n", argv[0]);
        return FAILURE;
    }

    // extract operator
    char op = argv[2][0];

    // initialize lists for numbers
    Dlist *h1 = NULL, *t1 = NULL;
    Dlist *h2 = NULL, *t2 = NULL;

    // initialize signs (0 = positive, 1 = negative)
    int s1 = 0, s2 = 0;

    // convert first number string to list
    if (convert_to_list(argv[1], &h1, &t1, &s1) == FAILURE) {
        printf("Invalid first number\n");
        return FAILURE;
    }

    // convert second number string to list
    if (convert_to_list(argv[3], &h2, &t2, &s2) == FAILURE) {
        printf("Invalid second number\n");
        free_list(&h1, &t1);
        return FAILURE;
    }

    // check division or modulus by zero
    if ((op == '/' || op == '%') && is_zero_list(h2)) {
        printf("Not defined (division by zero)\n");
        free_list(&h1, &t1);
        free_list(&h2, &t2);
        return FAILURE;
    }

    // initialize result list
    Dlist *hR = NULL, *tR = NULL;

    // result sign and status
    int res_sign = 0;
    int status = FAILURE;

    // perform operation based on operator
    switch (op) {
        case '+':
            if (s1 == s2) {
                // same sign, add absolute lists
                add_lists(h1, t1, h2, t2, &hR, &tR);
                res_sign = s1;
                status = SUCCESS;
            } else {
                // different signs, subtract smaller from larger
                int cmp = compare_lists(h1, h2);
                if (cmp == 0) {
                    // result is zero
                    insert_end(&hR, &tR, 0);
                    res_sign = 0;
                    status = SUCCESS;
                } else if (cmp > 0) {
                    subtract_lists(h1, t1, h2, t2, &hR, &tR);
                    res_sign = s1;
                    status = SUCCESS;
                } else {
                    subtract_lists(h2, t2, h1, t1, &hR, &tR);
                    res_sign = s2;
                    status = SUCCESS;
                }
            }
            break;

        case '-':
            if (s1 != s2) {
                // signs differ, addition of absolute values
                add_lists(h1, t1, h2, t2, &hR, &tR);
                res_sign = s1;
                status = SUCCESS;
            } else {
                // same signs, subtraction needed
                int cmp = compare_lists(h1, h2);
                if (cmp == 0) {
                    insert_end(&hR, &tR, 0);
                    res_sign = 0;
                    status = SUCCESS;
                } else if (cmp > 0) {
                    subtract_lists(h1, t1, h2, t2, &hR, &tR);
                    res_sign = s1;
                    status = SUCCESS;
                } else {
                    subtract_lists(h2, t2, h1, t1, &hR, &tR);
                    res_sign = !s1;
                    status = SUCCESS;
                }
            }
            break;

        case 'x':
        case '*':
            // multiplication
            multiply_lists(h1, t1, h2, t2, &hR, &tR);
            res_sign = (s1 != s2);
            status = SUCCESS;
            break;

        case '/': {
            // division
            Dlist *remH = NULL, *remT = NULL;
            status = divide_lists(h1, t1, h2, t2, &hR, &tR, &remH, &remT);
            if (status == SUCCESS) {
                res_sign = (s1 != s2);
                free_list(&remH, &remT);
            }
        } break;

        case '%': {
            // modulus
            Dlist *remH = NULL, *remT = NULL;
            status = divide_lists(h1, t1, h2, t2, &hR, &tR, &remH, &remT);
            if (status == SUCCESS) {
                // remainder becomes result
                free_list(&hR, &tR);
                hR = remH;
                tR = remT;
                res_sign = s1;
            }
        } break;

        default:
            // invalid operator
            printf("Invalid operator. Use + - * / %%\n");
            status = FAILURE;
    }

    /* --------------------------- */
    /*  CUSTOM OUTPUT FORMAT BELOW */
    /* --------------------------- */

    if (status == SUCCESS) {
        // display input numbers and operator
        printf("num1: %s\n", argv[1]);
        printf("num2: %s\n", argv[3]);
        printf("operator: %c\n", op);

        // display result
        printf("result: ");
        if (res_sign) printf("=");
        if (hR)
            print_list(hR);
        else
            printf("0");
        printf("\n");
    }

    // free all lists
    free_list(&h1, &t1);
    free_list(&h2, &t2);
    free_list(&hR, &tR);

    // return appropriate exit code
    return (status == SUCCESS) ? 0 : 1;
}

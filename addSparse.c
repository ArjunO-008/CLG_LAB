#include <stdio.h>
#include <stdlib.h>

struct Term {
    int coef;
    int exp;
};

int main() {
    struct Term a[100], b[100], res[200];
    int n1, n2, i, j, k;

    printf("Enter number of terms in polynomial 1: ");
    scanf("%d", &n1);
    for (i = 0; i < n1; i++) {
        printf("Enter coef and exp for term %d: ", i + 1);
        scanf("%d %d", &a[i].coef, &a[i].exp);
    }

    printf("Enter number of terms in polynomial 2: ");
    scanf("%d", &n2);
    for (i = 0; i < n2; i++) {
        printf("Enter coef and exp for term %d: ", i + 1);
        scanf("%d %d", &b[i].coef, &b[i].exp);
    }

    /* ---- sort polynomial 1 by exp descending ---- */
    for (i = 0; i < n1 - 1; i++)
        for (j = 0; j < n1 - 1 - i; j++)
            if (a[j].exp < a[j + 1].exp) {
                struct Term t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }

    /* ---- combine duplicate exponents in polynomial 1 ---- */
    for (i = 0; i < n1 - 1; i++) {
        if (a[i].exp == a[i + 1].exp) {
            a[i].coef += a[i + 1].coef;
            for (j = i + 1; j < n1 - 1; j++)
                a[j] = a[j + 1];
            n1--;
            i--;
        }
    }

    /* ---- sort polynomial 2 by exp descending ---- */
    for (i = 0; i < n2 - 1; i++)
        for (j = 0; j < n2 - 1 - i; j++)
            if (b[j].exp < b[j + 1].exp) {
                struct Term t = b[j];
                b[j] = b[j + 1];
                b[j + 1] = t;
            }

    /* ---- combine duplicate exponents in polynomial 2 ---- */
    for (i = 0; i < n2 - 1; i++) {
        if (b[i].exp == b[i + 1].exp) {
            b[i].coef += b[i + 1].coef;
            for (j = i + 1; j < n2 - 1; j++)
                b[j] = b[j + 1];
            n2--;
            i--;
        }
    }

    /* ---- sparse polynomial addition ---- */
    i = 0; j = 0; k = 0;
    while (i < n1 && j < n2) {
        if (a[i].exp == b[j].exp) {
            res[k].coef = a[i].coef + b[j].coef;
            res[k].exp = a[i].exp;
            i++; j++; k++;
        } else if (a[i].exp > b[j].exp) {
            res[k].coef = a[i].coef;
            res[k].exp = a[i].exp;
            i++; k++;
        } else {
            res[k].coef = b[j].coef;
            res[k].exp = b[j].exp;
            j++; k++;
        }
    }
    while (i < n1) {
        res[k].coef = a[i].coef;
        res[k].exp = a[i].exp;
        i++; k++;
    }
    while (j < n2) {
        res[k].coef = b[j].coef;
        res[k].exp = b[j].exp;
        j++; k++;
    }

    /* ---- print result ---- */
    int constant = 0;       /* stores value when exp is 0 */
    int haveConstant = 0;   /* flag whether a constant term exists */
    int printedAny = 0;

    printf("\nResult: ");
    for (i = 0; i < k; i++) {
        if (res[i].coef == 0)
            continue;  /* skip zero coefficient terms */

        if (res[i].exp == 0) {
            constant += res[i].coef;
            haveConstant = 1;
            continue;  /* print constant at the end */
        }

        if (printedAny)
            printf(" + ");
        printf("(%dx^%d)", res[i].coef, res[i].exp);
        printedAny = 1;
    }

    if (haveConstant && constant != 0) {
        if (printedAny)
            printf(" + ");
        printf("(%d)", constant);
        printedAny = 1;
    }

    if (!printedAny)
        printf("0");

    printf("\n");

    return 0;
}

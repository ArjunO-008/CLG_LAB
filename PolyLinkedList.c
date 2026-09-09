#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node *next;
};

// Create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    return newNode;
}

// Insert a term in descending order of exponent
void insertTerm(struct Node **poly, int coeff, int exp) {
    if (coeff == 0)
        return;

    struct Node *newNode = createNode(coeff, exp);

    // Empty list or exponent is greater than first node
    if (*poly == NULL || (*poly)->exp < exp) {
        newNode->next = *poly;
        *poly = newNode;
        return;
    }

    struct Node *temp = *poly;
    struct Node *prev = NULL;

    while (temp != NULL && temp->exp > exp) {
        prev = temp;
        temp = temp->next;
    }

    // Same exponent: add coefficients
    if (temp != NULL && temp->exp == exp) {
        temp->coeff += coeff;
        free(newNode);

        // Remove node if coefficient becomes zero
        if (temp->coeff == 0) {
            if (prev == NULL)
                *poly = temp->next;
            else
                prev->next = temp->next;

            free(temp);
        }
    } else {
        newNode->next = temp;

        if (prev != NULL)
            prev->next = newNode;
    }
}

// Read polynomial
void readPolynomial(struct Node **poly) {
    int n, coeff, exp;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    printf("Enter coefficient and exponent:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertTerm(poly, coeff, exp);
    }
}

// Display polynomial
void displayPolynomial(struct Node *poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    while (poly != NULL) {
        if (poly->coeff > 0 && poly != NULL)
            printf("+");

        printf("%dx^%d ", poly->coeff, poly->exp);

        poly = poly->next;
    }

    printf("\n");
}

// Polynomial addition
struct Node* addPolynomial(struct Node *p1, struct Node *p2) {
    struct Node *result = NULL;

    while (p1 != NULL) {
        insertTerm(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        insertTerm(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Polynomial multiplication
struct Node* multiplyPolynomial(struct Node *p1, struct Node *p2) {
    struct Node *result = NULL;

    struct Node *temp1 = p1;

    while (temp1 != NULL) {
        struct Node *temp2 = p2;

        while (temp2 != NULL) {
            int coeff = temp1->coeff * temp2->coeff;
            int exp = temp1->exp + temp2->exp;

            insertTerm(&result, coeff, exp);

            temp2 = temp2->next;
        }

        temp1 = temp1->next;
    }

    return result;
}

// Free linked list
void freePolynomial(struct Node *poly) {
    struct Node *temp;

    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}

int main() {
    struct Node *p1 = NULL;
    struct Node *p2 = NULL;
    struct Node *sum = NULL;
    struct Node *product = NULL;

    printf("Enter first polynomial:\n");
    readPolynomial(&p1);

    printf("\nEnter second polynomial:\n");
    readPolynomial(&p2);

    printf("\nFirst Polynomial: ");
    displayPolynomial(p1);

    printf("Second Polynomial: ");
    displayPolynomial(p2);

    sum = addPolynomial(p1, p2);
    product = multiplyPolynomial(p1, p2);

    printf("\nAddition: ");
    displayPolynomial(sum);

    printf("Multiplication: ");
    displayPolynomial(product);

    freePolynomial(p1);
    freePolynomial(p2);
    freePolynomial(sum);
    freePolynomial(product);

    return 0;
}

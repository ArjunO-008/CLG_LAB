#include <stdio.h>

#define MAX 100

/*
    Represents one non-zero element of a sparse matrix.

    row   -> row position of the element
    col   -> column position of the element
    value -> actual value stored at that position
*/
struct Term {
    int row;
    int col;
    int value;
};


/*
=========================================================
                TRANSPOSE OF SPARSE MATRIX
=========================================================
*/
void Transpose()
{
    /*
        A[]     -> Original sparse matrix   (elements stored from A[1])
        T[]     -> Transposed sparse matrix (elements stored from T[1])

        rows    -> Number of rows in A
        cols    -> Number of columns in A
        terms   -> Number of non-zero elements

        i, j    -> Loop counters
        k       -> Index where the next transposed element will be stored
    */
    struct Term A[MAX], T[MAX];
    int rows, cols, terms;
    int i, j, k;

    /*
        STEP 0: Read metadata and the matrix itself.
        Elements are expected in row-major order,
        the same way they would come out of a sparse
        matrix representation.
    */
    printf("\nEnter rows, columns and number of non-zero terms: ");
    scanf("%d %d %d", &rows, &cols, &terms);

    printf("Enter %d elements as (row col value), row-major order:\n", terms);
    for (i = 1; i <= terms; i++) {
        printf("Element %d: ", i);
        scanf("%d %d %d", &A[i].row, &A[i].col, &A[i].value);
    }

    /*
        Apply the metadata for the resultant (transposed) matrix.
        Rows and columns swap; the term count stays the same.
    */
    T[0].row = cols;
    T[0].col = rows;
    T[0].value = terms;

    k = 1;

    /*
        STEP 1:
        Transpose every non-zero element.

        (row, col, value)
              |
              v
        (col, row, value)
    */
    for (i = 1; i <= terms; i++) {

        T[k].row = A[i].col;
        T[k].col = A[i].row;
        T[k].value = A[i].value;

        k++;
    }

    /*
        STEP 2:
        Sort the transposed matrix by ROW.

        Since the original matrix was entered in
        row-major order, elements having the same
        transposed row will already be in column order.

        Therefore, we only need to sort by row.
    */
    for (i = 1; i < terms; i++) {

        for (j = i + 1; j <= terms; j++) {

            if (T[i].row > T[j].row) {

                struct Term temp = T[i];

                T[i] = T[j];
                T[j] = temp;
            }
        }
    }

    /*
        STEP 3: Print the result.
    */
    printf("\nTransposed sparse matrix (rows=%d, cols=%d, terms=%d):\n",
           T[0].row, T[0].col, T[0].value);
    printf("Row\tCol\tValue\n");
    for (i = 1; i <= terms; i++) {
        printf("%d\t%d\t%d\n", T[i].row, T[i].col, T[i].value);
    }
}


/*
=========================================================
                  ADDITION OF SPARSE MATRICES
=========================================================
*/
void Add()
{
    /*
        A[] -> First sparse matrix  (elements stored from A[1])
        B[] -> Second sparse matrix (elements stored from B[1])
        C[] -> Resultant sparse matrix (elements stored from C[1])

        rowsA, colsA, termsA -> Dimensions / term count of A
        rowsB, colsB, termsB -> Dimensions / term count of B

        i -> Current element of A
        j -> Current element of B
        k -> Position where next result is stored
    */
    struct Term A[MAX], B[MAX], C[MAX];
    int rowsA, colsA, termsA;
    int rowsB, colsB, termsB;
    int i, j, k;

    /*
        STEP 0: Read metadata and elements for both matrices.
        Elements are expected in row-major order.
    */
    printf("\n--- Matrix A ---\n");
    printf("Enter rows, columns and number of non-zero terms: ");
    scanf("%d %d %d", &rowsA, &colsA, &termsA);

    printf("Enter %d elements as (row col value), row-major order:\n", termsA);
    for (i = 1; i <= termsA; i++) {
        printf("Element %d: ", i);
        scanf("%d %d %d", &A[i].row, &A[i].col, &A[i].value);
    }

    printf("\n--- Matrix B ---\n");
    printf("Enter rows, columns and number of non-zero terms: ");
    scanf("%d %d %d", &rowsB, &colsB, &termsB);

    printf("Enter %d elements as (row col value), row-major order:\n", termsB);
    for (i = 1; i <= termsB; i++) {
        printf("Element %d: ", i);
        scanf("%d %d %d", &B[i].row, &B[i].col, &B[i].value);
    }

    /*
        Matrices must have the same dimensions
        for addition to be possible.
    */
    if (rowsA != rowsB || colsA != colsB) {

        printf("\nAddition not possible: dimension mismatch.\n");
        return;
    }

    /*
        Apply the metadata for the resultant matrix.
    */
    C[0].row = rowsA;
    C[0].col = colsA;

    i = 1;
    j = 1;
    k = 1;

    /*
        Compare elements of A and B
        according to their row-major positions.
    */
    while (i <= termsA && j <= termsB) {

        /*
            CASE 1:
            Both elements are at the same position.
        */
        if (A[i].row == B[j].row &&
            A[i].col == B[j].col) {

            int sum = A[i].value + B[j].value;

            /*
                If the sum is zero, we don't store it
                because it is no longer a non-zero element.
            */
            if (sum != 0) {

                C[k].row = A[i].row;
                C[k].col = A[i].col;
                C[k].value = sum;

                k++;
            }

            i++;
            j++;
        }

        /*
            CASE 2:
            A's element comes before B's element.
        */
        else if (A[i].row < B[j].row ||
                (A[i].row == B[j].row &&
                 A[i].col < B[j].col)) {

            C[k] = A[i];

            i++;
            k++;
        }

        /*
            CASE 3:
            B's element comes before A's element.
        */
        else {

            C[k] = B[j];

            j++;
            k++;
        }
    }

    /*
        Copy remaining elements of A.
    */
    while (i <= termsA) {

        C[k] = A[i];

        i++;
        k++;
    }

    /*
        Copy remaining elements of B.
    */
    while (j <= termsB) {

        C[k] = B[j];

        j++;
        k++;
    }

    /*
        Store the number of non-zero elements
        in the metadata row.
    */
    C[0].value = k - 1;

    /*
        STEP 4: Print the result.
    */
    printf("\nResultant sparse matrix (rows=%d, cols=%d, terms=%d):\n",
           C[0].row, C[0].col, C[0].value);
    printf("Row\tCol\tValue\n");
    for (i = 1; i <= C[0].value; i++) {
        printf("%d\t%d\t%d\n", C[i].row, C[i].col, C[i].value);
    }
}


/*
=========================================================
                          MAIN
=========================================================
*/
int main()
{
    int choice;

    /*
        Menu-driven: keep asking until the user chooses to exit.
    */
    do {
        printf("\n===== Sparse Matrix Operations =====\n");
        printf("1. Transpose\n");
        printf("2. Addition\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                Transpose();
                break;

            case 2:
                Add();
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 3);

    return 0;
}

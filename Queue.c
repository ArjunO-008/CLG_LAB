#include <stdio.h>
#include <string.h>

#define MAX 5

char linQueue[MAX][50];
int linFront = -1, linRear = -1;

void linearAdd() {
    char filename[50];
    if (linRear == MAX - 1) {
        printf("Queue is FULL. Cannot add print request.\n");
        return;
    }
    printf("Enter filename to print: ");
    scanf("%s", filename);
    if (linFront == -1) linFront = 0;
    linRear++;
    strcpy(linQueue[linRear], filename);
}

void linearPrint() {
    if (linFront == -1 || linFront > linRear) {
        printf("Print Queue is EMPTY. Nothing to print.\n");
        linFront = linRear = -1;
        return;
    }
    printf("Printing: \"%s\"\n", linQueue[linFront]);
    linFront++;
    if (linFront > linRear) {
        linFront = linRear = -1; 
    }
}

void linearDisplay() {
    if (linFront == -1 || linFront > linRear) {
        printf("Print Queue is EMPTY.\n");
        return;
    }
    printf("Current Print Queue: ");
    for (int i = linFront; i <= linRear; i++)
        printf("[%s] ", linQueue[i]);
    printf("\n");
}

void linearMenu() {
    int choice;
    while (1) {
        printf("1. Add print request\n");
        printf("2. Print\n");
        printf("3. Display all requests\n");
        printf("4. Exit to main menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: linearAdd(); break;
            case 2: linearPrint(); break;
            case 3: linearDisplay(); break;
            case 4: return;
            default: printf("Invalid choice.\n");
        }
    }
}

char deQueue[MAX][50];
int deFront = -1, deRear = -1;

void dequeAdd() {
    int side;
    char filename[50];

    if ((deFront == 0 && deRear == MAX - 1)) {
        printf("Deque is FULL. Cannot add print request.\n");
        return;
    }
    printf("Add at \n1.Front  \n2.Rear :\n");
    scanf("%d", &side);
    printf("Enter filename to print: ");
    scanf("%s", filename);

    if (deFront == -1) { 
        deFront = deRear = 0;
        strcpy(deQueue[deFront], filename);
        return;
    }
    if (side == 1) { 
        if (deFront == 0) {
            printf("Cannot add at front, no space.\n");
            return;
        }
        deFront--;
        strcpy(deQueue[deFront], filename);
    } else { 
        if (deRear == MAX - 1) {
            printf("Cannot add at rear, no space.\n");
            return;
        }
        deRear++;
        strcpy(deQueue[deRear], filename);
    }
}

void dequePrint() {
    int side;
    if (deFront == -1) {
        printf("Deque is EMPTY. Nothing to print.\n");
        return;
    }
    printf("Remove/Print from \n1.Front  \n2.Rear : \n");
    scanf("%d", &side);

    if (deFront == deRear) { 
        printf("Printing: \"%s\"\n", deQueue[deFront]);
        deFront = deRear = -1;
        return;
    }

    if (side == 1) {
        printf("Printing: \"%s\"\n", deQueue[deFront]);
        deFront++;
    } else {
        printf("Printing: \"%s\"\n", deQueue[deRear]);
        deRear--;
    }
}

void dequeDisplay() {
    if (deFront == -1) {
        printf("Deque is EMPTY.\n");
        return;
    }
    printf("Current Print Queue: ");
    for (int i = deFront; i <= deRear; i++)
        printf("[%s] ", deQueue[i]);
    printf("\n");
}

void dequeMenu() {
    int choice;
    while (1) {
        printf("1. Add print request\n");
        printf("2. Print\n");
        printf("3. Display all requests\n");
        printf("4. Exit to main menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: dequeAdd(); break;
            case 2: dequePrint(); break;
            case 3: dequeDisplay(); break;
            case 4: return;
            default: printf("Invalid choice.\n");
        }
    }
}

char cirQueue[MAX][50];
int cirFront = -1, cirRear = -1;

void circularAdd() {
    char filename[50];
    if ((cirFront == 0 && cirRear == MAX - 1) || (cirRear + 1) % MAX == cirFront) {
        printf("Circular Queue is FULL. Cannot add print request.\n");
        return;
    }
    printf("Enter filename to print: ");
    scanf("%s", filename);

    if (cirFront == -1) {
        cirFront = cirRear = 0;
    } else {
        cirRear = (cirRear + 1) % MAX;
    }
    strcpy(cirQueue[cirRear], filename);
}

void circularPrint() {
    if (cirFront == -1) {
        printf("Circular Queue is EMPTY. Nothing to print.\n");
        return;
    }
    printf("Printing: \"%s\"\n", cirQueue[cirFront]);

    if (cirFront == cirRear) { /* last element */
        cirFront = cirRear = -1;
    } else {
        cirFront = (cirFront + 1) % MAX;
    }
}

void circularDisplay() {
    if (cirFront == -1) {
        printf("Circular Queue is EMPTY.\n");
        return;
    }
    printf("Current Print Queue: ");
    int i = cirFront;
    while (1) {
        printf("[%s] ", cirQueue[i]);
        if (i == cirRear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

void circularMenu() {
    int choice;
    while (1) {
        printf("1. Add print request\n");
        printf("2. Print\n");
        printf("3. Display all requests\n");
        printf("4. Exit to main menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: circularAdd(); break;
            case 2: circularPrint(); break;
            case 3: circularDisplay(); break;
            case 4: return;
            default: printf("Invalid choice.\n");
        }
    }
}
int main() {
    int choice;
    while (1) {
        printf("PRINTER MANAGEMENT SYSTEM\n");
        printf("1. Linear Queue\n");
        printf("2. Double Ended Queue (Deque)\n");
        printf("3. Circular Queue\n");
        printf("4. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: linearMenu(); break;
            case 2: dequeMenu(); break;
            case 3: circularMenu(); break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char url[100];
    struct Node *prev;
    struct Node *next;
};

struct Node *current = NULL;

// Visit a new webpage
void visit(char url[]) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    strcpy(newNode->url, url);
    newNode->prev = NULL;
    newNode->next = NULL;

    if (current == NULL) {
        current = newNode;
        return;
    }

    // Delete forward history
    struct Node *temp = current->next;

    while (temp != NULL) {
        struct Node *next = temp->next;
        free(temp);
        temp = next;
    }

    // Insert new page after current
    current->next = newNode;
    newNode->prev = current;

    current = newNode;
}

// Go back
void back() {
    if (current == NULL) {
        printf("No pages visited.\n");
    }
    else if (current->prev == NULL) {
        printf("Cannot go back.\n");
    }
    else {
        current = current->prev;
        printf("Current page: %s\n", current->url);
    }
}

// Go forward
void forward() {
    if (current == NULL) {
        printf("No pages visited.\n");
    }
    else if (current->next == NULL) {
        printf("Cannot go forward.\n");
    }
    else {
        current = current->next;
        printf("Current page: %s\n", current->url);
    }
}

// Display current page
void display() {
    if (current == NULL)
        printf("No page opened.\n");
    else
        printf("Current page: %s\n", current->url);
}

int main() {
    int choice;
    char url[100];

    while (1) {
        printf("\n--- Web Browser ---\n");
        printf("1. Visit Page\n");
        printf("2. Back\n");
        printf("3. Forward\n");
        printf("4. Display Current Page\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                visit(url);
                display();
                break;

            case 2:
                back();
                break;

            case 3:
                forward();
                break;

            case 4:
                display();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

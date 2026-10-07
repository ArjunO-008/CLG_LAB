#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char word[50];
    char meaning[200];
    struct Node *left;
    struct Node *right;
};

// Create a new node
struct Node* createNode(char word[], char meaning[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    strcpy(newNode->word, word);
    strcpy(newNode->meaning, meaning);

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert a word into the BST
struct Node* insert(struct Node* root, char word[], char meaning[]) {
    if (root == NULL) {
        return createNode(word, meaning);
    }

    if (strcmp(word, root->word) < 0) {
        root->left = insert(root->left, word, meaning);
    }
    else if (strcmp(word, root->word) > 0) {
        root->right = insert(root->right, word, meaning);
    }
    else {
        // Word already exists
        strcpy(root->meaning, meaning);
    }

    return root;
}

// Search for a word
struct Node* search(struct Node* root, char word[]) {
    if (root == NULL || strcmp(root->word, word) == 0) {
        return root;
    }

    if (strcmp(word, root->word) < 0) {
        return search(root->left, word);
    }

    return search(root->right, word);
}

// Display dictionary in alphabetical order
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);

        printf("%s : %s\n", root->word, root->meaning);

        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    struct Node* result;

    int choice;
    char word[50];
    char meaning[200];

    while (1) {
        printf("\n--- DICTIONARY ---\n");
        printf("1. Insert word\n");
        printf("2. Search word\n");
        printf("3. Display dictionary\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter word: ");
                scanf("%s", word);

                printf("Enter meaning: ");
                scanf(" %[^\n]", meaning);

                root = insert(root, word, meaning);
                printf("Word inserted successfully.\n");
                break;

            case 2:
                printf("Enter word to search: ");
                scanf("%s", word);

                result = search(root, word);

                if (result != NULL) {
                    printf("Meaning: %s\n", result->meaning);
                }
                else {
                    printf("Word not found.\n");
                }
                break;

            case 3:
                printf("\nDictionary (Alphabetical Order):\n");
                inorder(root);
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

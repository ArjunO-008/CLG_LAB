#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Node {
    char data;
    struct Node *left, *right;
};

struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* stack[100];
int top = -1;

void push(struct Node* node) {
    stack[++top] = node;
}

struct Node* pop() {
    return stack[top--];
}

// Create expression tree from postfix
struct Node* createTree(char postfix[]) {
    int i;
    
    for (i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isalnum(ch)) {
            // Operand
            push(createNode(ch));
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            // Operator
            struct Node* node = createNode(ch);

            node->right = pop();
            node->left = pop();

            push(node);
        }
    }

    return pop();
}

// Prefix = Preorder traversal
void prefix(struct Node* root) {
    if (root != NULL) {
        printf("%c ", root->data);
        prefix(root->left);
        prefix(root->right);
    }
}

// Postfix = Postorder traversal
void postfix(struct Node* root) {
    if (root != NULL) {
        postfix(root->left);
        postfix(root->right);
        printf("%c ", root->data);
    }
}

int main() {
    char expression[100];
    struct Node* root;

    printf("Enter postfix expression: ");
    scanf("%s", expression);

    root = createTree(expression);

    printf("Prefix: ");
    prefix(root);

    printf("\nPostfix: ");
    postfix(root);

    return 0;
}

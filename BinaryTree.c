#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    char data;
    struct Node *left, *right;
};

struct Node* createNode(char data) {

    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


/* Stack for expression tree */

struct Node* stack[MAX];
int top = -1;

void push(struct Node* node) {
    stack[++top] = node;
}

struct Node* pop() {
    return stack[top--];
}


/* Stack for operators */

char opStack[MAX];
int opTop = -1;

void pushOp(char ch) {
    opStack[++opTop] = ch;
}

char popOp() {
    return opStack[opTop--];
}

char peekOp() {
    return opStack[opTop];
}

int isEmptyOp() {
    return opTop == -1;
}


/* Check operator */

int isOperator(char ch) {

    return ch == '+' ||
           ch == '-' ||
           ch == '*' ||
           ch == '/';
}


/* Operator priority */

int precedence(char ch) {

    if (ch == '*' || ch == '/')
        return 2;

    if (ch == '+' || ch == '-')
        return 1;

    return 0;
}


/* Infix → Postfix */

void InfixToPostfix(char infix[], char postfix[]) {

    int i = 0;
    int j = 0;

    while (infix[i] != '\0') {

        char ch = infix[i];

        /* Operand */

        if (ch >= 'A' && ch <= 'Z') {

            postfix[j++] = ch;
        }

        /* Opening bracket */

        else if (ch == '(') {

            pushOp(ch);
        }

        /* Closing bracket */

        else if (ch == ')') {

            while (peekOp() != '(') {
                postfix[j++] = popOp();
            }

            popOp();
        }

        /* Operator */

        else if (isOperator(ch)) {

            while (!isEmptyOp() &&
                   peekOp() != '(' &&
                   precedence(peekOp()) >= precedence(ch)) {

                postfix[j++] = popOp();
            }

            pushOp(ch);
        }

        i++;
    }


    /* Empty remaining operators */

    while (!isEmptyOp()) {
        postfix[j++] = popOp();
    }

    postfix[j] = '\0';
}


/* Create expression tree from postfix */

struct Node* createTree(char postfix[]) {

    int i;

    for (i = 0; postfix[i] != '\0'; i++) {

        char ch = postfix[i];

        /* Operand */

        if (ch >= 'A' && ch <= 'Z') {

            push(createNode(ch));
        }

        /* Operator */

        else if (isOperator(ch)) {

            struct Node* node = createNode(ch);

            node->right = pop();
            node->left = pop();

            push(node);
        }
    }

    return pop();
}


/* Prefix */

void prefix(struct Node* root) {

    if (root != NULL) {

        printf("%c ", root->data);

        prefix(root->left);

        prefix(root->right);
    }
}


/* Postfix */

void postfix(struct Node* root) {

    if (root != NULL) {

        postfix(root->left);

        postfix(root->right);

        printf("%c ", root->data);
    }
}


int main() {

    char expression[MAX];
    char postfixExpression[MAX];

    struct Node* root;


    printf("Enter infix expression: ");
    scanf("%s", expression);


    /* Infix → Postfix */

    InfixToPostfix(expression, postfixExpression);

    printf("Postfix: %s\n", postfixExpression);


    /* Postfix → Tree */

    root = createTree(postfixExpression);


    /* Tree traversals */

    printf("Prefix: ");
    prefix(root);

    printf("\nPostfix: ");
    postfix(root);

    return 0;
}

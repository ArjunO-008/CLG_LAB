#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 100
#define VARS 52

union Stack {
  char c[MAX];
  int i[MAX];
} S;
int top = -1;

void PushChar(char ch) { S.c[++top] = ch; }

char PopChar() { return S.c[top--]; }

char PeekChar() { return S.c[top]; }

int IsEmpty() { return top == -1; }

void PushInt(int x) { S.i[++top] = x; }
int PopInt() { return S.i[top--]; }
int PeekInt() { return S.i[top]; }

int ISP(char symbol) {
  switch (symbol) {
    case '(':
      return 0;

    case '+':
    case '-':
      return 2;

    case '*':
    case '/':
      return 4;

    case '^':
      return 5;

    default:
      return 8;
  }
}

int ICP(char symbol) {
  switch (symbol) {
    case ')':
      return 0;

    case '+':
    case '-':
      return 1;

    case '*':
    case '/':
      return 3;

    case '^':
      return 6;

    case '(':
      return 9;

    default:
      return 7;
  }
}

int isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}
int power(int a, int b) {
  int ans = 1;

  while (b--) ans *= a;

  return ans;
}
void InfixToPostfix(char infix[], char postfix[]) {
  int i = 0, j = 0;
  char ch;

  while (infix[i] != '\0') {
    ch = infix[i];
    if (ch == ' ') {
      i++;
      continue;
    }
    if (isdigit(ch)) {
      while (isdigit(infix[i])) {
        postfix[j++] = infix[i++];
      }

      postfix[j++] = ' ';
      continue;
    }

    if (isalpha(ch)) {
      postfix[j++] = ch;
      postfix[j++] = ' ';
    } else if (ch == '(') {
      PushChar(ch);
    } else if (ch == ')') {
      while (!IsEmpty() && PeekChar() != '(') {
        postfix[j++] = PopChar();
        postfix[j++] = ' ';
      }

      if (!IsEmpty()) PopChar();
    } else if (isOperator(ch)) {
      while (!IsEmpty() && ISP(PeekChar()) >= ICP(ch)) {
        postfix[j++] = PopChar();
        postfix[j++] = ' ';
      }

      PushChar(ch);
    }

    i++;
  }
  while (!IsEmpty()) {
    postfix[j++] = PopChar();
    postfix[j++] = ' ';
  }

  postfix[j] = '\0';
}

int value[VARS];
int assigned[VARS] = {0};
int getIndex(char ch) {
  if (ch >= 'A' && ch <= 'Z') return ch - 'A';

  return ch - 'a' + 26;
}

int EvaluatePostfix(char postfix[]) {
  int i = 0;
  top = -1;
  while (postfix[i] != '\0') {
    if (postfix[i] == ' ') {
      i++;
      continue;
    }
    if (isdigit(postfix[i])) {
      int num = 0;

      while (isdigit(postfix[i])) {
        num = num * 10 + (postfix[i] - '0');
        i++;
      }

      PushInt(num);
      continue;
    }
    if (isalpha(postfix[i])) {
      PushInt(value[getIndex(postfix[i])]);
    } else if (isOperator(postfix[i])) {
      int op2 = PopInt();
      int op1 = PopInt();
      int result;

      switch (postfix[i]) {
        case '+':
          result = op1 + op2;
          break;

        case '-':
          result = op1 - op2;
          break;

        case '*':
          result = op1 * op2;
          break;

        case '/':
          result = op1 / op2;
          break;

        case '^':
          result = power(op1, op2);
          break;
      }

      PushInt(result);
    }
    i++;
  }
  return PopInt();
}
void ReadVariables(char infix[]) {
  int i;
  for (i = 0; infix[i] != '\0'; i++) {
    if (isalpha(infix[i])) {
      int index = getIndex(infix[i]);
      if (!assigned[index]) {
        printf("Enter value of %c : ", infix[i]);
        scanf("%d", &value[index]);
        assigned[index] = 1;
      }
    }
  }
}
void main() {
  char infix[MAX];
  char postfix[MAX];
  int result;

  printf("Enter Infix Expression : ");
  fgets(infix, MAX, stdin);

  infix[strcspn(infix, "\n")] = '\0';
  top = -1;
  InfixToPostfix(infix, postfix);

  printf("Postfix Expression : %s\n", postfix);

  printf("\nEvaluating Postfix Expression: %s\n", postfix);

  ReadVariables(infix);
  result = EvaluatePostfix(postfix);
  printf("Result : %d\n", result);
}

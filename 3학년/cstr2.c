#include <stdio.h>

// postfix
//case문으로 해결 char 배열 -> 연산 기호 만나면 pop -> int로 바꾸고 계산 -> push

int postfix(char expr[]) {
    int stack[100];
    int top = 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        if (ch >= '0' && ch <= '9') {
            stack[top++] = ch - '0';
        } else {
            int a = stack[--top];
            int b = stack[--top];

            switch (ch) {
                case '+': stack[top++] = b + a; break;
                case '-': stack[top++] = b - a; break;
                case '*': stack[top++] = b * a; break;
                case '/': stack[top++] = b / a; break;
            }
        }
    }

    return stack[top-1];
}

int main() {
    char expr[] = "23*54*+9-";

    printf("%d\n", postfix(expr));

    return 0;
}
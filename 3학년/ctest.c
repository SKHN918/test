#include <stdio.h>
void hanoi(int n, char start, char mid, char end);

int main(void){
    int n=0;
    printf("원반의 개수 : ");
    scanf("%d", &n);

    hanoi(n, 'A','B','C');
    return 0;
}

void hanoi(int n, char start, char mid, char end){
    if (n==1) {
        printf("1번 원판을 %c에서 %c로 옮긴다. \n", start, end);
    }
    else {
        hanoi(n-1, start, end, mid);
        printf("%d번 원판을 %c에서 %c로 옮긴다. \n", n, start, end);
        hanoi(n-1, mid, start, end);
    }
}



// linked list 개수

typedef struct node{
    int data;
    struct node *next;
} node;

int count(node *head){
    int c = 0;
    node *p = head;

    while (p!=NULL){
        c++;
        p = p -> next;
    }
    return c;
}
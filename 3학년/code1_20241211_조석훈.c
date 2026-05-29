/*
 * [퀴즈 5 - 문제 1] 정상 동작하는 BST 코드
 * --------------------------------------------------------------
 * 본 코드는 컴파일 및 실행이 정상적으로 되는 BST 구현 코드이다.
 *
 * 학생은 이 코드의 [위치 A]~[위치 E] 사이에 표시된 (B1)~(D4) 등
 * 주석 표시 지점에 "추적용 printf"를 추가하여 BST 내부의 동작
 * (삽입 경로, 탐색 비교 순서, 삭제 시 후계자 처리 등)을
 * 관찰 가능한 형태로 출력하도록 만들어야 한다.
 *
 * 주의: printf 외의 어떤 코드도 추가/삭제/수정 하지 말 것.
 *       (새 함수, 새 전역 변수, 새 매개변수 추가 금지)
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

/* [위치 A] 노드 생성 */
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* [위치 B] 삽입: 재귀적으로 올바른 위치를 찾아 새 노드를 연결 */
Node* insert(Node* root, int key) {
    if (root == NULL) {
        /* (B1) 새 노드를 만들어 반환하는 지점 */
        printf("새 노드 생성: key=%d\n", key);
        return createNode(key);
    }
    if (key < root->key) {
        /* (B2) 왼쪽 서브트리로 내려가는 지점 */
        printf("key=%d < root->key=%d => 왼쪽으로 이동\n", key, root->key);
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        /* (B3) 오른쪽 서브트리로 내려가는 지점 */
        printf("key=%d > root->key=%d => 오른쪽으로 이동\n", key, root->key);
        root->right = insert(root->right, key);
    } else {
        /* (B4) 중복 키는 무시 */
        printf("key=%d 중복 무시\n", key);
    }
    return root;
}

/* [위치 C] 탐색: 재귀적으로 key를 찾음 */
Node* search(Node* root, int key) {
    if (root == NULL) {
        /* (C1) 더 이상 비교할 노드가 없음 */
        printf("key=%d 를 찾지 못함\n", key);
        return NULL;
    }
    if (key == root->key) {
        /* (C2) 찾음 */
        printf("key=%d == root->key=%d => 탐색 성공\n", key, root->key);
        return root;
    } else if (key < root->key) {
        /* (C3) 왼쪽으로 */
        printf("key=%d < root->key=%d => 왼쪽으로 이동\n", key, root->key);
        return search(root->left, key);
    } else {
        /* (C4) 오른쪽으로 */
        printf("key=%d > root->key=%d => 오른쪽으로 이동\n", key, root->key);
        return search(root->right, key);
    }
}

/* 최소 키 노드(후계자 후보) 찾기 */
Node* findMin(Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

/* [위치 D] 삭제 */
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key) {
        /* (D1) 왼쪽 서브트리로 내려감 */
        printf("key=%d < root->key=%d => 왼쪽으로 이동\n", key, root->key);
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        /* (D2) 오른쪽 서브트리로 내려감 */
        printf("key=%d > root->key=%d => 오른쪽으로 이동\n", key, root->key);
        root->right = deleteNode(root->right, key);
    } else {
        /* (D3) 삭제 대상 노드 발견(자식 수 분류) */
        printf("삭제 대상: key=%d => 왼쪽 자식=%s, 오른쪽 자식=%s\n",
               root->key,
               (root->left  != NULL ? "존재" : "존재X"),
               (root->right != NULL ? "존재" : "존재X"));
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        /* (D4) 자식이 둘인 경우: 오른쪽 서브트리의 최소값(후계자)으로 대체 */
        Node* succ = findMin(root->right);
        printf("자식이 둘 -> 오른쪽 서브트리 최솟값:key=%d로\n", succ->key);
        root->key = succ->key;
        root->right = deleteNode(root->right, succ->key);
    }
    return root;
}

/* [위치 E] 중위 순회 */
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

int main(void) {
    Node* root = NULL;
    int data[] = {50, 30, 70, 20, 40, 60, 80, 35};
    int n = sizeof(data) / sizeof(data[0]);

    /* 1) 삽입 */
    for (int i = 0; i < n; i++) {
        printf("\n=== insert(%d) ===\n", data[i]);
        root = insert(root, data[i]);
    }

    /* 2) 중위 순회 */
    printf("\n[중위 순회 결과] ");
    inorder(root);
    printf("\n");

    /* 3) 탐색 */
    int targets[] = {35, 55};
    for (int i = 0; i < 2; i++) {
        printf("\n=== search(%d) ===\n", targets[i]);
        Node* r = search(root, targets[i]);
        if (r) printf("-> 결과: 찾음(%d)\n", r->key);
        else   printf("-> 결과: 찾지 못함\n");
    }

    /* 4) 삭제 */
    int del[] = {20, 30, 50};  /* 잎, 자식 하나, 자식 둘 */
    for (int i = 0; i < 3; i++) {
        printf("\n=== delete(%d) ===\n", del[i]);
        root = deleteNode(root, del[i]);
        printf("[삭제 후 중위 순회] ");
        inorder(root);
        printf("\n");
    }
    return 0;
}
  
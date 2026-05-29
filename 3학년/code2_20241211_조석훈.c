/*
 * [퀴즈 5 - 문제 2] 논리 오류가 포함된 BST 코드
 * --------------------------------------------------------------
 * 본 코드는 C 문법상 컴파일과 실행은 정상적으로 되지만,
 * BST의 동작 결과가 의도와 다르게 나타난다.
 *
 * 코드에는 두 군데의 "논리 오류(BUG-1, BUG-2)"가 숨어 있다.

 *
 * 학생은 다음을 수행해야 한다.
 *   1) 우선 코드를 수정하지 말고 그대로 컴파일·실행하여
 *      출력이 어떻게 이상한지 확인한다.
 *   2) 디버깅용 printf를 적절한 위치에 추가하여 원인을 좁힌다.
 *   3) BUG-1, BUG-2를 찾아 수정하고, 수정 전/후의 동작 차이를
 *      설명한다.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}


Node* insert(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);          
    } else if (key > root->key) {
        root->right = insert(root->right, key);         
    }
    return root;
}


Node* search(Node* root, int key) {
    if (root == NULL) return NULL;
    if (key == root->key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}


Node* findSuccessor(Node* node) {
    while (node->left != NULL) {        
        node = node->right;
    }
    return node;
}


Node* deleteNode(Node* root, int key) {
    if (root == NULL) return NULL;
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* t = root->right; free(root); return t;
        } else if (root->right == NULL) {
            Node* t = root->left; free(root); return t;
        }
        Node* succ = findSuccessor(root->right);
        root->key = succ->key;
        root->right = deleteNode(root->right, succ->key);
    }
    return root;
}

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

    for (int i = 0; i < n; i++) {
        root = insert(root, data[i]);
    }

    printf("[삽입 후 중위 순회] ");
    inorder(root);
    printf("\n");

    printf("search(35) = %s\n", search(root, 35) ? "찾음" : "없음");
    printf("search(60) = %s\n", search(root, 60) ? "찾음" : "없음");

    root = deleteNode(root, 50);
    printf("[delete(50) 후 중위 순회] ");
    inorder(root);
    printf("\n");
    return 0;
}
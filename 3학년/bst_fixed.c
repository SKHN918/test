/*
 * [퀴즈 5 - 문제 2] 논리 오류 수정 코드
 * --------------------------------------------------------------
 * BUG-1: insert() 에서 재귀 반환값을 root->left / root->right 에
 *        연결하지 않아 루트 노드 하나만 트리에 남는 문제 수정.
 *
 * BUG-2: findSuccessor() 에서 right 방향으로 내려가
 *        최솟값이 아닌 최댓값을 반환하는 문제 수정.
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
    node->key  = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* -------------------------------------------------------
 * BUG-1 수정:
 *   수정 전) insert(root->left,  key);   <- 반환값 버림
 *            insert(root->right, key);   <- 반환값 버림
 *   수정 후) root->left  = insert(root->left,  key);
 *            root->right = insert(root->right, key);
 *
 *   원인: createNode()가 만든 새 노드 포인터를 부모 노드의
 *         left/right 에 연결하지 않아 트리에 루트(50)만 남음.
 * ------------------------------------------------------- */
Node* insert(Node* root, int key) {
    if (root == NULL) {
        printf("  [insert] 새 노드 생성: key=%d\n", key);
        return createNode(key);
    }
    if (key < root->key) {
        printf("  [insert] key=%d < %d -> 왼쪽\n", key, root->key);
        root->left  = insert(root->left,  key);   /* BUG-1 수정 */
    } else if (key > root->key) {
        printf("  [insert] key=%d > %d -> 오른쪽\n", key, root->key);
        root->right = insert(root->right, key);   /* BUG-1 수정 */
    }
    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL) return NULL;
    if (key == root->key) return root;
    if (key < root->key) return search(root->left,  key);
    return search(root->right, key);
}

/* -------------------------------------------------------
 * BUG-2 수정:
 *   수정 전) while (node->right != NULL) node = node->right;
 *            -> 오른쪽 서브트리의 최댓값을 반환 (wrong!)
 *   수정 후) while (node->left  != NULL) node = node->left;
 *            -> 오른쪽 서브트리의 최솟값(in-order successor)
 *
 *   원인: delete 시 두 자식이 있는 경우 in-order successor
 *         (오른쪽 서브트리 최솟값)로 대체해야 BST 성질이
 *         유지되는데, 반대 방향으로 내려가 최댓값을 사용해
 *         BST 정렬 순서가 깨짐.
 * ------------------------------------------------------- */
Node* findSuccessor(Node* node) {
    printf("  [findSuccessor] 오른쪽 서브트리에서 최솟값 탐색 시작: %d\n", node->key);
    while (node->left != NULL) {          /* BUG-2 수정: right -> left */
        node = node->left;
        printf("  [findSuccessor] 왼쪽으로 이동 -> %d\n", node->key);
    }
    printf("  [findSuccessor] 후계자 결정: key=%d\n", node->key);
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return NULL;
    if (key < root->key) {
        printf("  [delete] key=%d < %d -> 왼쪽\n", key, root->key);
        root->left  = deleteNode(root->left,  key);
    } else if (key > root->key) {
        printf("  [delete] key=%d > %d -> 오른쪽\n", key, root->key);
        root->right = deleteNode(root->right, key);
    } else {
        printf("  [delete] 삭제 대상 발견: key=%d\n", root->key);
        if (root->left == NULL) {
            printf("  [delete] 왼쪽 자식 없음 -> 오른쪽 자식으로 대체\n");
            Node* t = root->right; free(root); return t;
        } else if (root->right == NULL) {
            printf("  [delete] 오른쪽 자식 없음 -> 왼쪽 자식으로 대체\n");
            Node* t = root->left;  free(root); return t;
        }
        printf("  [delete] 자식 둘 -> 후계자 탐색\n");
        Node* succ = findSuccessor(root->right);
        printf("  [delete] 후계자 key=%d 로 현재 노드 key=%d 대체\n",
               succ->key, root->key);
        root->key   = succ->key;
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

    printf("======= 삽입 =======\n");
    for (int i = 0; i < n; i++) {
        printf("\n--- insert(%d) ---\n", data[i]);
        root = insert(root, data[i]);
    }

    printf("\n[삽입 후 중위 순회] ");
    inorder(root);
    printf("\n");
    /* 정상 출력: 20 30 35 40 50 60 70 80 */

    printf("\nsearch(35) = %s\n", search(root, 35) ? "찾음" : "없음");
    printf("search(60) = %s\n", search(root, 60) ? "찾음" : "없음");

    printf("\n======= delete(50) =======\n");
    root = deleteNode(root, 50);
    printf("\n[delete(50) 후 중위 순회] ");
    inorder(root);
    printf("\n");
    /* 정상 출력: 20 30 35 40 60 70 80  (50 자리를 후계자 60이 대체) */

    return 0;
}

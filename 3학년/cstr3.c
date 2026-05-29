#include <stdio.h>

//tree 뒤집기
typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}node;

void invert(node *root){
    if (root==NULL) return;

    node *temp = root->left;
    root->left = root->right;
    root->right = temp;

    invert(root->left);
    invert(root->right);
}

//
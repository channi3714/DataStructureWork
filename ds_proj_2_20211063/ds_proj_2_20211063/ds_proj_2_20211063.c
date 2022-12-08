#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode* treePtr;

typedef struct treeNode
{
    treePtr lchild;
    int data;
    treePtr rchild;
    int level;
}treeNode;

void preorder(treePtr tree);
treePtr post2tree(int ary[], int start, int end, int lev);

int main(void) {
    treePtr tree = NULL;
    char str[10000];
    char* result;
    int post[10000];
    int i = 0;
    gets(str);
    //printf("%s\n", str);
    result = strtok(str, " ");
    while (result != NULL) {
        post[i] = atoi(result);
        //printf("%d\n", post[i]);
        result = strtok(NULL, " ");
        i++;
    }
    //int post[] = { 5, 28, 24, 45, 30, 60, 52, 98, 50 };
    //int len = sizeof(post) / sizeof(post[0]);
    int len = i ;
    tree = post2tree(post, 0, len - 1, 1);

    preorder(tree);
    printf("\n");

    return 0;
}

treePtr post2tree(int ary[], int start, int end, int lev) {
    if (start > end) {
        return NULL;
    }
    treePtr ptr = (treePtr)malloc(sizeof(treeNode));
    ptr->data = ary[end];
    ptr->level = lev;
    ptr->lchild = ptr->rchild = NULL;

    int i;
    for (i = end; i >= start; i--) {
        if (ary[i] < ary[end]) {
            break;
        }
    }
    lev++;
    //right subtree
    ptr->rchild = post2tree(ary, i + 1, end - 1, lev);
    //left subtree
    ptr->lchild = post2tree(ary, start, i, lev);

    return ptr;
}
void preorder(treePtr tree) {
    if (tree) {
        printf("%d(%d) ", tree->data, tree->level);
        preorder(tree->lchild);
        preorder(tree->rchild);
    }
}
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define IS_FULL(ptr) (!(ptr))
typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
}treeNode;
void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);

void main()
{
	int i, n, A[MAX_TERMS];
	treePtr tree = NULL;
	treePtr root = NULL;
	
	FILE* fp;
	fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("파일열기 실패\n");
		return;
	}

	fscanf(fp, "%d", &n);
	int cnt = 0;
	while (EOF != fscanf(fp, "%d", &i)) {
		A[cnt] = i;
		//printf("%d\n", A[cnt]);
		cnt++;
	}
		// 순서대로 binary search tree에 삽입한다 //
	for (i = 0; i < n; i++) {
		//printf("%d\n", A[i]);
		insert(&tree, A[i]);
	}
	inorder(tree);
	printf("\n");
	preorder(tree);
	printf("\n");
	fclose(fp);
}

void inorder(treePtr tree) {
	if (tree)
	{
		inorder(tree->lchild);
		printf("%3d", tree->data);
		inorder(tree->rchild);
	}
}
void preorder(treePtr tree) {
	if (tree) {
		printf("%3d", tree->data);
		preorder(tree->lchild);
		preorder(tree->rchild);
	}
}
void insert(treePtr* node, int num) {
	static int nth = 0;
	//printf("------------%d\n", num);
	treePtr ptr, temp = modifiedSearch(*node, num);
	//printf("modify\n");
	if (temp || !(*node)) {
		//printf("modify after\n");
		/* num is not in the tree */
		ptr = (treePtr)malloc(sizeof(node));
		//printf("malloc\n");
		if (IS_FULL(ptr)) {
			fprintf(stderr, "The memory is full");
			exit(1);
		}
		ptr->data = num;
		ptr->lchild = ptr->rchild = NULL;
		//printf("ptr %d\n", num);
		if (*node) /* insert as child of temp */
			if (num < temp->data)
				temp->lchild = ptr;
			else temp->rchild = ptr;
		else {
			*node = ptr;
		}
	}
	//printf("nth %d\n", nth);
	nth++;
	//free(ptr);
}
treePtr modifiedSearch(treePtr node, int num) {
	treePtr temp = node;
	
	if (!(node)) {
		return NULL;
	}
	else {
		while (node) {
			if (node->data == num)
				return NULL;
			temp = node;
			//printf("%d %d\n", num, temp->data);
			if (num < node->data)
				node = node->lchild;
			else
				node = node->rchild;
		}
		//printf("node %d\n", temp->data);
		return temp;
	}
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50 /*maximum number of vertices*/
typedef struct node* node_pointer;
typedef struct node {
	int vertex;
	node_pointer link;
}node;
typedef struct {
	node_pointer top;
}Stack;

node_pointer graph[MAX_VERTICES];
int n = 0; /* vertices currently in use */

void vis(int visited[], int n);

void init(Stack* s);
int is_empty(Stack* s);
void push(Stack* s, int item);
int pop(Stack* s);

void makeGraph(int src, int dst, int visited[]);
void DFS(node_pointer graph[], int s, int visited[]);

int main(void) {
	FILE* fp = NULL;
	fp = fopen("graph.txt", "r");
	char line[255];
	int n, src, dst;
	char dir;

	for (int i = 0; i < MAX_VERTICES; i++){
		graph[i] = NULL;
	}

	if (fp == NULL) {
		fprintf(stderr, "파일 graph.txt를 열 수 없습니다.\n");
		exit(0);
	}
	fscanf(fp, "%d", &n);
	printf("%d\n", n);
	int* visited = (int*)malloc(sizeof(int) * n);
	vis(visited, n);
	while (EOF != fscanf(fp, "%d %d %c", &src, &dst, &dir)) {
		if (dir == 'u') {
			makeGraph(src, dst, visited);
			makeGraph(dst, src, visited);
			visited[src] = 1;
			visited[dst] = 1;
		}
		else if (dir == 'd') {
			makeGraph(src, dst, visited);
			visited[src] = 1;
		}
		printf("%d %d %c\n", src, dst, dir);
	}
	vis(visited, n);
	printf("\n");
	for (int i = 1; i <= n; i++) {
		node_pointer p = graph[i];
		printf("%d : ", i);
		while (p) {
			printf("%d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}

	//printf("%d %d", graph[1]->vertex, graph[1]->link->vertex);
	
	vis(visited, n);
	printf("\n");
	DFS(graph, 1, visited);
	vis(visited, n);
	printf("\n");
	DFS(graph, 2, visited);
	vis(visited, n);
	printf("\n");
	DFS(graph, 3, visited);
	vis(visited, n);
	printf("\n");
	DFS(graph, 4, visited);
	vis(visited, n);
	printf("\n");
	DFS(graph, 5, visited);
	printf("\n");

	fclose(fp);


	return 0;
}

void vis(int visited[], int n) {
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}
}

void init(Stack* s) {
	s->top = NULL;
}

int is_empty(Stack* s) {
	return (s->top == NULL);
}

void push(Stack* s, int item) {
	node_pointer temp = (node_pointer)malloc(sizeof(node));
	temp->vertex = item;
	temp->link = s->top;
	s->top = temp;
}

int pop(Stack* s) {
	if (is_empty(s)) {
		printf("stack empty\n");
	}
	else {
		node_pointer temp = s->top;
		int data = temp->vertex;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}

void makeGraph(int src, int dst, int visited[]) {
	node_pointer cur = graph[src];
	node_pointer ptr = (node_pointer)malloc(sizeof(node));
	if (visited[src] == 0) {
		printf("src %d NULL\n", src);
		ptr->vertex = dst;
		ptr->link = graph[src];
		graph[src] = ptr;
	}
	while (cur) {
		if (dst > cur->vertex) {
			/*ptr->vertex = dst;
			ptr->link = cur->link;
			cur->link = ptr;*/
			if (cur->link == NULL) {
				ptr->vertex = dst;
				ptr->link = cur->link;
				cur->link = ptr;
				return;
			}
			else if (dst < (cur->link)->vertex) {
				ptr->vertex = dst;
				ptr->link = cur->link;
				cur->link = ptr;
				return;
			}
		}
		else {
			ptr->vertex = dst;
			ptr->link = graph[src];
			graph[src] = ptr;
			return;
		}
		cur = cur->link;
	}
	return;
}

//void makeGraph(int src, int dst) {
//	node_pointer ptr = (node_pointer)malloc(sizeof(node));
//
//	ptr->vertex = dst;
//	ptr->link = graph[src];
//	graph[src] = ptr;
//}

void DFS(node_pointer graph[], int s, int visited[]) {
	node_pointer temp = NULL;
	int v;
	Stack S;
	init(&S);
	// 시작 정점을 스택에 push 합니다.
	push(&S, s);

	while (!is_empty(&S)) {
		// 스택에 있는 정점을 pop하고 방문 표시를 합니다.
		s = pop(&S);
		if (visited[s - 1] == 0) {
			visited[s - 1] = 1;
			printf("%d ", s);
		}

		// 방문하지 않은 인접 정점을 스택에 push합니다.
		for (temp = graph[s]; temp != NULL; temp = temp->link) {
			v = temp->vertex;
			if (visited[v - 1] == 0) {
				push(&S, v);
			}
		}
	}
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50 /*maximum number of vertices*/
typedef struct node* node_pointer;
typedef struct node {
	int vertex;
	node_pointer link;
}node;
typedef struct stackNode* stackNodePointer;
typedef struct stackNode {
	int src;
	int dst;
	stackNodePointer link;
}stackNode;
typedef struct {
	stackNodePointer top;
}Stack;

node_pointer graph[MAX_VERTICES];
int n = 0; /* vertices currently in use */

void vis(int visited[], int n);

void init(Stack* s);
int is_empty(Stack* s);
void push(Stack* s, int item1, int item2);
stackNode pop(Stack* s);

void makeGraph(int src, int dst, int visited[]);
void dfs(node_pointer graph[], int s, int visited[]);

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
	//printf("%d\n", n);
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
		//printf("%d %d %c\n", src, dst, dir);
	}
	vis(visited, n);
	//printf("\n");
	/*for (int i = 1; i <= n; i++) {
		node_pointer p = graph[i];
		printf("%d ", i);
		while (p) {
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
	printf("\n");*/

	int input;

	while (1) {
		scanf("%d", &input);
		if (input == -1) {
			break;
		}
		vis(visited, n);
		dfs(graph, input, visited);
		printf("\n");
	}
	

	
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

void push(Stack* s, int item1, int item2) {
	stackNodePointer temp = (stackNodePointer)malloc(sizeof(stackNode));
	temp->src = item1;
	temp->dst = item2;
	temp->link = s->top;
	s->top = temp;
}

stackNode pop(Stack* s) {
	if (is_empty(s)) {
		printf("stack empty\n");
	}
	else {
		stackNodePointer temp = s->top;
		stackNode data;
		data.src = temp->src;
		data.dst = temp->dst;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}

void makeGraph(int src, int dst, int visited[]) {
	node_pointer cur = graph[src];
	node_pointer ptr = (node_pointer)malloc(sizeof(node));
	if (visited[src] == 0) {
		//printf("src %d NULL\n", src);
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

void dfs(node_pointer graph[], int s, int visited[]) {
	if (graph[s] == NULL) {
		printf("%d", s);
		return;
	}
	node_pointer temp = NULL;
	stackNode data;
	Stack S;
	int item1, item2, cnt = 1;
	init(&S);
	temp = graph[s];
	item1 = s;
	item2 = temp->vertex;
	printf("%d ", item1);
	printf("%d ", item2);
	push(&S, item1, item2);
	//printf("--------------push %d %d\n", item1, item2);
	visited[s - 1] = 1;
	
	
	while (1) {
		//printf("%d ", temp->vertex);
		//printf("cnt%d\n", cnt);
		if (cnt >= 4) return;
		if (visited[temp->vertex - 1] == 1) {
			if (temp->link == NULL) {
				data = pop(&S);
				temp = graph[data.src];
				//printf("\n---------------pop %d %d\n", data.src, data.dst);
			}
			else {
				temp = temp->link;
				item2 = temp->vertex;
				if (visited[temp->vertex - 1] == 0) {
					printf("%d ", item2);
					push(&S, item1, item2);
					//printf("\n--------------push %d %d\n", item1, item2);
					cnt++;
				}
			}
		}
		else {
			item1 = temp->vertex;
			temp = graph[temp->vertex];
			item2 = temp->vertex;
			if (visited[item2 - 1] == 0) {
				printf("%d ", item2);
				push(&S, item1, item2);
				//printf("\n--------------push %d %d\n", item1, item2);
				cnt++;
			}
			visited[item1 - 1] = 1;
			
		}
	}
}

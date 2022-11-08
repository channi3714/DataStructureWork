#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACKS 100 /* maximum number of stacks */
#define IS_FULL(temp) (!(temp))
#define IS_EMPTY(temp) (!(temp))

typedef struct {
	char key;
	/* other fields */
} element;
typedef struct stack* stack_pointer;
typedef struct stack {
	element item;
	stack_pointer link;
}stack;
stack_pointer top[MAX_STACKS];

void push(stack_pointer* top, element item);
element pop(stack_pointer* top);

int main(void) {
	char brackets[30];
	int len, res;

	scanf("%s", brackets);
	len = strlen(brackets);

	res = bracket(brackets, len);
	printf("res : %d\n", res);


	return 0;
}

int bracket(char* br, int len) {
	char c;
	int total = 0, calc = 1;
	element val1, val2;
	stack_pointer temp = *top;
	for (int i = 0; i < len; i++) {
		temp = *top;
		val1.key = br[i];
		if (br[i] == '(') {
			push(top, val1);
			calc *= 2;
		}
		else if (br[i] == '[') {
			push(top, val1);
			calc *= 3;
		}
		else if (br[i] == ')') {
			if (IS_EMPTY(temp)) {
				return 0;
			}
			else if ((*top)->item.key == '[') {
				return 0;
			}
			if (br[i - 1] == '(') {
				total += calc;
			}
			val2 = pop(top);
			calc /= 2;
		}
		else if (br[i] == ']') {
			if (IS_EMPTY(temp)) {
				return 0;
			}
			else if ((*top)->item.key == '(') {
				return 0;
			}
			if (br[i - 1] == '[') {
				total += calc;
			}
			val2 = pop(top);
			calc /= 3;
		}
		printf("total : %d, calc : %d\n", total, calc);
	}
	temp = *top;
	if (!IS_EMPTY(temp)) {
		printf("top is NULL");
		return 0;
	}
	return total;
	/*for (int i = 0; i < len; i++) {
		val1.key = br[i];
		if (val1.key == '(' || val1.key == '[') {
			push(top, val1);
		}
		else if (val1.key == ')' || val1.key == ']') {
			if (IS_EMPTY(top)) {
				return 0;
			}
			val2 = pop(top);
			if (val2.key == '(' && val1.key == ')') {
				calc *= 2;
				if (IS_EMPTY(top)) {
					total *= 2;
					continue;
				}
				if ((*top)->item.key == '(' || (*top)->item.key == '[') {
					printf("a\n");
					calc += 2;
				}
				else if ((*top)->item.key == ')' || (*top)->item.key == ']') {
					printf("b\n");
					total += 2;
					total += calc;
					calc = 0;
				}
			}
			else if (val2.key == '[' && val1.key == ']') {
				calc *= 3;
				if (IS_EMPTY(top)) {
					total *= 3;
					continue;
				}
				if ((*top)->item.key == '(' || (*top)->item.key == '[') {
					printf("c\n");
					calc += 3;
				}
				else if ((*top)->item.key == ')' || (*top)->item.key == ']') {
					printf("d\n");
					total += 3;
					total += calc;
					calc = 0;
				}
			}
		}
		printf("%d %d\n", calc, total);
	}*/
}

void push(stack_pointer* top, element item)
{
	/* push an element to the top of the stack */
	stack_pointer temp = (stack_pointer)malloc(sizeof(stack));
	if (IS_FULL(temp)) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->item = item;
	temp->link = *top;
	*top = temp;
}

element pop(stack_pointer* top)
{
	/* pop an element from the stack */
	stack_pointer temp = *top;
	element item;
	if (IS_EMPTY(temp)) {
		fprintf(stderr, "The stack is empty\n");
		exit(1);
	}
	item = temp->item;
	*top = temp->link;
	free(temp);
	return item;
}
#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef struct Stack {
    int *data;
    int size, top;
} Stack;

void init_stack(Stack *stack, int n) {
    stack->data = (int *)malloc(sizeof(int) * n);
    stack->size = n;
    stack->top = -1;
}

int push_stack(Stack *stack, int value) {
    if (stack->top >= stack->size - 1) {
        return ERROR;
    }
    ++(stack->top);
    stack->data[stack->top] = value;
    return OK;
}
int empty_stack(Stack *stack) {
    return stack->top == -1;
}

int top_stack(Stack *stack) {
    return stack->data[stack->top];
}

void pop_stack(Stack *stack) {
    if (empty_stack(stack)) {
        return ERROR;
    }
    --(stack->top);
}
void clear(Stack *stack) {
    free(stack->data);
    free(stack);
}

int main() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    int n, m, id = 0, flag = 1;
    scanf("%d", &n);
    init_stack(stack, n + 3);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        while (m > id) {
            ++id;
            push_stack(stack, id);
        }
        if (empty_stack(stack) || top_stack(stack) != m) {
            flag = 0;
        }
        pop_stack(stack);
    }
    clear(stack);
    printf("%s", flag ? "YES" : "NO");
    return 0;
}

#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1

typedef enum {
    NUMBER,
    OPERATOR
} ENUM_DATA_TYPE;

typedef struct {
    ENUM_DATA_TYPE dt;
    int value;
} Node;

typedef struct {
    Node *data;
    int size, top;
} Stack;

void init(Stack *s, int n) {
    s->data = (Node *)malloc(sizeof(Node) * n);
    s->size = n;
    s->top = -1;
}

int push(Stack *s, Node value) {
    if(s->size - 1 <= s->top) {
        return ERROR;
    }
    s->data[++(s->top)] = value;
    return OK;
}

int pop(Stack *s) {
    if(empty(s)) {
        return ERROR;
    }
    --(s->top);
    return OK;
}

Node top(Stack *s) {
    return s->data[s->top];
}

int empty(Stack *s) {
    return s->top == -1;
}

void clear(Stack *s) {
    free(s->data);
    free(s);
}

int precede(int opr1, int opr2) {
    int rank1, rank2;
    if(opr1 == '+' || opr1== '-') {
        rank1 = 1;
    } else {
        rank1 = 2;
    }
    if (opr2 == '+' || opr2 == '-') {
        rank2 = 1;
    } else {
        rank2 = 2;
    }
    return rank1 > rank2;
}

int operate(int opr1, int a, int b) {
    switch(opr1) {
        case '+':return a + b;
        case '-':return b - a;
        case '*':return a * b;
        case '/':return b / a;
    }
    return 0;
}

int main() {
    char *buffer = (char *)malloc(22), *pre_ptr;
    scanf("%s", buffer);
    pre_ptr = buffer;
    Node *polish_arr = (Node *)malloc(sizeof(Node) * strlen(buffer));
    int polish_num = 0;
    Stack *s_opr = (Stack *)malloc(sizeof(Stack));
    Node data_node;
    init(s_opr, strlen(buffer));
    while(*buffer) {
        if(isdigit(buffer[0])) {
            data_node.dt = NUMBER;
            data_node.value = buffer[0] - '0';
            polish_arr[polish_num++] = data_node;
        } else {
            while(!empty(s_opr) && !precede(buffer[0], top(s_opr).value)) {
                data_node = top(s_opr);
                pop(s_opr);
                polish_arr[polish_num++] = data_node;
            }
            data_node.dt = OPERATOR;
            data_node.value = buffer[0];
            push(s_opr, data_node);
        }
        ++buffer;
    }
    while (!empty(s_opr)){
        data_node = top(s_opr);
        pop(s_opr);
        polish_arr[polish_num++] = data_node;
    }
    for (int i = 0; i < polish_num; ++i) {
        if(polish_arr[i].dt == NUMBER) {
            push(s_opr, polish_arr[i]);
        } else {
            int a, b;
            a = top(s_opr).value;
            pop(s_opr);
            b = top(s_opr).value;
            pop(s_opr);
            data_node.dt = NUMBER;
            data_node.value = operate(polish_arr[i].value, a, b);
            push(s_opr, data_node);
            
        }
    }
    printf("%d\n", top(s_opr).value);
    clear(s_opr);
    free(pre_ptr);
    return 0;
}

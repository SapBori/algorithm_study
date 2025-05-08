#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;  // Node안에서 자식 노드 및 자신을 참조하려면 struct 붙이기
}Node;

typedef struct Stack{
    Node *top; 
}Stack;

void InitStack(Stack *stack) {
	stack->top=NULL; 
    // 첫 노드 초기화
}
int IsEmpty(Stack *stack){
	return stack->top==NULL;
    // 첫 노드가 비었다면 스택은 비었음(큐는 다름)
}
void Push(Stack *stack, int data){
	Node *now = (Node *)malloc(sizeof(Node));
    
    now->data = data;
    now->next = stack->top; // 나중에 없애게 되면 top의 그 전 노드를 주기 위해서!
    stack->top= now; // 맨 위에가 now 노드로 설정!

    // stack의 top 의 next = Now 노드가 되는 것
}
int Pop(Stack *stack){
	if(stack->top==NULL) {
    	printf("꽉 찼다!!");
        return 0;
    }
    int re;
    Node *now;
    now = stack->top;   // now노드가 stack의 맨 위를 가져감
    re = now->data;     // Stack의 맨 위 노드의 값이 가져올 값

    stack->top = now->next; //현재 Stack의 top는 now가 아니므로 now->next를 stack->top의 next로 지정  
    // 맨 마지막의 next에는 그 전 노드의 주소가 들어있다!!
    free(now);
    return re;
}
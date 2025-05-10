#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 1000
typedef struct{
    int x;
    int y;
    int sum;
}Fruit;

// Stack을 써야 할 경우 tyepdef struct에 구조체 이름을 두번 작성해야함
typedef struct S_Fruit{
    int x;
    int y;
    int sum;
    struct S_Fruit *next;
}S_Fruit;

typedef struct{
    int f;
    int r;
    Fruit data[MAX_LEN];
}Queue;
Fruit deque(Queue* q){
    return q->data[q->f++];
}
void enque(Queue* q, Fruit now){
    q->data[q->r++] = now;
}
bool isEmpty(Queue * q){
    return q->f == q->r;
}

typedef struct{
    S_Fruit *top;
}Stack;
S_Fruit pop(Stack* s){
    S_Fruit* now_f;
    now_f = s->top;
    s->top = now_f->next;

    return *now_f;
}
void push(Stack* s, S_Fruit f){
    S_Fruit* new_f;
    
    // 데이터 복사
    new_f->x = f.x;
    new_f->y = f.y;
    new_f->sum = f.sum;

    // Stack에 들어있는 현재 데이터를 새로만든 구조체의 next에 복사
    new_f->next = s->top; 

    s->top= new_f; // Stack에 방금 만든 new_f를 저장
}


int square[MAX_LEN][MAX_LEN];
int max_sum = 0;
int main(){
    int square_int = 0;
    scanf("%d", &square_int);
    Queue f_queue;
    Stack f_stack;
    f_stack.top = NULL;

    char array[MAX_LEN];
    memset(square, 0, sizeof(square));
    memset(array, 0, sizeof(array));
    for (int i=0; i<square_int;i++){
        for (int j=0; j<square_int; j++){
            scanf("%s",array);
            int fruit =0;
            fruit = atoi(array);
            square[i][j] = fruit;
        }
    }
    S_Fruit f;
    f.x = 0;
    f.y = 0;
    f.sum = square[f.x][f.y];
    f.next = NULL;
    push(&f_stack, f);
    // enque(&f_queue, f);
    int dx[2] = {1, 0};
    int dy[2] = {0, 1};
    while(!isEmpty(&f_queue)){  
        S_Fruit new_f = pop(&f_stack);
        if (new_f.x == square_int-1 && new_f.y == square_int-1){
            break;
        }
        for (int i = 0; i < 2; i++){
            int mx,my,new_cnt;
            mx = new_f.x + dx[i];
            my = new_f.y + dy[i];
            new_cnt = new_f.sum + square[mx][my];
            printf("%d %d %d\n",mx,my,new_cnt);
            if (mx < 0 || my < 0 || mx >= square_int || my >=square_int){
                continue;
            }
            if (new_cnt > max_sum){
                max_sum = new_cnt;
            }
            new_f.x = mx;
            new_f.y = my;
            new_f.sum = new_cnt;
            push(&f_stack, new_f);
        }
    }
    printf("%d" ,max_sum);
    // 수로는 무조건 0,0에서 설치 시작 + 현위치에서 오른쪽(+1,0) 또는 아래로(0,+1) 설치 가능 + 수로는 제한이 없음 (맨 마지막 : 격자 끝, 격자 끝에 도달 하거나 설치 불가능하면 종료)
    // 스프링쿨러는 수로설치한 곳에만 설치가능
}

//https://softeer.ai/practice/7369
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// https://www.acmicpc.net/problem/3190
struct Position{
    int x;
    int y;
    int dir[2];
}; 

typedef struct SnakeQueue{
    struct Position* p[101] ;
    int f;
    int r;
    int count;
}Queue;

void enque(Queue* queue, void* data){
    // struct Position* new_position = malloc(sizeof(struct Position));
    queue->p[queue->r++] = (Queue *)data;
    queue->count++;
}
struct Position* deque(Queue* queue){
    queue->count--;
    return queue->p[queue->f++];
}
void push(Queue* queue, void* data){
    struct Position* temp = malloc(sizeof(struct Position*));
    temp = queue->p[queue->f];
    int front = queue->f;
    int rear = queue->r;
    if (queue->count == 0){
        enque(&queue, data);
    }
    else {
        for(int i=queue->count; i>0; i--){
        queue->p[rear+i+1] = queue->p[rear+i];
        queue->p[rear+i] = queue->p[rear+i-1]; 
        }
    queue->p[rear-front+1] = temp;
    }
     
}
struct Position* pop(Queue* queue){
    queue->count--;
    return queue->p[queue->f--];
}
bool isEmpty(Queue* queue){
    return queue->count ==0;
}

bool isFull(Queue* queue){
    return queue->count == 101;
}
bool box[101][101];
int main(){
    Queue* queue = (Queue *)malloc(sizeof(Queue));
    memset(&box, 0, sizeof(box));

    int square_size= 0;
    int time = 0;
    int total_apple = 0;
    int total_move = 0;
    scanf("%d", &square_size);
    bool snake_visited[square_size][square_size];
    memset(&snake_visited, 0, sizeof(snake_visited));
    rewind(stdin);

    scanf("%d", &total_apple);
    rewind(stdin);
    
    int dir[2][4]={{1,-1,0,0},{0,0,-1,1}};
    for (int i=0; i<total_apple; i++){
        int ax = 0;
        int ay = 0;
        scanf("%d %d", &ax, &ay);
        box[ay-1][ax-1] = true;
        rewind(stdin);
    }
    scanf("%d", &total_move);
    rewind(stdin);
    int move_timing[total_move];
    char move_stg[total_move];
    memset(move_timing,0, sizeof(move_timing));
    memset(move_stg,0, sizeof(move_stg));

    for (int s=0; s<total_move; s++){
        scanf("%d %c",&move_timing[s], &move_stg[s]);
        while (getchar() != '\n'); // 입력 버퍼 정리
    }
    int mov_dir = 0;
    int mov_stg_cnt = 0;
    struct Position* start = malloc(sizeof(struct Position*));
    start->dir[0] = 1;
    start->dir[1] = 0;
    start->x = 0;
    start->y = 0;
    box[start->y][start->x] = 1;
    
    enque(&queue, start);
    // 0 -> 우
    // 1 -> 좌
    // 2 -> 상
    // 3 -> 하
    while(1){
        time++;
        bool ate_flag=false;
        struct Position* head = deque(&queue);
        struct Position* tail = malloc(sizeof( struct Position*));
        int dx = head->x+head->dir[0];
        int dy = head->y+head->dir[1];
        
        printf("%d : %d %d\n",time, dx, dy);
        if(dx <0 || dx >=square_size || dy<0 || dy>=square_size){
            // 벽에 부딪히는 순간
            break;
        }
        if(snake_visited[dy][dx]){
            // 자기 몸에 부딪히는 순간
            break;
        }
        // // 머리가 도착
        snake_visited[dy][dx]= true;

        if (box[dy][dx]){
            // 머리가 사과 먹은 경우
            box[dy][dx]= false;

        }
        else {
            // 먹지 못함
            snake_visited[tail->y][tail->x] = false;
            tail->y = tail->y + tail->dir[1];
            tail->x = tail->x + tail->dir[0];
            
        }
       
        // // 꼬리 이동
        // int tdx = snake->tail.x+snake->head.dir[0];
        // int tdy = snake->tail.y+snake->head.dir[1];

        if (time == move_timing[mov_stg_cnt] && mov_stg_cnt <= sizeof(move_stg)){
            switch (move_stg[mov_stg_cnt])
            {
            case 'D':
                /* code */
                switch (mov_dir)
                {
                case 0:
                    // 우 방향에서 오른쪽 90도 >> 하
                    mov_dir = 3;
                    /* code */
                    break;
                case 1:
                    // 좌 방향에서 오른쪽 90도 >> 상
                    mov_dir = 2;
                    break;
                case 2:
                    // 상 방향에서 오른쪽 90도 >> 우
                    mov_dir = 0;
                    /* code */
                    break; 
                case 3:
                    // 하 방향에서 오른쪽 90도 >> 좌
                    mov_dir = 1;
                    /* code */
                    break;
                default:
                    break;
                }
                break;
            case 'L':
            switch (mov_dir)
                {
                case 0:
                    // 우 방향에서 왼쪽 90도 >> 상
                    mov_dir = 2;
                    /* code */
                    break;
                case 1:
                    // 좌 방향에서 왼쪽 90도 >> 하
                    mov_dir = 3;
                    break;
                case 2:
                    // 상 방향에서 왼쪽 90도 >> 좌
                    mov_dir = 1;
                    /* code */
                    break; 
                case 3:
                    // 하 방향에서 왼쪽 90도 >> 우
                    mov_dir = 0;
                    /* code */
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            mov_stg_cnt++;
            head->x = dx;
            head->y = dy;
            head->dir[0] = dir[0][mov_dir];
            head->dir[1] = dir[1][mov_dir];
            printf("Turn Diretion x : %d y : %d\n",dir[0][mov_dir],dir[1][mov_dir]);
        }
        enque(&queue, head);
    }
    printf("%d ", time);
}
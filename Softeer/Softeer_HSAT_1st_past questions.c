#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// https://softeer.ai/practice/6275
typedef struct{
    int h;
    int w;
    unsigned direction; // 배열 인덱스로 사용 -> 음수 배제
}Position;

typedef struct {
    Position data[1000];
    int top;
}Stack;

void stack_init(Stack *s){
    s-> top = -1;
}
int isStackFull(Stack *s){
    return s->top == sizeof(s->data)/sizeof(int)-1;
}

int isStackEmtpy(Stack *s){
    return s->top == -1;
}
Position pop(Stack *s){
    Position p;
    if (isStackEmtpy(s)){
        printf("Emtpy\n");
    }
    else {
        p = s->data[s->top--];
    }
     return p;
}
void push(Stack* s, Position data){
    if (isStackFull(s))
        printf("Overflow\n");
    else {
        s->top++;
        s->data[s->top] = data;
    }
}
Position peek(Stack *s){
    Position p;
   if (isStackEmtpy(s)){
        printf("Emtpy\n");
    }
    else {
        p = s->data[s->top];
       
    }
    return p;
}

typedef struct{
    Position data[1000];
    int cnt;
    int f;
    int r;
}Queue;

bool isQueueEmpty(Queue *q){
    return q->cnt <= 0;
}
bool isQueueFull(Queue *q){
    return q->cnt == sizeof(q->data);
}
void enque(Queue *q, Position d){
    if(isQueueFull(q)){
        printf("Queue is Full\n");
    }
    else {
        q->cnt++;
        q->data[q->r++] = d;
    }
}

Position deque(Queue *q){
    if(isQueueEmpty(q)){
        printf("Queue is Empty\n");
    }
    else {
        q->cnt--;
        return q->data[q->f++];
    }
}
int queue_storagy(Queue *q){
    return q->cnt;
}
void Queue_Init(Queue *q){
    q->cnt= 0;
    q->f= 0;
    q->r = 0;
}
int direction[2][4] = {{1,0,-1,0},{0,1,0,-1}}; // 방향
char back_direction[1000];
char arrow[4] = {'>','v','<','^'};
Position p[1000];   // 백트래킹용
int main(){
    int h,w;
    scanf("%d %d",&h,&w);
    char map[h][w];
    memset(map, 0, sizeof(map));
    memset(back_direction, 0, sizeof(back_direction));
    
    bool visited[h][w];
    memset(visited, 0, sizeof(visited));
    
    Queue queue;
    Queue_Init(&queue);
    for(int y=0; y<h;y++){
        scanf("%s",map[y]);
    }
    Position temp;
    // 처음 좌표 찾기
    int back_cnt = 0;
    for (int y=0; y<h; y++){
        for(int x=0; x<w; x++){
            if(map[y][x]== '#'){
                int cnt = 0;
                for(int d =0; d<4; d++){
                    int dx,dy;
                    dy = y+direction[1][d];
                    dx = x+direction[0][d];
                    if(dy >= h || dy <0 || dx >=w || dx <0){
                        continue;
                    }
                    if(map[dy][dx] == '#'){
                        cnt++;
                        continue;
                    }
                }
                if(cnt == 1){
                    // 어떤 좌표에서 주변의 '#'이 한개만 있는 경우
                    // 2칸씩 이동하기에 이어진 경우 주변에 무조건 2개 이상
                    temp.w = x;
                    temp.h = y;
                    p[back_cnt++] = temp;
                    continue; // 같은 라인에 있는 경우도 있기에 continue로
                }
            } 
        }
    }
    for (int i=0; i< back_cnt; i++){
        // printf("%d %d\n", p[i].h+1,p[i].w+1);
        for (int j=0; j<4; j++){
            int dx,dy;
            dy = p[i].h+direction[1][j];
            dx = p[i].w+direction[0][j];
            if(dy >= h || dy <0 || dx >=w || dx <0){
                continue;
            }
            if(map[dy][dx] == '#'){
                p[i].direction = j;
            }
        }
        // printf("Direction : %c\n",arrow[p[i].direction]);
    }
    Position start = {p[0].h, p[0].w, p[0].direction};
    Position end =   {p[1].h, p[1].w, p[1].direction};
    enque(&queue, start);
    memset(&p, 0, sizeof(p));
    back_cnt = 0;
    // 길 탐색 시작 
    while(!isQueueEmpty(&queue)){
        Position now;
        now = deque(&queue);
        visited[now.h][now.w] = true;
        // printf("Direction : %c\n",arrow[now.direction]);
        if (now.h == end.h && now.w== end.w){
            break;
        }
        for (int di=0; di<4; di++){
            int dx,dy;
            dy = now.h+direction[1][di];
            dx = now.w+direction[0][di];
            if(dy >= h || dy <0 || dx >=w || dx <0){
                continue;
            }
            if(map[dy][dx] == '#' && !visited[dy][dx]){
                Position new;
                visited[dy][dx] = true; // #이 있는 겨우는 방문 했다고 판단, 어차피 새로 이동한 노드에서도 visited 판단
                // 가장 큰 문제 현재가 0이고 di가 3일때 ->
                if (now.direction == 0 && di == 3){
                    now.direction = 3;
                    back_direction[back_cnt] = 'L';
                    back_cnt++;
                }
                else if(now.direction == 3 && di == 0){
                    now.direction = 0;
                    back_direction[back_cnt] = 'R';
                    back_cnt++;
                }
                else if(now.direction < di){
                    // 예시 di 2, now가 0,1
                    while(now.direction != di){
                        now.direction++;
                        now.direction%=4;
                        back_direction[back_cnt] = 'R';
                        back_cnt++;
                    }
                }
                else if(now.direction > di){
                    // 예시 di 0, now가 1,2
                    while(now.direction != di){
                        now.direction--;
                        now.direction%=4;
                        back_direction[back_cnt] = 'L';
                        back_cnt++;
                    }
                }
                // 2칸 이동 한것으로 한번 더 더함
                new.h = dy+direction[1][di];
                new.w = dx+direction[0][di];
                new.direction = now.direction;
                back_direction[back_cnt] = 'A';
                back_cnt++;
                // 다음 좌표 큐에 추가
                enque(&queue,new);
            }
        } 
    }
    printf("%d %d\n%c\n",(start.h)+1,1+(start.w),arrow[start.direction]);
    puts(back_direction);
    //시작 좌표는 좌우가 # 가 1개만 잇거나 상하가 1개만 있는 경우 >> 방향까지 정할 수 있음

};


//1. 로봇이 어느 위치든 상관없음 (최소 문자 길이만 유지)
//2. #으로 표시된 지점을 모두 지나야함
//3. A -> 방향으로 2칸 전진, R(시계),L(반시계)에서 회전, 0-1 => 3이 되면 됨
//4. 이동 명령이 최소이면 로봇의 좌표는 상관이 없으나 시작방향에 따라 명령의 개수가 달라짐
//5. 숫자는 1부터 시작 해야함 (출력시 +1)

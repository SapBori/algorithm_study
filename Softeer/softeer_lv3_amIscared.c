#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 1004

int mage_x,mage_y;
char wall = '#';
char people = 'N';
char ghost = 'G';
char exit_c = 'D';
int ghost_num = 0;
int walls_num =0;
int dir_x[4] = {-1,0,1,0};
int dir_y[4] = {0,1,0,-1};
char mage[1004][1004];
typedef struct{
    int x;
    int y;
}Position;
typedef struct{
    int f;
    int r;
    Position data[MAX_LEN];
}Queue;

Queue n_queue;
int namwo_visited[1004][1004];

Queue ghost_queue;
int ghost_visited[1004][1004];

void queue_init(Queue* queue){
    queue->f = 0;
    queue->r = 0;
    memset(queue->data, 0, sizeof(Position)*MAX_LEN);
}
Position n_pop(){
    return n_queue.data[n_queue.f++];
}
void n_push(Position pos){
    n_queue.data[n_queue.r++]= pos; 
}
Position g_pop(){
    return ghost_queue.data[ghost_queue.f++];
}
void g_push(Position pos){
    ghost_queue.data[ghost_queue.r++]= pos; 
}
bool n_isEmpty(){
    return n_queue.f == n_queue.r;
}
bool n_isFull(){
    return n_queue.r == MAX_LEN;
}
bool g_isEmpty(){
    return ghost_queue.f == ghost_queue.r;
}
bool g_isFull(){
    return ghost_queue.r == MAX_LEN;
}
int namwo_shortest_sec = 0;
int ghost_shortest_sec = 0;

int ghost_find_path(Position exit){
    int x,y;
    int move_x,move_y;
    while(!g_isEmpty()){
        Position new_ghost = g_pop();
        for (int i=0; i<4; i++){
            move_x = new_ghost.x + dir_x[i];
            move_y = new_ghost.y + dir_y[i];

            if (move_y < 0 || move_y >= mage_y || move_x < 0 || move_x >= mage_x){
                continue;
            }
            if(ghost_visited[move_y][move_x]==0) {
                ghost_visited[move_y][move_x]=ghost_visited[new_ghost.y][new_ghost.x]+1;    
                // 최종 거리만 확인
                new_ghost.x = move_x;
                new_ghost.y = move_y;
                g_push(new_ghost);
            }
        }
    }
    return ghost_visited[exit.y][exit.x];
}
int namwo_find_path(Position exit){
    int x,y;
    int move_x,move_y;
    while(!n_isEmpty()){
        Position now_namwo = n_pop();
        for (int i=0; i<4; i++){
            move_x = now_namwo.x + dir_x[i];
            move_y = now_namwo.y + dir_y[i];

            if (move_y < 0 || move_y >= mage_y || move_x < 0 || move_x >= mage_x || mage[move_y][move_x]=='#'){
                continue;
            }
            if(namwo_visited[move_y][move_x]==0 && namwo_visited[now_namwo.y][now_namwo.x]+1 < ghost_visited[move_y][move_x]) {
                namwo_visited[move_y][move_x]=namwo_visited[now_namwo.y][now_namwo.x]+1;    
                // 최종 거리만 확인
                now_namwo.x = move_x;
                now_namwo.y = move_y;
                n_push(now_namwo);
            }
        }
    }
    return namwo_visited[exit.y][exit.x];
}

int main(){
    
    Position pos_exit;
    Position namwo;
    Position ghost;
    queue_init(&n_queue);
    queue_init(&ghost_queue);
    memset(namwo_visited, 0, sizeof(namwo_visited));
    memset(ghost_visited, 0, sizeof(ghost_visited));
    scanf("%d %d", &mage_y,&mage_x);
   
    memset(mage, 0, sizeof(mage));

    for (int y= 0 ; y < mage_y; y++){
        scanf("%s", mage[y]);
        for(int x =0; x < mage_x; x++){
            if (mage[y][x] =='D'){
                pos_exit.x=x;
                pos_exit.y=y;
            }
            else if (mage[y][x] == 'N'){
                namwo.x = x;
                namwo.y = y;
                namwo_visited[y][x]++;
                n_push(namwo);
            }
            else if(mage[y][x] == 'G'){
                ghost.x = x;
                ghost.y = y;
                ghost_visited[y][x]++;
                g_push(ghost);
            }
        }
    }
    ghost_shortest_sec = ghost_find_path(pos_exit);
    namwo_shortest_sec = namwo_find_path(pos_exit);

    ghost_shortest_sec > namwo_shortest_sec ? printf("No") : printf("Yes");
}
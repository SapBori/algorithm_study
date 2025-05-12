#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//https://www.acmicpc.net/problem/14499


int row = 0;
int col = 0;
// 동쪽은 1, 서쪽은 2, 북쪽은 3, 남쪽은 4
// 좌 1, 우 2, 상 3, 하 4
// 
int direction[6][4]= {{4,3,5,2},{4,3,1,6},{1,6,5,2},{6,1,5,2},{4,3,6,1},{4,3,2,5}};
// 0~5에서 우좌상하로 갈때 실제 넘버링
int dice[6] = {0,0,0,0,0,0};
int other_side[6][2] = {{1,6},{2,5},{3,4},{4,3},{5,2},{6,1}};
// 0: 윗면, 1: 아랫면
int main(){
    int n,m;
    int x,y;
    int k;
    scanf("%d %d %d %d %d",&n,&m, &x, &y, &k);

    int map[n][m];
    int order[k];
    memset(map, 0, sizeof(map));
    for(int i=0; i<n; i++){
        char number[m];
        for(int j=0; j<m; j++){
            scanf("%s",&number);
            map[i][j] = atoi(number);
        }
    }
    memset(dice, 0, sizeof(dice));

    for(int r = 0; r <k; r++){
        char direction[2];
        scanf("%s",&direction);
        order[r] = atoi(direction);
    }
    int order_cnt =0;
    int before_dice =0;    // 윗면 기준
    bool pass_flag = false;
    int start_under = other_side[before_dice][1];
    dice[start_under-1] = map[y][x];

    while(order_cnt<k){
        // printf("Now Order : %d\n", order[order_cnt]);
        switch(order[order_cnt]){
            case 1 :
                if(x+1 >= m){
                    // 명령 패스
                    pass_flag= true;
                }
                x+=1;
                break;
            case 2 :
                if(x-1 < 0){
                     // 명령 패스
                    pass_flag= true;
                }
                
                x-=1;
                break;
            case 3 :
                if(y-1 < 0){
                    // 명령 패스
                    pass_flag= true;
                }
                
                y-=1;
                break;
            case 4 :
                if(y+1 >= n){
                    // 명령 패스
                    pass_flag= true;
                }
                
                y+=1;
                break;
        }

        // 이동 -> 윗 출력, 아래면 숫자 복사
    
        if (!pass_flag){
            // 정상 이동
            int map_number = map[y][x];
            int o = order[order_cnt];   // 이동 명령=
            int now_dice = direction[before_dice][o-1];    // 다음 주사위 윗면 위치(눈값 x)
            int under = other_side[now_dice-1][1];    // 현재 위치의 주사위 아랫면
            
            // printf("Under Position %d UnderValue : %d\n",under, dice[under-1]);
            printf("Now dice %d, Value : %d ", now_dice,dice[now_dice-1]);
            
                // 이동했을 때 찍히는 값을 주사위눈에 넣기
            // printf("%d\n",dice[now_dice-1]);
            dice[under-1]= map_number;
            printf("Under Pos %d Value : %d\n",under, dice[under-1]);
            before_dice = now_dice-1;
        }
        else {
            // printf("Not Moved Now dice %d -> Current DiceValue : ",now_dice+1);
            // printf("%d\n",dice[now_dice]);
            pass_flag = false;
        }
        order_cnt++;
    }
    // 맵 출력
    // for(int i=0; i<n; i++){
    //     for(int j=0; j<m; j++){
    //         printf("%d ",map[i][j]);       
    //     }
    //     printf("\n");
    // }
    
};
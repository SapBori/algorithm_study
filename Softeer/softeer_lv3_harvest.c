#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 1000

int square[MAX_LEN][MAX_LEN];
int array_sum[MAX_LEN][MAX_LEN][2];
int max_sum = 0;
int main(){
    int square_int = 0;
    scanf("%d", &square_int);
    char array[MAX_LEN];
    memset(square, 0, sizeof(square));
    memset(array, 0, sizeof(array));
    memset(array_sum, 0, sizeof(array_sum));
    for (int i=0; i<square_int;i++){
        for (int j=0; j<square_int; j++){
            scanf("%s",array);
            int fruit =0;
            fruit = atoi(array);
            square[i][j] = fruit;
            if (i ==0 || j == 0 ){
                array_sum[i][j][0] = fruit;
                array_sum[i][j][1] = fruit*2;
            }
            else {
                array_sum[i][j][0] = array_sum[i-1][j][1] > array_sum[i][j-1][1] ? (array_sum[i-1][j][0]+fruit) : (array_sum[i][j-1][0] + fruit) ;
                array_sum[i][j][1] = array_sum[i-1][j][1] > array_sum[i][j-1][1] ? (array_sum[i-1][j][0]+(fruit*2)) : (array_sum[i][j-1][0] + (fruit*2)) ;
                
            }
        }
    }
    
    printf("%d" , array_sum[square_int-1][square_int-1][1]);
    // 수로는 무조건 0,0에서 설치 시작 + 현위치에서 오른쪽(+1,0) 또는 아래로(0,+1) 설치 가능 + 수로는 제한이 없음 (맨 마지막 : 격자 끝, 격자 끝에 도달 하거나 설치 불가능하면 종료)
    // 스프링쿨러는 수로설치한 곳에만 설치가능
}

//https://softeer.ai/practice/7369
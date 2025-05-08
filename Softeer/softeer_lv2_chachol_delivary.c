#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 200
int compare (const void* a, const void* b){
    int num1 = *(int*)a;
    int num2 = *(int*)b;
    if (num1 > num2 ){
        return 1;
    }
    else if(num1 < num2){
        return -1;
    }
    else {
        return 0;
    }
}
int main(){
    int house_num;
    
    scanf("%d",&house_num);
    int house_list[house_num];
    char input_buffer[MAX_LENGTH];
    memset(input_buffer, 0, sizeof(input_buffer));
    int before_index = 0;
    int house_index = 0;
    char temp_str[3];
    for (int i=0; i<house_num; i++){
        scanf("%s",input_buffer);
        house_list[house_index++] = atoi(input_buffer);
    }
    int min_divider = 2;
    qsort(house_list, house_num, sizeof(int), compare);
    int last_house_num = house_num;
    int max_divided_cnt = 0;
    int house_max = house_list[house_num-1];
    for (int index = 0; index <= house_max; index++){
        int now_cnt = 0;
        for (int j =0; j<house_num; j++){
            if (house_list[j]% min_divider ==0){
                now_cnt++;
            }
        }
        if (now_cnt > max_divided_cnt ){
            max_divided_cnt= now_cnt;
        }
        if (min_divider>=house_max){
            break;
        }
        min_divider++;
    }
    printf("%d", max_divided_cnt);
    
}
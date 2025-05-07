#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// https://softeer.ai/practice/11001
typedef struct {
    int x_arr;
    int y_arr;
} Number;

int intcompare(const void *a , const void *b) 
{ 
    Number* num1 = (Number*) a;
    Number* num2 = (Number*) b;
    if (num1->x_arr > num2->x_arr ){
        return 1;
    }
    else if (num1->x_arr < num2->x_arr){
        return -1;
    }
    else {
        if (num1->y_arr > num2->y_arr){
            return 1;
        }
        else if (num1->y_arr < num2->y_arr){
            return -1;
        }
        else {
            return 0;
        }  
    }
} 
int strcompare(const void *a, const void *b) 
{ 
    return strcmp((char*)a, (char*)b);
}
int main(){
    int num = 0;
    scanf("%d\n", &num);    // 1 <= num <= 1000
    char string[num][8];    // ***.*** >> 8자리
    char x[num][4];
    Number real_num[1001];
    char y[num][4];
    int result_order[num];
    memset(string, 0, sizeof(string));
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    for (int i=0; i<num ; i++){
        scanf("%s", string[i]);
    }
    char point = '.';
    for (int i=0; i<num; i++){
        char *point_add= NULL;
        int point_index;
        point_add = strchr(string[i], point);
        if (point_add != NULL){
            point_index = (int)(point_add- string[i]);
            strncpy(x[i],string[i], point_index);
            strncpy(y[i],string[i]+point_index+1,8-point_index);
            real_num[i].x_arr = atoi(x[i]);
            real_num[i].y_arr = atoi(y[i]);
        }
        else {
            point_index = 0;
            strncpy(x[i],string[i], strlen(string[i])); 
            real_num[i].x_arr = atoi(x[i]);
            real_num[i].y_arr = -1;
        }
    }
    qsort(real_num, num, 4,intcompare);
    qsort(real_num, num, 8,intcompare);
    // // real_num = quickSort(real_num, num/2, num-1);
    for(int i=0; i<num; i++){
        printf("%d.%s\n", real_num[i].x_arr,real_num[i].y_arr);
    }
}

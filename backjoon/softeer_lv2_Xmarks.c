#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
//https://softeer.ai/practice/7703

int main(){
    int n;
    char* result = malloc(500000* sizeof(char *));
    scanf("%d",&n);
    int string_index = 0;
    for(int i=0; i<n; i++){
        char* x1 = malloc(500000* sizeof(char *)); 
        char* x2 = malloc(500000* sizeof(char *));
        scanf("%s %s",x1,x2);
        char *pos1 = (char *)memchr(x1, 'x', 500000);
        char *pos2 = (char *)memchr(x1, 'X', 500000);
        long p1 = pos1 != NULL ? pos1-x1 : -1;
        long p2 = pos2 != NULL ? pos2-x1 : -1;

        if (p1 >=0){
            char ch = *(x2+p1);
            if (ch >= 'a' && ch <= 'z'){
                ch-=32;
            }
            memcpy(result+string_index, &ch, 1);
        }
        else if(p2 >=0){
            char ch = *(x2+p1);
            if (ch >= 'a' && ch <= 'z'){
                ch-=32;
            }
            memcpy(result+string_index, &ch, 1);
        }
        string_index++;
        free(x1);
        free(x2);
    }
    puts(result);
    free(result);
};
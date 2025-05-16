#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Ch{
    char state[5001][102];
    int small[5001];
    int big[5001];
    int stack_flag[5001];
}Check;

typedef struct St
{
    char stack[5001];
    unsigned int top;
    /* data */
}Stack;

int isEmpty(Stack* s){
    if (s->top == 0){
        return 1;
    }
    else {
        return 0;
    }

}
int isFull(Stack* s){
    if (s->top >= 5001){
        return 1;
    }
    else {
        return 0;
    }

}
void push(Stack* s, char ch){
    if (!isFull(s)){
        s->stack[s->top++] = ch;
    }
    
}
char pop(Stack* s){
    if (!isEmpty(s)){
        char temp;
        temp = s->stack[s->top-1];
        s->top--;
        return temp;
    }
    return ' ';
    
}
char peek(Stack* s){
    if (!isEmpty(s)){
        char temp;
        temp = s->stack[s->top-1];
        return temp;
    }
    return ' ';
}

int main(){
    Check braket;
    
    memset(&braket,0, sizeof(Check));
    
    int state_index = 0;
    int end_flag = 0;
    while(1){
        Stack stack;
        memset(&stack,0, sizeof(stack));
        fgets(braket.state[state_index], sizeof(braket.state[0]),stdin);
        int next_flag=0;
        for (int i=0; i<strlen(braket.state[state_index]); i++){
            char ch = braket.state[state_index][i];
            switch (ch)
            {
            case '[':
                push(&stack, ch);
                /* code */
                braket.big[state_index]++;
                break;
            case '(':
                push(&stack, ch);
                /* code */
                braket.small[state_index]++;
                break;
            case ']':
                /* code */
                if(peek(&stack) == '['){
                    pop(&stack);
                    braket.big[state_index]--;
                }
                else {
                    push(&stack, ch);
                }
                break;
            case ')':
                if(peek(&stack) == '(' ){
                    pop(&stack);
                    braket.small[state_index]--;
                }
                else {
                    push(&stack, ch);
                }
                break;
            case '.':
                if(braket.state[state_index][i+1] = '\n'){
                    next_flag = 1;
                }
                break;
            default:
                break;
        
            }
            
            if ( (i ==0 && ch == '.') || state_index>=5000){
                end_flag = 1;
                break;
            }
            if(next_flag){
                break;
            }
        }
        braket.stack_flag[state_index] = stack.top;
        if (end_flag){
            break;
        }
        state_index++;
    }
    for(int i=0; i<state_index; i++){

        if(braket.stack_flag[i] != 0){
            printf("no\n");
        }
        else {
            printf("yes\n");
            continue;
        }
    }
    
};
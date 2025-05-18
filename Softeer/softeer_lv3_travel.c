#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
    int number[2];
    int root;
    char str[2];
}N;

bool visited[5001];
char fav[5001];
char string[5001];
int path[5000][2];
int max_len = 0;
void dfs(N node_list[], N start, int depth){
    visited[start.root-1] = true;
    N left = node_list[start.number[0]-1];
    N right = node_list[start.number[1]-1];
    if (max_len < depth){
        max_len = depth;
    }
    if(!visited[left.root-1] && start.number[0] != 0){
        string[depth] = start.str[0];
        dfs(node_list, left, depth+1);
    }
    else if(!visited[right.root-1] && start.number[1] != 0){
        string[depth] = start.str[1];
        dfs(node_list, right, depth+1);
    }
}

int main(){
    int n,m;
    scanf("%d %d",&n, &m);
    N node_list[n];
    memset(visited, 0, sizeof(visited));
    memset(fav, 0, sizeof(fav));
    memset(path, 0, sizeof(path));
    memset(node_list, 0, sizeof(node_list));
    scanf("%s", fav);
    
    for (int i=0; i<n-1; i++){
        int dep, land;
        char ch;
        scanf("%d %d %c", &dep, &land, &ch);
        node_list[dep-1].root = dep;
        node_list[land-1].root = land;

        if (node_list[dep-1].number[0] == 0){
            node_list[dep-1].number[0] = land;
            node_list[dep-1].str[0] = ch;
        }
        else {
            node_list[dep-1].number[1] = land;
            node_list[dep-1].str[1] = ch;
        }
        if (node_list[land-1].number[0] == 0){
            node_list[land-1].number[1] = dep;
            node_list[land-1].str[0] = ch;
        }
        else {
            node_list[land-1].number[1] = dep;
            node_list[land-1].str[1] = ch;
        }
    }
}


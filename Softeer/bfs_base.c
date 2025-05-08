#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LEN   500

int graph[MAX_LEN][MAX_LEN];
bool visited[MAX_LEN];  //  방문 노드의 방문 여부 저장
int queue[MAX_LEN];     // 방문 노드 저장 
int f=0,r=0;            // queue의 인덱스 변수 
// r -> push에 이용, f -> pop에 이용


void enque(int v){
    queue[r++] = v;
}
int deque(){
    return queue[f++];
}
bool isEmpty(){
    return f==r;
    // 같으면 다 들어감, 다르면 공간이 있음
}


void bfs(int start, int n){
    // start : 시작 노드, n : 탐색 목표 노드
    enque(start);
    visited[start] = true;
    while(!isEmpty()){
        int current = deque();
        
        for (int i=0; i<n; i++){
            int value = 1;
            if (graph[current][i] == value && !visited[i]){
                // 방문을 하지 않았고, 현재 노드의 값이 목표하는 값가 동일한경우
                enque(i);   // 큐에 저장
                visited[i] = true; 
            }
        }
    }
}
void dfs(int node) {
    printf("%d\n", node);
    visited[node] = true;

    for (int i = 0; i < sizeof(graph[node]) / sizeof(graph[node][0]); i++) {
        int neighbor =0; 
        neighbor = graph[node][i];
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
}

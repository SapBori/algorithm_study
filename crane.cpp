#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
queue<pair<int,int>> container_list;
bool visited[51][51];
void bfs(vector<string> storage, string target, int col ,int row){
    pair<int,int> start = {col, row};
    queue<pair<int,int>> bfs_queue;
    int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
   
    bfs_queue.push(start);
    while(!bfs_queue.empty()){
        pair<int,int> queue_data = bfs_queue.front();
        bfs_queue.pop();
        
        visited[queue_data.first][queue_data.second] = true;
        if(storage[queue_data.first][queue_data.second] == target[0]){
            storage[queue_data.first][queue_data.second] = '*';
            container_list.push(make_pair(queue_data.first,queue_data.second));
        }
        for(int i=0; i<4; i++){
            int new_col = queue_data.first+dir[i][0];
            int new_row = queue_data.second+dir[i][1];
            if(new_col< 0 || new_row < 0 || new_col >= storage.size() ||  new_row >= storage[0].size() || !visited[new_col][new_row]){
                continue;
            }
            else {
                if(storage[new_col][new_row] == '*'){
                    bfs_queue.push(make_pair(new_col,new_row));
                }
            }
        }   
    }
}
int solution(vector<string> storage, vector<string> requests) {
    int answer = 0;
    
    answer = storage[0].size() * storage.size();
    int m  = storage[0].size();
    int n = storage.size();
    cout << n << "," << m << endl;
    for (auto target : requests){
        if (target.size() == 1){
            // 지게차
            // 부분 탐색
            for(int row =0; row< m; row++){
                // 첫번째 세로 줄, 마지막 세로 줄 검색
                int first = 0;
                int last = m-1;
                //cout << storage[col][first] << " : " << target[first] <<endl;
                if(storage[first][row] == target[first]){
                    cout << first << "," << row << endl;
                    storage[first][row] = '*';
                    container_list.push(make_pair(first,row));
                }
               
                if(storage[last][row] == target[first]){
                    cout << last << "," << row << endl;
                    storage[last][row] = '*';
                    container_list.push(make_pair(last,row));
                }
                // else if(storage[first][row] == '*'){
                //     bfs(storage, target, first,row);
                // }
                // else if(storage[last][row] == '*'){
                //     bfs(storage, target, last,row);
                // }
            }
            for(int col =0; col< n; col++){
                // 첫번째 세로 줄, 마지막 세로 줄 검색
                int first = 0;
                int last = n-1;
                //cout << storage[col][first] << " : " << target[first] <<endl;
                if(storage[col][first] == target[first]){
                    cout << col << "," << first << endl;
                    storage[col][first] = '*';
                    container_list.push(make_pair(col,first));
                }
               
                if(storage[col][last] == target[first]){
                   cout << col << "," << last << endl;
                    storage[col][last] = '*';
                    container_list.push(make_pair(col,last)); 
                }
                // else if(storage[col][first] == '*'){
                //     bfs(storage, target,col,first);
                // }
                // else if(storage[col][last] == '*'){
                //     bfs(storage, target,col, last);
                // }
            }
        }
        else {
            // 크레인
            // 완탐
            for(int col =0; col < storage.size(); col++){
                for(int row = 0; row < storage[0].size(); row++){
                    if(storage[col][row] == target[0]){
                        storage[col][row] = '*';
                        container_list.push(make_pair(col,row));
                    }
                    else {
                        continue;
                    }
                }

            }
        }
    }
    for (auto line : storage){
        cout << line << endl;
    }
    answer -= container_list.size();
    return answer;
}
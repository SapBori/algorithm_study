#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;
int arrow_r_left_index = 2;
int arrow_r_right_index = 6;
int arrow_l_left_index = 6;
int arrow_l_right_index = 2;
int direction(int left_i, int right_i, vector<int> left, vector<int> right){
    // 1,2번째만 비교
    // 나머진 -1만 곱함


    // 기어끼리 비교하는데
    // 왼쪽 오른쪽 기어 차 비교 * 타겟 아닌 것에서 같으면 0, 아니면 1
    if(abs(left_i-right_i)%2 == 0){
        
    }
}
void move(int dir, vector<int>& g){
    if (dir == 1){
        int old_next = g[0];
        for(int i=0; i<g.size(); i++){
            int new_index = i+dir;
            if(i == g.size()-1){        
                new_index %= g.size();    
            }
            g[new_index] = old_next;
            old_next = g[new_index+1];
        }
    }
    else if(dir == -1){
        int old_next = g[0];
        for(int i=g.size(); i>0; i--){
            int new_index = i+dir;
            if(i== g.size()){        
                // 8-> 7
                old_next = g[new_index];
                g[new_index] = g[i%g.size()];
                continue;
            }
            else {
                // i -> i-1
                g[new_index] = old_next;
                old_next = g[(new_index-1)%8];
            }
        }
    }
}

int main(){
    int num=0;
    int score_list[4] = {1,2,4,8};
    int gear_num =0;
    int limit = 100;
    vector<vector<int>> gear;
    string g;
    cin >> g;
    vector<vector<pair<int,int>>> move_order;
    move_order = {
                {make_pair(1,2),make_pair(1,3),make_pair(1,4)}, 
                {{2,1},{2,3},{2,4}},
                {{3,4},{3,2},{3,1}},
                {{4,3},{4,2},{4,1}}
            };
    // 12 -> 0번째
    // N -> 0, S -> 1
    for(int i=0; i<4; i++){
        for(int j=0; j<g.size();j++){
            gear[i][j]= g[j];
        }
    }

    cin >> num;
    for(int c=0; c<num; c++){
        int g_index, dir;
        cin >> g_index >> dir;
        // 목표 기어 먼저 순환
        move(dir,gear[g_index-1]);
        for(auto p : move_order[g_index-1]){
            // 주변 기어 순환
            int check_dir = direction(gear[p.first.first], gear[p.first.second]);
            
        }
        // 3-> 4,3 -> 3,2 -> 2,1
        // 4-> 4,3 -> 3,2 -> 2,1
        // 2-> 1,2 -> 2,3 -> 3,4
        // 1-> 1,2 -> 2,3 -> 3,4
    }
    int answer = 0;
    for(int i=0; i<4; i++){
        answer = answer + (gear[i][0]* score_list[i]);
    }
    cout << answer << endl;
    return 0;
}
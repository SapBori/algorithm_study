#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iostream>
using namespace std;
typedef struct{
    int path_index;
    pair<int,int> curr_pos;
    queue<int> land_queue;
    bool arrived;
}Path;
int dir[5][2] = {{0,1},{0,-1},{-1,0},{1,0},{0,0}};
int direction_check(pair<int,int> dest, vector<int> land){
    // y좌표 이동을 먼저 함함
    int r = 0;
    int l = 1;
    int u = 2;
    int d = 3;
    int s = 4;
    int diff_w = land[1]-dest.second;
    int diff_h = land[0]-dest.first;
    if (abs(diff_h)!=0){
        if(diff_h < 0){
            return u;
        }
        else if(diff_h >= 0){
            return d;
        }
    }
    else {
        if(diff_w < 0){
            return l;
        }
        else if(diff_w >= 0){
            return r;
        }
    }
    return s;
}


int check_collision(vector<Path> path_list){
    int cnt =0;
    map<pair<int,int>, int> check;
    for (auto path : path_list){
        // pm.first = path-index
        // pm.second = current_path= position
        if(!path.arrived){
            check[{path.curr_pos}]++;
        }
    }
    for (auto c : check){
        if (c.second >= 2){
            cnt++;
        }
    }
    return cnt;
}

int solution(vector<vector<int>> points, vector<vector<int>> routes) {
    // routes -> dest_point , land_point 구조
    // points -> routes의 포인트의 좌표
    
    // 움직일때는 points를 건드림
    // point의 위치 정보는 Point_map으로 관리
    // p[0] -> y , p[1] -> x
    
    int answer = 0;
    int p_num =0;
    vector<Path> path_list;    // 
    
    for (int i = 0; i < points.size(); i++) {
        points[i][0]--;  // 좌표 보정
        points[i][1]--;
    }
    int path_index=0;
    for(auto r : routes){
        Path p;
        p.path_index = path_index;
        p.arrived = false;
        p.curr_pos = {points[r[0]-1][0],points[r[0]-1][1]};
        queue<int> q;
        for(int i=1; i<r.size(); i++){
            q.push(r[i]-1);
        }
        p.land_queue = q;
        path_list.push_back(p);
        path_index++;
    }

    bool on_flag = false;
    long rp_cnt=0;
    while(!on_flag ){
        rp_cnt++;
        answer +=(int)check_collision(path_list);
        for(int i=0; i<path_index; i++){
            auto& curr_path = path_list[i];
            if (curr_path.land_queue.empty() || curr_path.arrived){
                if(curr_path.arrived){
                    curr_path.arrived=true;
                }
                continue;
            }
            int land_p = curr_path.land_queue.front();
            
            
            // 현재 포인트의 좌표
            // points는 변경 금지
            // pathsmap의 키를 변경예정
            if(curr_path.curr_pos.first == points[land_p][0] && curr_path.curr_pos.second == points[land_p][1])          
            {
                cout << "Path " << i+1 << " is On Position" << endl;
                // 목적지 삭제
                curr_path.land_queue.pop();
                if (curr_path.land_queue.empty()){
                    if(!curr_path.arrived){
                        curr_path.arrived=true;
                    }
                }else {
                    land_p=curr_path.land_queue.front();
                    int arrow = direction_check(curr_path.curr_pos, points[land_p]);
                    cout << "Move Next Land Point" << endl;
                    cout << "Path : " << i+1 << "_arrow " << arrow << endl;
                    curr_path.curr_pos.first = curr_path.curr_pos.first+ dir[arrow][0];
                    curr_path.curr_pos.second = curr_path.curr_pos.second+ dir[arrow][1];
                }
            }
            else {
                int arrow = direction_check(curr_path.curr_pos, points[land_p]);
                cout << "Path : " << i+1 << "_arrow " << arrow << endl;
                curr_path.curr_pos.first = curr_path.curr_pos.first+ dir[arrow][0];
                curr_path.curr_pos.second = curr_path.curr_pos.second+ dir[arrow][1];
            }
        }
        int on_pos=0;
        for (int i=0; i<path_list.size(); i++){
            if(path_list[i].land_queue.empty()){   
                on_pos++;
            }
        }
        cout << "Try : " << rp_cnt << " On Pos : " << on_pos << endl;
        if(on_pos == path_list.size() || rp_cnt == 1000000){
            on_flag = true;
            // cout << rp_cnt << endl;
        }
        
    }
    cout << answer << endl;    
    return answer;

}


int main(){
    // vector<vector<int>> points = {{3, 2}, {6, 4}, {4, 7}, {1, 4}};
    // vector<vector<int>> routes = {{4, 2}, {1, 3}, {2, 4}};
    // vector<vector<int>> points=  {{3, 2}, {6, 4}, {4, 7}, {1, 4}};
    // vector<vector<int>> routes = {{4, 2}, {1, 3}, {4, 2}, {4, 3}};
    vector<vector<int>> points={{2, 2}, {2, 3}, {2, 7}, {6, 6}, {5, 2}};
    vector<vector<int>> routes={{2, 3, 4, 5}, {1, 3, 4, 5}};
    solution(points,routes);
};




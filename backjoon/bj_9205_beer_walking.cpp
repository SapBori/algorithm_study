#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main(){
    int test_case = 0;
    cin >> test_case ;
    vector<string> result;
    for(int c = 0; c < test_case; c++){
        int store = 0;
        int beer_cnt = 20;
        pair<int,int> home;
        queue<pair<pair<int,int>,int>> map_queue;
        
        vector<pair<int,int>> store_cnt;
        pair<int,int> site;
        
        cin >> store;
        cin >> home.first >> home.second;
        for (int i=0; i<store; i++){
            pair<int,int> temp;
            cin >> temp.first >> temp.second;
            store_cnt.push_back(temp);
        }
        cin >> site.first >> site.second;
    
        vector<pair<int,int>> dir = {{50,0}, {0,50}};
        pair<pair<int,int>,int> start = {home,beer_cnt};
        map_queue.push(start);
        while(!map_queue.empty()){
            auto [pos, beer] = map_queue.front();
            map_queue.pop();
            
            if (pos.first == site.first && pos.second==site.second && beer >= 0){
                result.push_back("happy");
                break;
            }
            else {
                if (beer <=0){
                    // 움직여야 하는데 맥주가 없음    
                    result.push_back("sad");
                    break;
                }
                // 맥주가 남아 움직일 수 있음
                for(auto st : store_cnt){
                    if((st.first - pos.first) < (st.second-pos.second)){
                        int new_x = pos.first + 50;
                        int new_y = pos.second;
                        if(new_x > st.first || new_y > st.second){
                            // 편의점 지나침
                            continue;
                        }
                        if (new_x == st.first && new_y == st.second){
                            // 우연히 편의점을 들림
                            beer = 20;
                        }
                        map_queue.push({{new_x,new_y},beer-1});
                        continue;
                    }
                    else if ((st.first - pos.first) > (st.second-pos.second)){
                        int new_x = pos.first ;
                        int new_y = pos.second + 50;
                        if(new_x > st.first || new_y > st.second){
                            // 편의점 지나침
                            continue;
                        }
                        if (new_x == st.first && new_y == st.second){
                            // 우연히 편의점을 들림
                            beer = 20;
                        }
                        map_queue.push({{new_x,new_y},beer-1});
                        continue;
                    }
                }
            }
        }
    }
    for (auto st : result){
        cout << st << endl;
    }
}
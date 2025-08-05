#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    // 완탐 
    // 해시
    vector<pair<string, int>> buy_list;
    for (int it = 0; it<want.size(); it++){
        pair<string, int> buy;
        buy.first= want[it];
        buy.second = number[it];
        buy_list.push_back(buy);
    }
    for(int discount_index=0; discount_index< discount.size(); discount_index++){
        vector<pair<string, int>> copy_buy_list = buy_list;
        bool check_next = false;
        // 현재 discount에서 10개를 먼저 봄 근데 사이즈 넘어서 보면 그건 케이스가 없는것
        if (discount_index + 10 > discount.size()){
            break;
        }
        for(int thing = discount_index; thing < discount_index+10; thing++){
            // 그자리에서 10가지를 봄
            // cout << discount[thing] << endl;
            for (auto t = copy_buy_list.begin(); t != copy_buy_list.end(); t++){
                // 할인 항목에 맞는 것 확인
                if(t->first == discount[thing]){
                    t->second -=1;
                    break;
                }
            }
        }
        for(const auto& [name, number] : copy_buy_list){
            if(number != 0){
                check_next=true;
                break;
            }
        }
        if (check_next){
            // 한 항목이라도 못사면 다음날로 넘어감
            continue;
        }
        else {
            // 케이스 조건 날짜 확인
            answer+=1;
        }
        
    }
    return answer;
}
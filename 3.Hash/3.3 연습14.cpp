#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;
using uint = unsigned int;

class hash_map{
  std::vector<std::list<int>> data;
  
public:
  hash_map(size_t n){
    data.resize(n);
  }
  void insert(uint value){
    int n = data.size();
    data[value % n].push_back(value);
    cout << value << "를 저장하였습니다. " << endl;
  }
  bool find(uint value){
    int n = data.size();
    auto& entries = data[value % n];
    return std::find(entries.begin(), entries.end(), value) != entries.end();
  }
  void erase(uint value){
    int n = data.size();
    auto& entries = data[value % n];
    auto iter = std::find(entries.begin(), entries.end(), value);
    
    if(iter != entries.end()){
      // entries의 끝값과 일치 하지 않다 == 데이터가 존재
      entries.erase(iter);
      cout << value << "를 삭제하였습니다. " << endl;
    }
  }
};

int main() 
{
  hash_map map(7);
  
  auto print = [&](int value){
    if(map.find(value)){
      cout <<"해시 맵에서 " << value << "를 찾았습니다. " << endl;
    }
    else {
      cout <<"해시 맵에서 " << value << "를 못 찾았습니다. " << endl;
    }
  };
  
  map.insert(2);
  map.insert(25);
  map.insert(10);
  map.insert(100);
  map.insert(55);
  
  print(100);
  print(2);
  
  map.erase(2);
}
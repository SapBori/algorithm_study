#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;

class hash_map{
  vector<int> data;
public:
  hash_map(size_t n){
    data = vector<int>(n, -1);
  }
  void insert(uint value){
    int n = data.size();
    data[value% n] = value;
    cout << value << "를 삽입했습니다." << endl;
  }
  bool find(uint value){
    int n = data.size();
    return (data[value % n] == value);
  }
  void erase(uint value){
    int n = data.size();
    
    if (data[value % n ]== value){
      data[value % n ] = -1;
      cout << value << "를 삭제 했습니다." << endl;
    }
  }
};

int main() 
{
  hash_map map(7);
  auto print = [&](int value){
    if (map.find(value)){
      cout << "해시 맵에서 " << value << "를 찾았습니다." << endl;
    }
    else{
      cout << "해시 맵에서 " << value << "를 못 찾았습니다." << endl;
      cout << endl;
    }
  };
  
  map.insert(2);
  map.insert(25);
  map.insert(10);
  print(25);
  cout << endl;
  
  map.insert(100);      // 2 % 7 = 2이고, 100 % 7 = 2이기에 나중에 들어온 데이터 100이 2의 자리를 바꿔치기 함(충돌방지)
  print(100);
  print(2);
  
  map.erase(25);
  
}
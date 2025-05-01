#include <iostream>
#include <vector>
using namespace std;


class bloom_filter{
  vector<bool> data;
  int nBits;
  
  int hash(int num, int key){
    switch(num){
      case 0: return key% nBits;
      case 1: return (key/7)% nBits;
      case 2: return (key/11)% nBits;
    }
    return 0;
  }
public:
  bloom_filter(int n) : nBits(n){
    data = vector<bool>(nBits, false);
  }
  void lookup(int key){
    bool result = data[hash(0,key)] & data[hash(1,key)] & data[hash(2,key)];
    // 3가지 해시 함수에서 모두 긍정이 나와야 값이 있을 수 있다고 판단
    
    if(result){
      cout << key << " may be in Container" << endl;
    }
    else {
      cout << key << " is Not in Container" << endl;
    }
  }
  void insert(int key){
    data[hash(0,key)] = true;
    data[hash(1,key)] = true;
    data[hash(2,key)] = true;
    cout << key << " is Inserted in Container" << endl;
    
    for (auto a : data){
      cout << a << " ";
    }
    cout << endl;
  }
};
int main() 
{
  bloom_filter bf(7);
  bf.insert(100);
  bf.insert(54);
  bf.insert(82);
  
  bf.lookup(5);  // 거짓-긍정이 발생
  bf.lookup(50);
  bf.lookup(20);
  bf.lookup(54);
  return 0;
}
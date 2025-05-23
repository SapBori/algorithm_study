#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>


// 표즌 라이브러리를 이용해서 맵 리듀스 구현
using namespace std;
void transform_test(std::vector<int> S){
  vector<int> Tr;
  cout << "[Map Test] " << endl;
  cout << "Input Array, S :";
  for (auto i : S){
    cout << i << " ";
  }
  cout << endl;
  
  transform(S.begin(), S.end(), back_inserter(Tr),
  [](int x) {return pow(x,2.0); });
  
  cout << "transform(), Tr: ";
  for (auto i : Tr){
    cout << i << " ";
  }
  cout << endl;
  
  for_each(S.begin(), S.end(), [](int& x){ x = pow(x,2.0); } );
  
  cout << "for_each (), S: ";
  for (auto i : S){
    cout << i << " ";
  }
  cout << endl;
   
}

void reduce_test(std::vector<int> S){
  cout << endl << "[Reduce Test] " << endl;
  cout << "Input Array, S :";
  for (auto i : S){
    cout << i << " ";
  }
  cout << endl;
  
  auto ans = accumulate(S.begin(), S.end(),0,[](int acc, int x){return acc + x ;});
  cout << "Accumulate Result : " << ans << endl;
}

int main(){
  vector<int> S {1, 10, 4, 7, 3, 5, 6, 8,9,2};
  
  transform_test(S);
  
  reduce_test(S);
}
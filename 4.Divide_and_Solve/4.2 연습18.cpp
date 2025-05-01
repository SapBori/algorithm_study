#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
using namespace std;

bool linear_search(int N, std::vector<int>& S){
  for (auto i : S){
    if (i == N){
      return true;
    }
  }
  return false;
}
bool binary_search(int N, std::vector<int>& S){
  auto first= S.begin();
  auto last = S.end();
  while(true){
    auto range_length = std::distance(first,last); // 범위 길이 찾기 // std::distance는 암의 접근 생성자
    auto mid_element_index = static_cast<int>(std::floor(range_length / 2)); // 범위에서의 중간 인덱스값 찾기 // std::floor는 반올림 함수
    auto mid_element = *(first + mid_element_index);            // 중간인덱스의 원소값 지정
    
    if(mid_element == N){
      
      return true;
    }
    else if(mid_element > N){
      // 중간 인덱스의 원소가 N의 오른쪽에 있다
      advance(last, -mid_element_index);    // advance()함수​ iterator를 원하는 위치로 옮길 수 있는 함수
    }
    else {
      advance(first,mid_element_index);
    }
    if(range_length==1){
      // 최종적으로 찾을 수 있는 범위가 1개이고, 이 원소가 N과 다르다면 N은 범위에 없는 것임
      return false;
    }
    
  }
}
void run_small_search_test(){
  auto N = 2;
  vector<int> S = {1,3,5,7,4,2,9,8,6};
  sort(S.begin(),S.end());
  
  if(linear_search(N,S)){
    cout << "선형 검색으로 원소를 찾음" << endl;
  }
  else {
    cout << "선형 검색으로 원소를 찾지 못함 " << endl;
  }
  
  if(binary_search(N,S)){
    cout << "이진 검색으로 원소를 찾음 " << endl;
  }
  else {
    cout << "이진 검색으로 원소를 찾지 못함 " << endl;
  }
}
void run_large_search_test(int size, int N){
  vector<int> S;
  random_device rd;
  std:mt19937 rand(rd());
  
  //[1,size] 범위에서 정수 난수 발생
  std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1,size);
  
  for (auto i=0; i< size; i ++){
    // 난수 추가
    S.push_back(uniform_dist(rand));
  }
  sort(S.begin(),S.end());
  
  // 검색 시작 시간 저장
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  
  bool serach_result = binary_search(N,S);
  
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  
  auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
  cout << "정수 난수 이진 검색 수행시간 : " << diff.count() << endl;
  
   if(serach_result){
    cout << "이진 검색으로 원소를 찾음 " << endl;
  }
  else {
    cout << "이진 검색으로 원소를 찾지 못함 " << endl;
  }
}
int main() 
{
    run_small_search_test();
    run_large_search_test(10000,35645);
    run_large_search_test(100000,35645);
    run_large_search_test(100000,35645);
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
auto partition(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end){
  // 세개의 반복자 생성
  // 1. 피벗, 2. 벡터의 시작, 3. 백터의 끝
  
  auto pivot_val = *begin;
  auto left_iter = begin+1;
  auto right_iter = end;
  
  while(true){
    while(*left_iter <= pivot_val && std::distance(left_iter,right_iter) > 0)
      left_iter++;
    // 벡터의 마지막 원소부터 시작해서 역순으로 피벗보다 적은 원소를 찾음
    while(*right_iter > pivot_val && std::distance(left_iter,right_iter) > 0)
      right_iter--;
    
    // left_iter == right_iter --> 교환할 원소가 없음
    // 그렇지 않으면 left_iter와 right_iter를 서로 교환
    if(left_iter == right_iter){
      break;
    }
    else std::iter_swap(left_iter,right_iter);
  }
  
  if(pivot_val > *right_iter){
    std::iter_swap(begin,right_iter);
  }
  return right_iter;
}
template <typename T>
void quick_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator last){
  // 벡터에 1개 이상의 원소가 있다면
  if(std::distance(begin ,last) >= 1){
    // 분할 작업 실행
    auto partition_iter = partition<T>(begin, last);
    
    // 분할 작업에 의해 생성된 벡터를 재귀적으로 정렬
    quick_sort<T>(begin, partition_iter-1);
    quick_sort<T>(partition_iter,last);
  }  
}
template <typename T>
void print_vector(std::vector<T> arr){
  for (auto i : arr){
    cout << i << " ";
  }
  cout << endl;
}
void run_quick_sort_test(){
  std::vector<int> S1 {45,1,3,1,2,3,45,5,1,2,44,5,7};
  std::vector<float> S2 {45.6f,1.0f,3.2f,1.5f,2.1f,3.5f,45.1f,5.4f,1.8f,2.6f,44.0f,5,7.5f};
  std::vector<double> S3 {45.2,1.1,3.4,1.6,2.1,3.4,45.4,5.7,1.0,2.5,44.8,5.1,7.5};
  std::vector<char> C {'b','z','a','r','t','p','y'};
  
  cout << " 정렬되지 않는 벡터들 " << endl;
  print_vector<int> (S1);
  print_vector<float> (S2);
  print_vector<double> (S3);
  print_vector<char> (C);
  
  quick_sort<int> (S1.begin(), S1.end()-1);
  quick_sort<float> (S2.begin(), S2.end()-1);
  quick_sort<double> (S3.begin(), S3.end()-1);
  quick_sort<char> (C.begin(), C.end()-1);
  
  cout << " 병합정렬된 벡터들 " << endl;
  print_vector<int> (S1);
  print_vector<float> (S2);
  print_vector<double> (S3);
  print_vector<char> (C);
}
int main() 
{
  run_quick_sort_test();
}
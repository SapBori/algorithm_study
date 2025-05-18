#include <iostream>
#include <vector>
using namespace std;


template <typename T>
std::vector<T> merge(std::vector<T>& arr1,std::vector<T>& arr2) {
  std::vector<T> merged;
  
  auto iter1 = arr1.begin();
  auto iter2 = arr2.begin();
  
  while(iter1 != arr1.end() && iter2 != arr2.end()){
    if(*iter1 < *iter2){
      // 부분 집합 원소중에서 arr1이 arr2 보다 작으면
      // arr1을 먼저 병합할 부분집합에 추가
      merged.emplace_back(*iter1);
      iter1++; // arr1의 다음원소를 가리킴
    }
    else {
      merged.emplace_back(*iter2);
      iter2++;
    }
  }
  if(iter1 != arr1.end()){
    for(; iter1!=arr1.end(); iter1++){
      merged.emplace_back(*iter1);
    }
  }
  else {
    for(; iter2!=arr2.end(); iter2++){
      merged.emplace_back(*iter2);
    }
  }
  return merged;
}
template <typename T>
std::vector<T> merge_sort(std::vector<T> arr){
  if(arr.size()>1){
    auto mid =size_t(arr.size()/2);
    auto left_half = merge_sort<T>(std::vector<T>(arr.begin(), arr.begin()+mid) );
    auto right_half = merge_sort<T>(std::vector<T>(arr.begin()+mid, arr.end()) );
    return merge<T>(left_half, right_half);
  }
  return arr;
}
template <typename T>
void print_vector(std::vector<T> arr){
  for (auto i : arr){
    cout << i << " ";
  }
  cout << endl;
}

void run_merge_sort_test(){
  std::vector<int> S1 {45,1,3,1,2,3,45,5,1,2,44,5,7};
  std::vector<float> S2 {45.6f,1.0f,3.2f,1.5f,2.1f,3.5f,45.1f,5.4f,1.8f,2.6f,44.0f,5,7.5f};
  std::vector<double> S3 {45.2,1.1,3.4,1.6,2.1,3.4,45.4,5.7,1.0,2.5,44.8,5.1,7.5};
  std::vector<char> C {'b','z','a','r','t','p','y'};
  
  cout << " 정렬되지 않는 벡터들 " << endl;
  print_vector<int> (S1);
  print_vector<float> (S2);
  print_vector<double> (S3);
  print_vector<char> (C);
  
  auto sorted_S1 = merge_sort<int>(S1);
  auto sorted_S2 = merge_sort<float>(S2);
  auto sorted_S3 = merge_sort<double>(S3);
  auto sorted_C = merge_sort<char>(C);
  
  cout << " 병합정렬된 벡터들 " << endl;
  print_vector<int> (sorted_S1);
  print_vector<float> (sorted_S2);
  print_vector<double> (sorted_S3);
  print_vector<char> (sorted_C);
  
}
int main() 
{
    run_merge_sort_test();
    return 0;
}
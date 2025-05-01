#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct median{
  // 중앙값(데이터 상의 가운데 값) 을 기준으로 
  // 크면 최대 힙에 저장
  // 작으면 최소 힙에 저장
  std::priority_queue<int> maxHeap;
  std::priority_queue<int, std::vector<int>, std::greater<int> > minHeap;
  
  void insert(int data){
    if (maxHeap.size() == 0){
      // 최대 힙의 원소가 없는 경우
      maxHeap.push(data);
      return;
    }
    if (maxHeap.size() == minHeap.size()){
      // 데이터의 개수가 짝수라면 중앙값 == 힙의 최대/최소값의 산술평균
      if (data <=get())
        maxHeap.push(data);
      else 
        minHeap.push(data);
     return;
    }
    if (maxHeap.size() < minHeap.size()){
      // 최소 힙의 개수가 적은 경우 >> 최소 힙에 원소 추가
      if (data > get()){
        // 데이터가 중앙값 보다 큰 경우 >> 최대 힙에 원소 추가
        maxHeap.push(minHeap.top());
        minHeap.pop();
        minHeap.push(data);
      }
      else 
        maxHeap.push(data);
      return;
    }
    
    // 최대 힙의 개수가 적은 경우 >> 최대 힙에 원소 추가
    if (data < get()){
      // 데이터가 중앙값 보다 작은경우 >> 최소 힙에 원소 추가
      minHeap.push(maxHeap.top());
      maxHeap.pop();
      maxHeap.push(data);
    }
    else 
      minHeap.push(data);
  }
  double get(){
    if(maxHeap.size() == minHeap.size()){
      return (maxHeap.top() + minHeap.top()) /2.0;
    }
    if (maxHeap.size() < minHeap.size()){
      return minHeap.top();
    }
    return maxHeap.top();
  }
};
int main() 
{
  median med;
  int insert_value = 1;
  med.insert(insert_value);
  std::cout << insert_value << " 삽입 후 중앙값: " << med.get() << std::endl;
  
  insert_value = 5;
  med.insert(insert_value);
  std::cout << insert_value << " 삽입 후 중앙값: " << med.get() << std::endl;
  
  insert_value = 2;
  med.insert(insert_value);
  std::cout << insert_value << " 삽입 후 중앙값: " << med.get() << std::endl;
  
  insert_value = 10;
  med.insert(insert_value);
  std::cout << insert_value << " 삽입 후 중앙값: " << med.get() << std::endl;
 
  insert_value = 40;
  med.insert(insert_value);
  std::cout << insert_value << " 삽입 후 중앙값: " << med.get() << std::endl;
}
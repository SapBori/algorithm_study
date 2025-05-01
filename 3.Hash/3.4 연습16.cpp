#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void print(const std::unordered_set<int>& container){
  for(const auto& element : container){
    cout << element << " ";
  }
  cout << endl;
}
void find(const std::unordered_set<int>& container, const int element){
  if (container.find(element) == container.end()){
    cout << element << " is Not Found Container " << endl;
  }
  else {
    cout << element << " is In Container " << endl;
  }
}
void print(const std::unordered_map<int, int> container){
  for(const auto& element : container){
    cout << element.first << " -> " << element.second << ", ";
  }
  cout << endl;
}
void find(const std::unordered_map<int, int>& container, const int element){
  auto it = container.find(element);
  if (it == container.end()){
    cout << element << " is Not Found Container " << endl;
  }
  else {
    cout << element<< " is In Container, Value : " << it->second << endl;
  }
}

int main() 
{
    cout << "unordered_set 예제" << endl;
    unordered_set<int> set1 = {1,2,3,4,5};
    cout << "set1 초기값 : "; print(set1);
    
    set1.insert(2);
    cout << "2 삽입 " << endl;
    
    set1.insert(10);
    set1.insert(300);
    cout << "10, 300 삽입" << endl;
    
    find(set1, 4);
    find(set1, 100);
    
    set1.erase(2);
    cout << "2 삭제"; print(set1);
    find(set1, 2);
    
    cout << "\n---------------------------------------\n" << endl;
    cout << "unordered_map 예제 " << endl;
    
    unordered_map<int, int> squareMap;
    squareMap.insert({2,4});
    squareMap[3] = 9;
    squareMap[20] = 400;
    squareMap[30] = 900;
    
    cout << "현재 설정된 Map: " ; print(squareMap);
    
    find(squareMap, 20);
    find(squareMap, 10);
    cout << "squareMap[3] = " << squareMap[3] << endl; 
    cout << "squareMap[30] = " << squareMap[30] << endl;
    
}
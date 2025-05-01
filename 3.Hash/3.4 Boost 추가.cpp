#include <iostream>
#include <unordered_map>
#include <unordered_set>
// #include <boost/functional/hash.hpp>
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
// struct Car{
//   string model;
//   string brand;
//   int buildYear;
// };
// struct CarHasher{
//   size_t operator()(const Car& car) const{
//     size_t seed = 0;
//     boost::hash_combine(seed,car.model);
//     boost::hash_combine(seed,car.brand);
//     return seed;
//   }
// };
// struct CarComparator{
//   bool operator()(const Car& car1, const Car& car2) const{
//     return (car1.model == car2.model) && (car1.brand == car2.brand);
//   }
// };
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
    cout << "squareMap[10] = " << squareMap[10] << endl;  // unordered_map에서는 저장되지 않았던 Key의 초기 Value는 0이다
    //
    // unordered_map,unordered_set에서는 중복 값을 허용하지 않음
    // 중복된 Key에 값을 저장하고 싶다면, unordered_multiset, unordered_multimap 을 이용해야 함
    //
    
    cout << "\n--------------------------------\n" << endl;
    // unordered_set<Car, CarHasher, CarComparator> carSet;
    // unordered_map<Car, string, CarHasher, CarComparator> carDescriptionMap;
    
}
#include <iostream>
#include <queue>
using namespace std;

// 한 직원은 최대 2명의 부하 직원에게 오더가 가능 >>> 하위 노드는 최대 2개
struct node{
  std::string position;
  node* first; // 부하 1
  node* second; // 부하 2
};

struct org_tree {
  node* root;

  static org_tree create_org_structure(const std::string& pos){
    org_tree tree;
    tree.root = new node {pos, NULL,NULL};  // 최상단 노드 생성
    return tree;
  }

  static node* find(node* root, const std::string& value){
    if(root == NULL){
      // 해당 노드가 없다면 종속되지 않았거나 생성되지 않았음 -> NULL
      return NULL;
    }
    if(root->position == value){
      // 해당 노드가 자신의 노드라면
      return root;
    }
    
    auto firstFound = org_tree::find(root->first, value);
    
    if(firstFound != NULL){
      // 하위 노드에서 첫번째 노드가 있는경우
      return firstFound;
    }
    // 아니면 두번쩨 노드 리턴
    return org_tree::find(root->second, value);
  }
  bool addSubordinate(const std::string& manager, const std::string& subordinate){
    auto managerNode = org_tree::find(root, manager);
    
    if(!managerNode){
      std::cout << manager << "을 찾을 수 없습니다. " << std::endl;
      return false;
    }
    
    if(managerNode->first && managerNode->second){
      // 매니저의 하위 부하들이 모두 있는 경우
      std::cout << manager << " 아래에 " << subordinate << "을 추가할 수 없습니다." << std::endl;
      return false;
    }
    if(!managerNode->first){
      // 첫번째 부하가 없다면 그곳에 추가
      managerNode->first = new node {subordinate, NULL, NULL};
    }
    else{
      managerNode->second = new node {subordinate, NULL, NULL};
    }
    std::cout << manager << " 아래에 " << subordinate << " 을 추가했습니다. " << std::endl;
    return true;
  }
};
int main() 
{
  auto tree = org_tree::create_org_structure("CEO");  
  
  tree.addSubordinate("CEO", "부사장");           // CEO 아래에  부사장 추가
  
  tree.addSubordinate("부사장", "IT부장");          // 부사장 아래에  IT부장 추가
  tree.addSubordinate("부사장", "마케팅부장");     // 부사장 아래에  마케팅부장 추가
  
  tree.addSubordinate("IT부장", "보안팀장");      // IT부장 아래에  보안팀장 추가
  tree.addSubordinate("IT부장", "앱개발팀장");    // IT부장 아래에  앱개발팀장 추가
  
  tree.addSubordinate("마케팅부장", "물류팀장");  // 마케팅부장 아래에  물류팀장 추가
  tree.addSubordinate("마케팅부장", "홍보팀장");  // 마케팅부장 아래에  홍보팀장 추가
  
  tree.addSubordinate("부사장", "재무부장");      // 부사장 아래에는 2명 부하 존재 >> 추가 실패패
  
}
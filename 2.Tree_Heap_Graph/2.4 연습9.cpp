#include <iostream>
struct node{
    int data;
    node* left;
    node* right;
};

struct bst{
    node* root = nullptr;
    node* find(int value){
        return find_imlp(root, value);
    }
private:
    node* find_imlp(node* current, int value){
        // 원소 검색은 재귀적으로 동작함
        // 따로 검색 함수를 만들어야 함
        if(!current){
            std::cout << std::endl;
            return NULL;
        }
        if(current->data == value){
            std::cout << value << "을 찾았습니다. " << std::endl;
            return current;
        }
        if(value < current->data){
            std::cout << value << "보다 작음 왼쪽으로 이동. " << std::endl;
            return find_imlp(current->left,value);
        }
        
        std::cout << value << "보다 큼 오른쪽으로 이동. " << std::endl;
        return find_imlp(current->right ,value);
        
    }
    void insert_node(node* current, int value){
        if(value < current->data){
            if (!current->left){
                 //왼쪽에 자식노드가 없으면 자식 노드 생성
                current->left = new node{value, NULL, NULL};
            }
            else {
                insert_node(current->left, value);
            }
        }
        else {
            if (!current->right){
                 //오른쪽에 자식노드가 없으면 자식 노드 생성
                current->right = new node{value, NULL, NULL};
            }
            else {
                insert_node(current->right, value);
            }
        }
    }
    node* delete_impl(node* start, int value){
        if(!start){
            return NULL;
        }
        if(value < start->data){
            // 현재 노드 값이 지우려는 값보다 작은 경우 왼쪽자식으로 이동
            start->left = delete_impl(start->left, value);
        }
        else if(value > start->data){
            // 현재 노드 값이 지우려는 값보다 큰 경우 오른쪽자식으로 이동
            start->right= delete_impl(start->right, value);
        }
        else {
            if(!start->left){
                // 왼쪽 자식 노드만 없는 경우
                auto tmp = start->right;
                delete start;
                return tmp;
            }
            if(!start->right){
                // 오른쪽 자식노드만 없는 경우
                auto tmp = start->left;
                delete start;
                return tmp;
            }
            auto succNode = successor(start);
            start->data = succNode->data;

            start->right = delete_impl(start->right, succNode->data);
        }
        return start;
    }
    void inorder_impl(node* start){
        // 중위 순회 함수
        if(!start){
            return;
        }
        inorder_impl(start->left);
        std::cout << start->data << " ";
        inorder_impl(start->right);
    }
public:
    void insert(int value){
        if(!root){
            root = new node{value, NULL,NULL};
        }
        else {
            insert_node(root, value);
        }   
    }
    void inorder(){
        inorder_impl(root);
    }
    node* successor(node* start){
        auto current = start->right;
        while (current && current->left){
            current = current->left;
        }
        return current;
    }
    void deleteValue(int value){
        root = delete_impl(root,value);
    }
};
int main() {
    bst tree;
    tree.insert(12);
    tree.insert(20);
    tree.insert(10);
    tree.insert(8);
    tree.insert(15);
    tree.insert(11);
    tree.insert(28);
    tree.insert(4);
    tree.insert(2);

    std::cout << "중위 순회 : ";
    tree.inorder();  // 모든 원소를 오름차순으로 정렬출력
    std::cout << std::endl;

    tree.deleteValue(12);
    std::cout << "중위 순회 : ";
    tree.inorder();  // 12삭제 후 모든 원소를 오름차순으로 정렬출력
    std::cout << std::endl;

    if (tree.find(12)){
        std::cout << "원소 12는 트리에 있습니다." << std::endl;
    }
    else{
        std::cout << "원소 12는 트리에 없습니다." << std::endl;
    }
}
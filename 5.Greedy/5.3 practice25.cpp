#include <iostream>
#include <vector>
#include <algorithm>

struct Object
{
    int id;
    int weight;
    double value;
    double value_per_unit_weight;

    Object(int i, int w, double v): id(i), weight(w), value(v), value_per_unit_weight(v/w){}

    inline bool operator< (const Object& obj) const{
        return this->value_per_unit_weight < obj.value_per_unit_weight;
    }

    // 콘솔 출력 지원 std::cout << obj << std::endl 사용 가능
    friend std::ostream& operator<<(std::ostream& os, const Object& obj);
};

std::ostream& operator<<(std::ostream& os, const Object& obj){
    os << "[" << obj.id << "] 가격: " << obj.value 
    << "\t 무게" << obj.weight
    << "kg\t 단위 무게 당 가격: " << obj.value_per_unit_weight;
    return os;
}

auto fill_knapsack(std::vector<Object>& objects, int knapsack_capacity){
    std::vector<Object> knapsack_contents;
    knapsack_contents.reserve(objects.size());

    std::sort(objects.begin(), objects.end());
    std::reverse(objects.begin(), objects.end());

    auto current_object = objects.begin();
    int current_total_weight = 0;
    while (current_total_weight <knapsack_capacity && current_object!= objects.end())
    {
        knapsack_contents.push_back(*current_object);
        current_total_weight +=current_object->weight;
        current_object++;
        /* code */
    }
    
    int weight_of_last_obj_to_remove = current_total_weight- knapsack_capacity;
    Object& last_object = knapsack_contents.back();
    if(weight_of_last_obj_to_remove >0){
        last_object.weight -= weight_of_last_obj_to_remove;
        last_object.value  -= last_object.value_per_unit_weight * weight_of_last_obj_to_remove;
    }

    return knapsack_contents;
}

int main(int argc, char* argv){
    std::vector<Object> objects;

    objects.reserve(7);

    std::vector<int> weights {1,2,5,9,2,3,4};
    std::vector<double> values {10,7,15 ,10,12,11,5};

    for(auto i =0; i<7 ; i++){
        objects.push_back(Object(i+1, weights[i],values[i]));
    }
    std::cout << "[사용 할 수 있는 물건 정보]" << std::endl;
    for(auto& o: objects){
        std::cout << o << std::endl;
    }
    std::cout << std::endl;

    int knapsack_capcity = 7;
    auto solution = fill_knapsack(objects, knapsack_capcity);

    std::cout << "[배낭에 넣을 물건들 (최대 용량 = " << knapsack_capcity << ")]" << std::endl;
    for (auto& o : solution){
        std::cout << o << std::endl;
    }
    std::cout << std::endl; 
}
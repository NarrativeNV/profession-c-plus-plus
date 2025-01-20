#include <iostream>
#include <vector>

int main(){
    int vec_capacity = 0;
    while (vec_capacity <= 0){
        std::cout << "Input vector size: ";
        std::cin >> vec_capacity;
    }

    std::vector<int> vec(vec_capacity);
    std::cout << "Input numbers: ";
    for (int i = 0; i < vec_capacity; i++){
        int vec_numbers = 0;
        std::cin >> vec_numbers;
        vec[i] = vec_numbers;
    }

    int number_to_delete = 0;
    std::cin.sync();
    std::cout << "Input number to delete: ";
    std::cin >> number_to_delete;

    for (int i = 0; i < vec.size(); i++){
        if (vec[i] == number_to_delete) {
            for (int j = 0; j < vec.size() - i - 1; j++){
                std::swap(vec[j + i], vec[j + i + 1]);
            }
            vec.pop_back();
            i--;
        }
    }

    std::cout << "Result: ";
    for (int i = 0; i < vec.size(); i++){
        std::cout << vec[i] << " ";
    }
}
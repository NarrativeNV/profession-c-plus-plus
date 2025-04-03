#include <iostream>

int main(){
    float numbers[15];
    std::cout << "Array: ";
    std::cin >> numbers[0] >> numbers[1] >> numbers[2] >> numbers[3] >> numbers[4]
            >> numbers[5] >> numbers[6] >> numbers[7] >> numbers[8] >> numbers[9]
            >> numbers[10] >> numbers[11] >> numbers[12] >> numbers [13] >> numbers[14];

    for (int i = 0; i < 15; i++){
        bool swaped = false;
        for (int j = 0; j < 15 - 1 - i; j++){
            if (numbers[j] < numbers[j + 1]){
                std::swap(numbers[j], numbers[j+1]);
                swaped = true;
            }
        }
        if (!swaped) break;
    }

    std::cout << "Sorted array: ";
    for (int i = 0; i < 15; i++){
        std::cout << numbers[i] << " ";
    }
}
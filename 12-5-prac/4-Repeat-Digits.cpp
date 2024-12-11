#include <iostream>

int main(){
    int numbers[15] = {114, 111, 106, 107, 108, 105, 115, 108, 110, 109, 112, 113, 116, 117, 118};

    int minValue = numbers[0];

    for(int i = 0; i < 14; i++){
        if (numbers[i] < minValue) minValue = numbers[i];
    }

    int expectedSum = (minValue * 14) + (91);
    int actualSum = 0;

    for (int i = 0; i < 15; ++i) {
        actualSum += numbers[i];
    }

    int duplicate = actualSum - expectedSum;

    std::cout << "Повторяющееся число: " << duplicate << std::endl;
}
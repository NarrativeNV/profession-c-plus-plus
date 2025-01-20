#include <iostream>
#include <vector>

int main(){
    std::vector<float> prices {2.5, 4.25, 3.0, 10.0};
    std::vector<int> items {1, 1, 0, 3, 4, 5, 6, 7};
    std::vector<int> misses;
    float result = 0;
    int error_items = 0;
    for (int i = 0; i < items.size(); i++){
        if (items[i] > prices.size() - 1) {
            error_items++;
            misses.push_back(items[i]);
        }
        else result += prices[items[i]];
    }

    if (error_items > 0){
        std::cout << "Misses: ";
        std::cout << error_items << " {";
        for (int i = 0; i < misses.size() - 1; i++){
            std::cout << misses[i] << ", ";
        }
        std::cout << misses[misses.size() - 1] << "}. There are no products with this index.\n"; 
    }
    std::cout << "Result: " << result;
}
#include <iostream>
#include <vector>

int main() {
    std::vector<int> db(20);
    int number = 0;
    
    for (int i = 0;; i++){
        std::cout << "Input number: ";
        std::cin.sync();
        std::cin >> number;
        if (number == -1){
            std::cout << "output: ";
            for(int j = 0; j < db.size(); j++){
                std::cout << db[j] << " ";
            }
            i--;
            std::cout <<"\n";
        }
        else {
            if (i < db.capacity()) db[i] = number;
            else {
                for (int k = 0; k < db.size(); k++){
                    std::swap(db[k], db[k + 1]);
                }
                db[db.size() - 1] = number;
            }
        }
    }
}
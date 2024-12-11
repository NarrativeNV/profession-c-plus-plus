#include <iostream>
#include <string>

int main(){
    std::string surname[10];

    //ARRAY FILL
    for (int i = 0; i < 10; i++){
        std::cout << "Input surname <- ";
        std::cin >> surname[i];
    }

    //SELECT FLOOR
    int floor;
    std::cout << "\n";
    for (int i = 0; i < 3; i++){
        std::cout << "Input floor <- ";
        std::cin >> floor;
        if (floor > 10 || floor < 1){
            std::cout << "Incorrect floor\n\n";
            i -= 1;
        } 
        else{
            std::cout << "Tenant -> " << surname[floor-1] << std::endl; 
        }
    }
}
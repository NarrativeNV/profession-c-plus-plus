#include <iostream>
#include <string>

int main() {
  while(true){
    std::string integer;
    std::string real;

    std::cout << "Input integer part: ";
    std::cin >> integer;

    std::cout << "Input real part: ";
    std::cin >> real;

    std::string new_num_str = integer + "." + real;

    double new_number = stod(new_num_str);
    printf("Your number %f\n\n", new_number);
  }
}
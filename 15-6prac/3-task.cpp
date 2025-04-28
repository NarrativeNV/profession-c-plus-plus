#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int string_parser (std::string number, int count) {
  int digit = 0;
  if (number[0] == '-'){
    --count;
    for (int i = 1; i < number.length(); i++){\
      digit += (number[i] - '0') * pow(10, count-1);
      --count;
    }
    digit *= -1;
  }
  else {
    for (int i = 0; i < number.length(); i++){\
      digit += (number[i] - '0') * pow(10, count-1);
      --count;
    }
  }

  return digit;
}

void vector_output (std::vector<int> vec){
  std::cout << "Your array: "; 
  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << " ";
  }
  std::cout << std::endl;
} 

std::vector<int> vector_sort(std::vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    int min_index = i;
    for (int j = i + 1; j < vec.size(); j++) {
      if (vec[j] < vec[min_index]) {
        min_index = j;
      }
    }
    std::swap(vec[i], vec[min_index]);
  }
  return vec;
}

bool number_validation (std::string number){
  for (int i = 0; i < number.length(); i++){
    if ((number[i] < '0' || number[i] > '9') && number[0] != '-') return false;
  }
  return true;
}

std::vector<int> vector_fill (std::vector<int> vec, std::string array_numbers){
  int digit_count = 0;
  int number_count = 0;
  std::vector<int> vec_curr(vec);
  std::string number;
  for (int i = 0; i <= array_numbers.length(); i++){
    if (array_numbers[i] == ' ' || i == array_numbers.length()){
      if (number_validation(number)) {
        if(string_parser(number, digit_count) == -1) return vec;
        else if (string_parser(number, digit_count) == -2) {
          vec.push_back(-2);
          return vec;
        }
        else {
          vec.push_back(string_parser(number, digit_count));
          vec = vector_sort(vec);
          if (vec.size() > 5) vec.pop_back();
          ++number_count;
          number = "";
          digit_count = 0;
          i++;
        }
      }
      else {
        std::cerr << "**Invalid characters in the " << number_count + 1 << " number**\n";
        for (int i = 0; i < number_count; i++) vec.pop_back();
        break;
      }
    }

    number += array_numbers[i];
    ++digit_count;
  }
  std::cerr << "**Error**\n";
  return vec_curr;
}

std::string input () {
  std::string numbers;
  std::cout << "Input: ";
  getline(std::cin, numbers);
  return numbers;
}

int main () {
  std::cout << "***Enter -2 to stop programm***\n";
  std::cout << "**Enter -1 at the end to accept numbers**\n";
  std::vector<int> vec;
  std::string numbers;
  numbers = input();

  while (true) {
    vec = vector_fill(vec, numbers);
    if (vec.size() > 0){
      if (vec[vec.size() - 1] == -2) break;
      else {
        if (vec.size() >= 5){
          std::cout << "Output: " << vec[4] << std::endl;
          vector_output(vec);          
        } else {
          std::cerr << "**Enter at least 5 numbers**\n";
        }
        numbers = "";
        numbers = input();
      }
    } else {
      numbers = "";
      numbers = input();
    }
    
  }
  std::cout << "***Programm stopped***\n";
}
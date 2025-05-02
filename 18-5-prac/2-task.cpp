#include <iostream>

void string_parser(int& n, int& k, const std::string& input) {
    std::string current_number;
    int target = 0;
    for (char ch : input) {
      if (ch >= '0' && ch <= '9') {
        current_number += ch;
      } else {
        if (!current_number.empty()) {
          int value = std::stoi(current_number);
          if (target == 0) {
            n = value;
            target = 1;
          } else {
              k = value;
              return;
            }
          current_number.clear();
        }
      }
    }

    // Обработка последнего числа в строке
    if (!current_number.empty()) {
        int value = std::stoi(current_number);
        if (target == 0) {
            n = value;
        } else {
            k = value;
        }
    }
}


int countWays (int n, int k = 3){
  if (n == 0) return 1;
  if (n < 0) return 0;

  int ways = 0;
    for (int jump = 1; jump <= k; ++jump) {
      ways += countWays(n - jump, k);
    }
    return ways;
}

int main() {
  int n = 0, k = 0, result;
  std::string input;
  std::cout << "Input: ";
  getline (std::cin, input);
  string_parser(n, k, input);

  result = countWays(n, k);
  std::cout << "Output: " << result; 
}
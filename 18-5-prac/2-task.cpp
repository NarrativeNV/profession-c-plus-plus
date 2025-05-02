#include <iostream>

void string_parser(int& n, int& k, std::string input){
  for (int i = 0; i < input.length(); i++){
    if (input[i] >= '0' && input[i] <= '9' && n == 0) {
      n = input[i] - '0';
      continue;
    }
    if (input[i] >= '0' && input[i] <= '9' && k == 0) {
      k = input[i] - '0';
      return;
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
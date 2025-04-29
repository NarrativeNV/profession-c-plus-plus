#include <iostream>
#include <limits>

bool value_validate (std::string number){
  for(int i = 0; i < number.length(); i++){
    if (number[i] < '0' || number[i] > '9') return false;
  }
  return true;
}

int main() {
  std::string expression;
  while(true){
    std::cout << "Enter expression(<a><operation><b>): ";
    std::cin >> expression;

    size_t op_pos = expression.find_first_of("+/*-");

    if (op_pos == std::string::npos || op_pos == 0 || op_pos == expression.length() - 1) {
      std::cerr << "Format error\n\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    double number_a = 0, number_b = 0;
    std::string number_a_str = expression.substr(0, op_pos);
    std::string number_b_str = expression.substr(op_pos + 1);
    if (value_validate(number_a_str) && value_validate(number_b_str)) {
      number_a = stod(number_a_str);
      number_b = stod(number_b_str);
    }
    else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "Input error!\n\n";
      continue;
    }

    char operation = expression[op_pos];

    double result = 0;

    if (operation == '+') result = number_a + number_b;
    else if (operation == '-') result = number_a - number_b;
    else if (operation == '/' && number_b != 0) result = number_a / number_b;
    else if (operation == '*') result = number_a * number_b;
    else {
      std::cerr << "Counting error\n\n";
      continue;
    }

    std::cout << "Result: " << result << "\n\n";
  }
}
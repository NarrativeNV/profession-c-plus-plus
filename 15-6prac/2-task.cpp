#include <iostream>
#include <vector>

int main () {
  std::vector<int> vec = {2, 7, 11, 15};
  int sum = 0;
  int first_num = 0;
  int second_num = 0;
  int result = 9;
  bool found = false;

  for (int i = 0; i < vec.size() && !found; i++){
    for (int j = i + 1; j < vec.size(); j++){
      sum+=vec[i] + vec[j];
      if (vec[i] > result || vec[j] > result) break;
      else if (sum == result) {
        first_num = vec[i];
        second_num = vec[j];
        found = true;
        break;
      }
      else sum = 0;
    } 
  }

  if (found){
    std::cout << "Array: ";
    for (int i = 0; i < vec.size(); i++){
      std::cout << vec[i] << " ";
    } 
    std::cout << "\nTarget: " << result << std::endl;
    std::cout << "Answer: " << first_num << " and " << second_num << std::endl;
    std::cout << first_num << " + " << second_num << " = " << result; 
  } else std::cout << "Not found";


}
#include <iostream>
#include <cmath>
#include <vector>

std::vector<int> vector_sort(std::vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    int min_index = i;
    for (int j = i + 1; j < vec.size(); j++) {
      if (abs(vec[j]) < abs(vec[min_index])) {
        min_index = j;
      }
    }
    std::swap(vec[i], vec[min_index]);
  }
  return vec;
}

int main(){
  std::vector<int> vec = {-100, -50, -5, 1, 10, 15};
  vec = vector_sort(vec);
  
  std::cout << "Output: ";
  for (int i = 0; i < vec.size(); i++){
    std::cout << vec[i] << " ";
  }

}
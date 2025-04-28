#include <iostream>
#include <vector>

std::pair<int, int> indexes_range (std::vector<int> vec){
  int max_sum = -2147483648;
  int last_sum = 0;
  int start = 0;
  std::pair<int, int> min_max_indexes;
  for (int i = 0; i <= vec.size(); i++){
    if (i == vec.size()) {
      last_sum = 0;
      ++start;
      i = start;
    }

    last_sum += vec[i];

    if (last_sum > max_sum){
      max_sum = last_sum;
      min_max_indexes.first = start;
      min_max_indexes.second = i;
    } 
  }
  return min_max_indexes;
}

int main() {
  std::vector<int> vec = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  std::pair<int, int> indexes(indexes_range(vec));
  std::cout << "\nThe largest amount between " <<  indexes.first << " and " << indexes.second << " indexes\n\n";
}
#include <iostream>
#include <map>
#include <string>
#include <limits>

#define INPUT(func) func(trainSize, trainVans)
#define CHECK(func) func(trainSize, trainVans, van_flags)
#define OUTPUT(func) func(van_flags)
#define FOR_EACH(i, limit) for (int i = 0; i < (limit); ++i)
#define MM_FOR(first, second) for (auto it = first; it != second; ++it)

void v_input(int& vans_am, int* van_pas){

  FOR_EACH(i, vans_am){ 
    printf("Input %d van passengers: ", i+1); 
    std::cin >> van_pas[i]; 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "\n**Input error**\n\n"; 
      --i; 
    }
    else if (van_pas[i] < 0) { 
      std::cerr << "\n**Input error**\n\n"; 
      --i; 
    }
  } 

}

void v_check(int& vans_am, int* van_pas, std::multimap<char, std::string>& flag){

  FOR_EACH(i, vans_am)
    if (van_pas[i] == 0) 
      flag.insert({'0', "Van " + std::to_string(i+1)});
    else if (van_pas[i] > 20)
      flag.insert({'1', "Van " + std::to_string(i+1)}); 

}

void v_output(std::multimap<char, std::string>& flags){

  std::pair<std::multimap<char, std::string>::iterator, 
  std::multimap<char, std::string>::iterator> empty = flags.equal_range('0');

  std::pair<std::multimap<char, std::string>::iterator, 
  std::multimap<char, std::string>::iterator> overflowing = flags.equal_range('1');

  if (overflowing.first != overflowing.second){ 
    std::cout << "**Overflowing vans**\n\n"; 
    MM_FOR(overflowing.first, overflowing.second)
      std::cout << it->second << std::endl; 
    std::cout << std::endl;
  } 

  if (empty.first != empty.second){ 
    std::cout << "**Empty vans**\n\n"; 
    MM_FOR(empty.first, empty.second)
      std::cout << it->second << std::endl; 
    std::cout << std::endl;
  }
  if (overflowing.first == overflowing.second && empty.first == empty.second)
    std::cout << "**The wagons are properly filled**\n\n";

}

int main(){

  int trainSize = 10;
  int trainVans[trainSize];
  std::multimap<char, std::string> van_flags;

  INPUT(v_input);
  CHECK(v_check);

  std::cout << std::endl;

  OUTPUT(v_output);

  int sum = 0;

  FOR_EACH(i, trainSize)
    sum += trainVans[i];
  std::cout << "Total passengers amount: " << sum;
}
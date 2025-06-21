#include <iostream>
#include <limits>

#define DAY1 "Monday"
#define DAY2 "Tuesday"
#define DAY3 "Wednesday"
#define DAY4 "Thursday"
#define DAY5 "Friday"
#define DAY6 "Saturday"
#define DAY7 "Sunday"

#define PRINT_DAY(num) std::cout << DAY##num

int main(){

  int wDay;
  std::cout << "Inpuy day: ";
  std::cin >> wDay;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if (!std::cin.fail() && wDay >= 1 && wDay <= 7)
    if (wDay == 1)
      PRINT_DAY(1);
    else if (wDay == 2)
      PRINT_DAY(2);
    else if (wDay == 3)
      PRINT_DAY(3);
    else if (wDay == 4)
      PRINT_DAY(4);
    else if (wDay == 5)
      PRINT_DAY(5);
    else if (wDay == 6)
      PRINT_DAY(6);
    else if (wDay == 7)
      PRINT_DAY(7);
  else 
    std::cerr << "Input error\n";
}
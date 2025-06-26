#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <limits>
#include <sstream>

int main() {
  std::time_t time = std::time(nullptr);
  std::time_t container = time;
  std::tm min_sec = *std::localtime(&time);
  min_sec.tm_hour = 0;
  min_sec.tm_min = 0;
  min_sec.tm_sec = 0;

  while (true) {
    std::cout << "Input min.sec: ";
    std::cin >> std::get_time(&min_sec, "%M.%S");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail()) {
      std::cerr << "\n**FORMAT ERROR**\n\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    break;
  }

  std::time_t normalize = std::mktime(&min_sec);
  min_sec = *std::localtime(&normalize);
  std::cout << "\n**START**\n\n";

  while (min_sec.tm_min > 0 || min_sec.tm_sec > 0) {
    time = std::time(nullptr);
    if (time != container) {
      std::cout << std::put_time(&min_sec, "%M:%S") << std::endl;
      normalize -= 1;
      min_sec = *std::localtime(&normalize);
      container = time;
    }
  }
  std::cout << "\n**TIME FINISHED**\n\n";
}
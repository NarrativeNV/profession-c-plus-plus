#include <iostream>

// #define SPRING
// #define SUMMER
// #define AUTUMN
// #define WINTER

#if defined(SPRING)

  int main() {
      std::cout << "Spring" << std::endl;
      return 0;
  }

#elif defined(SUMMER)

  int main() {
      std::cout << "Summer" << std::endl;
      return 0;
  }

#elif defined(AUTUMN)

  int main() {
      std::cout << "Autumn" << std::endl;
      return 0;
  }

#elif defined(WINTER)

  int main() {
      std::cout << "Winter" << std::endl;
      return 0;
  }

#else

  int main() {
      std::cerr << "Error: No season macro defined!" << std::endl;
      return 1;
  }

#endif
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <limits>

int main(){
  
  std::cout << "\n\t**Input \"stop\" to complete session**\n\n";

  std::srand(std::time(nullptr));

  std::string fish;
  bool catched = false;
  int fish_per_session = 0;
  int fish_catched = 0;
  int fish_broke = 0;

  while (true){
    std::cout << "Input type of fish: ";
    std::cin >> fish;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::ifstream river("fishing\\river.txt");

    if (fish == "stop") {
      std::cout << "\nTotal fish caught: " << fish_per_session << "\n\n";
      return 1;
    }
      
    std::string fish_match;

    while (!river.eof()){

      river >> fish_match;
      if (fish_match == fish){

        catched = std::rand() % 2;
        if (catched){

          std::ofstream basket("fishing\\basket.txt", std::ios::app);
          ++fish_catched;
          ++fish_per_session;
          basket << fish << '\n';
          basket.close();

        } else ++fish_broke;

      }

    }

    river.close();

    if (fish_catched > 0){

      fish += '\0';

      if (fish_broke > 0){
        printf("\n**%d %s(s/es) %s caught**\n", fish_catched, fish.c_str(), 
        fish_catched == 1 ? "was" : "were");
        printf("**%d %s(s/es) %s broke**\n\n", fish_broke, fish.c_str(), 
        fish_broke == 1 ? "was" : "were");
      } else 
          printf("\n**%d %s(s/es) %s caught**\n\n", fish_catched, fish.c_str(), 
          fish_catched == 1 ? "was" : "were");
        
    } else std::cerr << "\n**The catch failed**\n\n";

    fish_catched = 0;
    fish_broke = 0;

  }

}
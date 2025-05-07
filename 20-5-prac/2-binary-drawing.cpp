#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

int main(){
  int w = 0;
  int h = 0;

  std::srand(std::time(nullptr));

  while(true){

    while(true){
      std::cout << "Input width(px) and height(px): ";
      std::cin >> w >> h;

      if (std::cin.fail() || h < 1 || w < 1){
        std::cerr << "\n**Input error**\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else break;
    }

    int value = 0;

    std::ofstream pic("pic.txt");

    if (pic.is_open()){

      for (int i = 0; i < h; ++i){

        for(int j = 0; j < w; ++j){
          
          value = std::rand() % 2;
          pic << value << "\t";

        }

        pic << std::endl;

      }

      pic.close();
      std::cout << "\n*Success write**\n\n";

    } else std::cerr << "\n**Open error**\n\n";

  }
}
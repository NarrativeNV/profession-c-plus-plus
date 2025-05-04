#include <iostream>
#include <fstream>
#include <string>
#include <limits>

int main(){
  while(true){
    std::string n_word = "";
    std::cout << "Input necessary word: ";
    std::cin >> n_word;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::ifstream words;
    words.open("C:\\words.txt");

    int repeat = 0;

    while (!words.eof()){
      std::string word;
      words >> word;
      if (word == n_word) ++repeat;
    }

    words.close();
    printf("\"%s\" repeats: %d\n\n", n_word.c_str(), repeat);
  }
}
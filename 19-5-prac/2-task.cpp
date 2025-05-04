#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(){
  std::string path;
  std::cout << "Input file path: ";
  std::cin >> path;
  std::ifstream words;
  words.open(path, std::ios::binary);

  int bytes_read = 0;
  if (words.is_open()){
    std::cout << std::endl;
    while(!words.eof()){
      char text[50];
      words.read(text, sizeof(text));
      bytes_read = words.gcount();
      std::cout.write(text, bytes_read);
    }
    std::cout << std::endl;
    words.close();
  } else std::cerr << "Open Error";

}
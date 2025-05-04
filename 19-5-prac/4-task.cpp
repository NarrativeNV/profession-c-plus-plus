#include <iostream>
#include <fstream>
#include <string>

int main(){
  std::string path;
  std::cout << "Input path to png: ";
  std::cin >> path;

  std::ifstream png;
  png.open(path, std::ios::binary);
  char type[5];

  if (png.is_open()){

    png.read(type, sizeof(type));
    png.close();
    type[4] = '\0';
    std::string file_type = type;
    if (file_type.substr(1, 3) == "PNG") std::cout << "This is a PNG file";
    else std::cout << "This is not a PNG file.";
  } else std::cerr << "Open error";
}
#include <iostream>
#include <cstring>

bool substring(const char* str, const char* substr){
  char temp_str[strlen(substr)];
  temp_str[0] = '\0';
  for (int i = 0; i < strlen(str); i++){
    if (*(str + i) == *(substr)) {
      for (int j = 0; j < strlen(substr); j++){
        if (*(str + i) == *(substr + j)) {
          temp_str[j] = *(str+i);
          ++i;
        }
        else {
          temp_str[0] = '\0';
          break;
        }
      }
    }
    if (temp_str[0] != '\0') return true;
  }
  return false;
}

int main() {
  const char* a = "Hello world";
  const char* b = "wor";
  const char* c = "banana";

  std::cout << std::boolalpha << substring(a, b) << " " << substring(a, c);
}
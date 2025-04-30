#include <iostream>

void reverse (int* a, int size){
  bool even = true;
  if (size % 2 != 0) {
    size -= 1;
    even = false;
  }
  int half = size / 2;
  for (int i = 0; i < half; i++){
    // int first = *(a+i);
    // int second = even ? *(a + size - 1 - i) : *(a + size - i);
    std::swap(*(a+i), even ? *(a + size - 1 - i) : *(a + size - i));
  }
}

int main() {
  int a[] = {2, 4, 6, 8, 10, /*12*/};
  int size = sizeof(a) / sizeof(a[0]);
  reverse(a, size);
  for (int i = 0; i < size; i++){
    std::cout << a[i] << " ";
  }
}
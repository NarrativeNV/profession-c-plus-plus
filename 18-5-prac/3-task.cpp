#include <iostream>

void evendigits (long long n, int& ans){
  if (n == 0) return;
  if ((n % 10) % 2 == 0) ++ans;
  evendigits(n / 10, ans);

}

int main(){
  int ans = 0;
  evendigits(9223372036854775806, ans);

  std::cout << "ans: " << ans;
}
#include <iostream>
#include <cmath>
#include <limits>

bool null_speed (double speed, double epsilon) {
  return (speed - 0 <= epsilon) || (speed - 0 == 0);
} 

bool max_speed (double speed, double epsilon) {
  return speed - 150 > epsilon;
}

int main () {

  double speed = 0.0;
  double different = 0.0;
  double delta = 0.01;
  char speed_str[20];
  bool stop = false;

  std::cout << "Speed: 0\n";
  do {
    std::cout << "Speed delta: ";
    std::cin >> different;
    if (std::cin.fail()){
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Input error!\n\n";
      continue;
    }
    speed += different;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (max_speed(speed, delta)) {
      std::cerr << "Max speed is 150km/h\n";
      speed -= different;
    }
    else {
      sprintf(speed_str, "Speed: %.1f\n", speed);
      if (null_speed(speed, delta)) std::cout << "Speed: 0\n";
      else std::cout << speed_str;
    }
  } while (!null_speed(speed, delta));
  std::cout << "Car has stopped\n";
}
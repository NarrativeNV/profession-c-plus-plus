#include <iostream>
#include <cassert>

float travelTime(float distance, float speed){
    assert(speed > 0 && distance > 0);
    float travelTime = distance/speed;
    return travelTime;
}

int main(){
    float distance;
    std::cout << "Input distance: ";
    std::cin >> distance;

    float speed;
    std::cout << "Input speed: ";
    std::cin >> speed;

    float time = travelTime(distance, speed);
    std::cout << "Travel time: " << time;
}

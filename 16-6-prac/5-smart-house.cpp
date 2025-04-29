#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

enum home_systems {
  LIGHT_INDOOR = 1,
  LIGHT_OUTDOOR_GARDEN = 2,
  HEATING_INDOOR = 4,
  WATER_HEATING_WELL_PUMP = 8,
  AIR_CONDITIONER_INDOOR = 16
};

void print_state(int home_systems_state, std::vector<bool> curr_states, std::vector<bool> last_states, int color_temp, int hours){
  if (curr_states != last_states){
    if (curr_states[0] == true && last_states[0] == false) std::cout << "Lights indoor ON!\n";
    if (curr_states[0] == false && last_states[0] == true) std::cout << "Lights indoor OFF!\n";

    if (curr_states[1] == true && last_states[1] == false) std::cout << "Ligths in garden ON!\n";
    if (curr_states[1] == false && last_states[1] == true) std::cout << "Ligths in garden OFF!\n";

    if (curr_states[2] == true && last_states[2] == false)  std::cout << "Heating indoor ON!\n";
    if (curr_states[2] == false && last_states[2] == true)  std::cout << "Heating indoor OFF!\n";

    if (curr_states[3] == true && last_states[3] == false)  std::cout << "Water heating ON!\n";
    if (curr_states[3] == false && last_states[3] == true)  std::cout << "Water heating OFF!\n";

    if (curr_states[4] == true && last_states[4] == false) std::cout << "Conditioner ON!\n";
    if (curr_states[4] == false && last_states[4] == true) std::cout << "Conditioner OFF!\n";
  }
  printf("Color temperature: %dK\n", color_temp);
}

void borders () {
  for (int i = 0; i < 25; i++){
    std::cout << "-";
  }
  std::cout << std::endl;
}

std::vector<bool> state_indexing (std::vector<bool> state, int home_systems_state, int exp){
  for (int i = 0; i < 5; i++){
    state[i] = (home_systems_state & exp) != 0;
    exp *= 2;
  }
  return state;
}

int main(){
  const double epsilon = 0.01;

  int hours = 0;
  int days_curr = 1;
  int days_last = 0;
  int temp_inside = 0;
  int temp_outside = 0;
  int color_temp = 5000;
  std::string movement;
  std::string lights;

  std::string parameters;
  int home_systems_state = 0;
  int exp = 1;

  std::vector<bool> last_states(5, false);
  std::vector<bool> curr_states(5, false);

  do {
    if (days_curr != days_last) printf("\nDay: %d\n", days_curr);
    days_last = days_curr;
    printf("\nTime: %02d:00", hours);
    std::cout << "\nTemperature inside, temperature outside, movement, lights:\n";
    getline (std::cin, parameters);
    std::stringstream par_stream(parameters);
    par_stream >> temp_inside >> temp_outside >> movement >> lights;

    std::cout << std::endl;
    borders();

    if ((movement == "yes" || movement == "no") && (lights == "on" || lights == "off") && !std::cin.fail()){

      if (hours == 0) color_temp = 5000;
      if (temp_outside < 0) home_systems_state |= WATER_HEATING_WELL_PUMP;
      if (temp_outside > 5) home_systems_state &= ~WATER_HEATING_WELL_PUMP;
      if (hours > 16 && hours < 5 && movement == "yes") home_systems_state |= LIGHT_OUTDOOR_GARDEN;
      else home_systems_state &= ~LIGHT_OUTDOOR_GARDEN;
      if (temp_inside < 22) home_systems_state |= HEATING_INDOOR;
      if (temp_inside >= 25) home_systems_state &= ~HEATING_INDOOR;
      if (temp_inside >= 30) home_systems_state |= AIR_CONDITIONER_INDOOR;
      if (temp_inside <= 25) home_systems_state &= ~AIR_CONDITIONER_INDOOR;
      if (lights == "on") home_systems_state |= LIGHT_INDOOR;
      else home_systems_state &= ~LIGHT_INDOOR;
      if (hours > 16 && hours <= 20 && (home_systems_state & LIGHT_INDOOR)) color_temp -= 460;
      ++hours;
      if (hours == 24) {
        hours = 0;
        ++days_curr;
      }

      curr_states = state_indexing(curr_states, home_systems_state, exp);
      print_state(home_systems_state, curr_states, last_states, color_temp, hours);
      borders();
      last_states = curr_states;
    }

    else {
      std::cout << "Input error\n";
      borders();
      std::cin.clear();
      continue; 
    }
      
  } while (days_curr <= 2);


}
#include <iostream>
#include <string>

void player_step (std::string current_player, int &x, int&y, char playing_field[][3]){
  bool step_success = false;
  while (!step_success) {
    std::cout << "Player " << current_player << " enter coordinates(x y): ";
    std::cin >> x >> y;
    if (playing_field[x-1][y-1] == '.') step_success = true;
    else std::cout << "Is the cell already occupied or does not exist\nTry Again\n\n";
  }
}

void field_output(char playing_field[][3]){
  std::cout << std::endl;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      std::cout << playing_field[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

bool combo_validate (std::string &combination){
  if (combination == "XXX") { 
    std::cout << "Player X won!\n";
    return true;
  }
  if (combination == "OOO") {
    std::cout << "Player O won!\n";
    return true;
  }
  combination = "";
  return false;
}

bool draw (char playing_field [][3]){
  int free_count = 0;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if (playing_field[i][j] == '.') ++free_count;
    }
  }
  if (free_count == 0) {
    std::cout << "Draw!\n";
    return true;
  }
  else return false; 
}

bool game_over (char playing_field[][3], int x, int y){
  std::string combination;

  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      combination += playing_field[i][j];
    }
    if (combo_validate(combination)) return true;
  }

  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      combination += playing_field[j][i];
    }
    if (combo_validate(combination)) return true;
  }

  for (int i = 0; i < 3; i++){
    combination += playing_field[i][i];
  }
  if (combo_validate(combination)) return true;

  int j = 2;

  for (int i = 0; i < 3; i++){
      combination += playing_field[i][j];
      j -= 1;
    }
  if (combo_validate(combination)) return true;
    
  return false;
}

int main() {
  while (true){
    std::cout << "\nTic-Tac-Toe\n";
    char playing_field[3][3] = {{'.', '.', '.'},
                                {'.', '.', '.'},
                                {'.', '.', '.'}};
    std::string current_player;
    int x, y;
    while(true) {

      field_output(playing_field);
      if (game_over(playing_field, x, y) or draw(playing_field)) break;

      current_player = "X";
      player_step(current_player, x, y, playing_field);
      playing_field[x-1][y-1] = 'X';
      field_output(playing_field);
      if (game_over(playing_field, x, y) or draw(playing_field)) break;

      current_player = "O";
      player_step(current_player, x, y, playing_field);
      playing_field[x-1][y-1] = 'O';
    }
  }
}
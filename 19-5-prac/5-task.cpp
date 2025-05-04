#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>

void play_round (std::pair<std::string, std::string>& QA, int& scores_p, int& scores_s, int& cur_sector){
  std::string answer;
  std::cout << "\nSector: " << cur_sector << std::endl;
  std::cout << "Question: " << QA.first << std::endl;
  std::cout << "Player answer: ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getline(std::cin, answer);
  if (answer == QA.second) {
    ++scores_p;
    std::cout << "\n**Congratulations!**\n**Player get 1 score!**\n\n";
    return;
  }
  else {
    ++scores_s;
    std::cout << "\n**Spectators get 1 score!**\n\n";
    return;
  }
}

void sector_select (std::vector<int>& played_sectors, int& cur_sector){
  bool free_sector = true;
  bool same_sector = false;
  for (int i = 0; i < played_sectors.size() - 1; i++){
    if (played_sectors[i] == played_sectors[played_sectors.size()-1] && played_sectors.size() > 2){
      played_sectors.pop_back();
      same_sector = true;
      break;
    }
  }

  if (same_sector){
    printf("**Sector %d has already been played**\n", cur_sector);
    ++cur_sector;
    for (int i = 0; i < played_sectors.size(); i++){
      if (cur_sector == played_sectors[i]){
        printf("**Sector %d has already been played**\n", cur_sector);
        ++cur_sector;
        free_sector = false;
      }
      if (cur_sector > 13) cur_sector = 1;
    }
    free_sector = true;
  }

  if (free_sector && same_sector) {
    played_sectors.push_back(cur_sector);
    return;
  } else {
    std::cout << "**Success!**\n";
    return;
  }
}

void sector_input (int& cur_sector, int& offset, std::vector<int>& played_sectors){
  while(true){
    std::cout << "\nInput offset: ";
    std::cin >> offset;
    std::cout << std::endl;
    if (std::cin.fail() || offset < 1 || offset > 12) {
      std::cerr << "**Input error!**\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else{
      if (cur_sector + offset > 13){
        int steps = 13 - cur_sector;
        cur_sector = 0;
        offset -= steps;
      }
      cur_sector += offset;
      played_sectors.push_back(cur_sector);
      return;
    }
  }
}

int main(){
  int cur_sector = 1;
  int offset = 0;
  int scores_player = 0;
  int scores_spectators = 0;

  std::vector<int> played_sectors;
  while(true){
    printf("Player: %d\n", scores_player);
    printf("Spectators: %d\n\n", scores_spectators);
    std::cout << "Current sector: " << cur_sector;
    sector_input(cur_sector, offset, played_sectors);
    sector_select(played_sectors, cur_sector);;

    std::stringstream path_pars_q;
    std::stringstream path_pars_a;
    path_pars_q << "C:\\WhatWhereWhen\\" << cur_sector << "Q.txt";
    path_pars_a << "C:\\WhatWhereWhen\\" << cur_sector << "A.txt";
    std::string path_q = path_pars_q.str();
    std::string path_a = path_pars_a.str();

    std::pair<std::string, std::string> QA;
    std::ifstream sectors;
    sectors.open(path_q);
    getline(sectors, QA.first);
    sectors.close();
    sectors.open(path_a);
    getline(sectors, QA.second);
    sectors.close();
    play_round(QA, scores_player, scores_spectators, cur_sector);
    if (scores_player == 6 || scores_spectators == 6)
      if (scores_player == 6) {
        std::cout << "Player WON with " << scores_player << " scores";
        break;
      }
      else {
        std::cout << "Spectators WON with " << scores_spectators << " scores";
        break;
      }


  }
}
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

int main(){

  std::srand(std::time(nullptr));
  std::string path = "ATM\\banknotes.bin";

  const int size = 6;
  const int atm_size = 7;
  int nominals[size] = {100, 200, 500, 1000, 2000, 5000};
  int nom_amount[size] = {0};
  int last_amount[size] = {0};
  int total_sum = 0;

  std::ofstream atm_w(path, std::ios::binary);

  int rand_nom = 0;
  int cur_bank = 0;
  int to_fill = atm_size;

  for (int i = 0; i < size; ++i)
    cur_bank += nom_amount[i];

  to_fill = atm_size - cur_bank;

  for (int i = 0; i < to_fill; ++i){

    rand_nom = nominals[std::rand() % size];
    atm_w.write((char*)&rand_nom, sizeof(rand_nom));

    for (int j = 0; j < size; ++j){

      if (rand_nom == nominals[j]){

        total_sum += rand_nom;
        ++nom_amount[j];
        break;

      }

    }

  }

  atm_w.close();

  std::cout << std::endl;

  std::vector<int> atm_bank;

  int cash = 0;

  std::ifstream atm(path, std::ios::binary);

  if (atm.is_open()){

    while(atm.read((char*)&cash, sizeof(cash))){

      atm_bank.push_back(cash);

    }

    for (int i = 0; i < atm_bank.size(); ++i){

      std::cout << atm_bank[i] << " ";

    }

    atm.close();

  }

  std::cout << "\n\n";



}
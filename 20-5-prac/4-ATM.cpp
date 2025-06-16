#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <limits>

void withdrawal_money(const int& size, const int& atm_size, int* nominals, int* nom_amount, int& total_sum, std::string& path, int* last_amount){

  int cash = 0;
  int sum_last = total_sum;
  int cur_bn = 0;
  
  for (int i = 0; i < size; ++i)
    cur_bn += nom_amount[i];

  while(true){

    std::cout << "Input cash: ";
    std::cin >> cash;

    if (cur_bn == 0){

      std::cerr << "\n**ATM is empty! Input \"+\" to fill**\n";
      return;

    }

    if (std::cin.fail() || cash % 10 != 0 || cash > total_sum || cash < 0){

      std::cerr << "\n**Invalid value**\n\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } else if (cash == 0) return;
    else break;

  }

  total_sum -= cash;

  for (int i = size - 1; i >= 0; --i){

    if (cash == 0) break;
    
    while (true){

      if (nom_amount[i] == 0 || cash / nominals[i] == 0) break;
      cash -= nominals[i];
      --nom_amount[i];

    }

  }

  if (cash == 0){

    std::cout << "\n**Money given**\n\n";

    for (int i = 0; i < size; ++i)
      if (last_amount[i] - nom_amount[i] != 0)
        printf("%d banknote: %d\n", nominals[i], last_amount[i] - nom_amount[i]);

    for (int i = 0; i < size; ++i)
      last_amount[i] = nom_amount[i];

  } else {

    std::cerr << "\n**ATM cannot give this sum**\n";
    total_sum = sum_last;
    for (int i = 0; i < size; ++i)
      nom_amount[i] = last_amount[i];

    return; 

  }
}

void atm_fill(const int& size, const int& atm_size, int* nominals, int* nom_amount, int& total_sum, std::string& path) {

  std::ofstream atm(path, std::ios::binary | std::ios::app);

  int rand_nom = 0;
  int cur_bank = 0;
  int to_fill = atm_size;

  for (int i = 0; i < size; ++i)
    cur_bank += nom_amount[i];

  to_fill = atm_size - cur_bank;

  for (int i = 0; i < to_fill; ++i){

    rand_nom = nominals[std::rand() % size];
    atm.write((char*)&rand_nom, sizeof(rand_nom));

    for (int j = 0; j < size; ++j){

      if (rand_nom == nominals[j]){

        total_sum += rand_nom;
        ++nom_amount[j];
        break;

      }

    }

  }

  atm.close();

}

void nom_count (std::string& path, const int& size, int* nominals, bool& corrupt, int* nom_amount, int& total_sum){

  std::ifstream atm_check(path, std::ios::binary);

  int cash = 0;

  while (atm_check.read((char*)&cash, sizeof(cash))){

    if (cash != nominals[0] && cash != nominals[1] && cash != nominals[2] 
      && cash != nominals[3] && cash != nominals[4] && cash != nominals[5])
        corrupt = true;

    if (corrupt) {

      std::cout << "\n**Corrupted file**\n\n";
      atm_check.close();
      return;

    }

    for (int i = 0; i < size; ++i){

      if (cash == nominals[i]){

        total_sum += cash;
        ++nom_amount[i];
        break;

      }

    }

  }
  
  atm_check.close();

}

void status_output (const int& size, int* nominals, int* nom_amount, int total_sum = 0) {

  printf("\nTotal sum: %d\n\n", total_sum);

  for (int i = 0; i < size; ++i)
    printf("%d nominal: %d pcs\n", nominals[i], nom_amount[i]);

  std::cout << std::endl;

}

void bin_output (std::string& path){

  std::cout << std::endl;

  std::vector<int> atm_bank;

  int cash = 0;

  std::ifstream atm(path, std::ios::binary);

  if (atm.is_open()){

    while(atm.read((char*)&cash, sizeof(cash)))
      atm_bank.push_back(cash);


    for (int i = 0; i < atm_bank.size(); ++i){

      std::cout << atm_bank[i] << " ";

    }

    atm.close();

  }

  std::cout << "\n\n";

}

int main() {

  std::srand(std::time(nullptr));
  std::string path = "ATM\\banknotes.bin";
  std::cout << "\n**Welcome to ATM! Input \"+\", \"-\" or \"stop\"**\n";

  const int size = 6;
  const int atm_size = 1000;
  int nominals[size] = {100, 200, 500, 1000, 2000, 5000};
  int nom_amount[size] = {0};
  int last_amount[size] = {0};
  int total_sum = 0;

  bool corrupt = false;

  std::ifstream atm_check(path, std::ios::binary);

  if (atm_check.is_open()){
    atm_check.close();

    nom_count(path, size, nominals, corrupt, nom_amount, total_sum);
    if (corrupt) return 0;

    for (int i = 0; i < size; ++i)
      last_amount[i] = nom_amount[i];

    status_output(size, nominals, nom_amount, total_sum);

  } else status_output(size, nominals, nom_amount);

  while (true){
  // bin_output(path);
  std::string action;
  std::cout << "Input action: ";
  std::cin >> action;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if (action == "+"){
    int cur_bn = 0;
    
    for (int i = 0; i < size; ++i)
      cur_bn += nom_amount[i];

    if (cur_bn == atm_size){

      std::cout << "\n**ATM is full**\n\n";
      continue;

    }
    std::cout << "\n**Filling ATM**\n";
    atm_fill(size, atm_size, nominals, nom_amount, total_sum, path);
    for (int i = 0; i < size; ++i)
      last_amount[i] = nom_amount[i];
    // bin_output(path);
    status_output(size, nominals, nom_amount, total_sum);
  }
  else if (action == "-") {
    withdrawal_money(size, atm_size, nominals, nom_amount, total_sum, path, last_amount);

    std::ofstream atm(path, std::ios::binary);
    int cur_bn = 0;

    for (int i = 0; i < size; ++i){
      cur_bn = nominals[i];

      for (int j = 0; j < nom_amount[i]; j++)
        atm.write((char*)&cur_bn, sizeof(cur_bn));

    }

    atm.close();

    // bin_output(path);

    status_output(size, nominals, nom_amount, total_sum);
  } else if (action == "stop"){

    std::cout << "\n**ATM stopped**\n\n";
    return 1;

  }
  else 
    std::cerr << "\n**Unknown command**\n\n";

  }

  

  // std::ofstream atm(path, std::ios::binary);


}

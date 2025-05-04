#include <iostream>
#include <fstream>
#include <string>

int main(){
  const short statement_size = 4;
  std::string max_payout[statement_size];
  std::string inf_buf[statement_size];
  int sum = 0; 
  int max_sum = 0;

  std::ifstream statement;
  statement.open("C:\\statement.txt");

  if (statement.is_open()){

    while (!statement.eof()){
    
      for (int i = 0; i < statement_size; ++i)
        statement >> inf_buf[i];

      sum += std::stoi(inf_buf[2]);

      if (std::stoi(inf_buf[2]) > max_sum){
        max_sum = std::stoi(inf_buf[2]);
        for (int i = 0; i < statement_size; ++i)
          max_payout[i] = inf_buf[i];
      } 

    }
    statement.close();
    
    printf("\nTotal amount of cash paid out: %d %d\n\n", sum/1000, sum%1000);
    std::cout << "**The person with the maximum payout amount**\n";
    printf("\t%s %s %s %s\n\n", max_payout[0].c_str(), max_payout[1].c_str(), max_payout[2].c_str(), max_payout[3].c_str());

  } else std::cerr << "Open error";
}
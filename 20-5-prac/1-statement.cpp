#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include <ctime>

bool isLeapYear(int year) {
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      return true;  
  } else {
      return false; 
  }
}

bool date_valid (int& day, int& month, int& year){

  if (day > 31 || month > 12)
    return false;

  bool leap_year = isLeapYear(year);

  time_t cur_date = time(nullptr);
  tm* local_time = localtime(&cur_date);

  int cur_year = local_time->tm_year + 1900;

  if (year <= cur_year){

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leap_year) 
      days_in_month[1] = 29; 

    if (day > days_in_month[month - 1])
      return false;

  }

  else return false;

  return true;
}

bool data_valid (std::string& name, std::string& subname, 
  int& payout, std::string& date){

    for (int i = 0; i < name.length(); ++i)
      if ((name[i] < 'A' || name[i] > 'Z') 
      && (name[i] < 'a' || name[i] > 'z'))
        return false;

    for (int i = 0; i < subname.length(); ++i)
      if ((subname[i] < 'A' || subname[i] > 'Z') 
      && (subname[i] < 'a' || subname[i] > 'z'))
        return false;

    if (payout < 0)
      return false;

    std::string day_s = date.substr(0, 2);
    std::string month_s = date.substr(3, 2);
    std::string year_s = date.substr(6);

    int day = 0;
    int month = 0;
    int year = 0;

    for (int i = 0; i < 2; ++i)
      if ((day_s[i] < '0' || day_s[i] > '9') 
      && (month_s[i] < '0' || month_s[i] > '9'))
        return false;
      else {
        day = std::stoi(day_s);
        month = std::stoi(month_s);
      }

    for (int i = 0; i < 4; ++i)
      if (year_s[i] < '0' || year_s[i] > '9')
        return false;
      else year = std::stoi(year_s);
    
    if(!date_valid(day, month, year)){
      std::cerr << "\n**Invalid date**\n\n";
      return false; 
    }
    
    return true;
  }

void data_input (std::string& data, std::string& name, 
  std::string& subname, int& payout, std::string& date){
    while (true){
      std::cout << "Input data: ";
      getline(std::cin, data);
      std::stringstream data_s(data);
      data_s >> name >> subname >> payout >> date;

      if (data_s.fail()){
        std::cerr << "\n**Input error**\n\n";
        data_s.clear();
        data_s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else return;
    }
}

int main(){
  int payout = 0;
  std::string data;
  std::string name;
  std::string subname;
  std::string date;

  while (true){

    data_input(data, name, subname, payout, date);
    if(data_valid(name, subname, payout, date)){
      
      std::ofstream data_w("statement.txt", std::ios::app);
      data_w << "\n\n" << data;
      data_w.close();
      std::cout << "\n**Success write**\n\n";

    } else std::cerr << "\n**Incorrect data**\n\n";

  }
}
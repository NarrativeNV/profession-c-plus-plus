#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>

#define ERROR_IN { std::cerr << "\n**INPUT ERROR**\n\n"; continue; }
#define ERROR_DATE { std::cerr << "\n**DATE ERROR**\n\n"; continue; } 
#define TIME_NULL(time) { time.tm_sec = 0; time.tm_min = 0; time.tm_hour = 0; }

struct birthday {

  std::string name;
  std::tm date;

};

int main(){

  birthday bd;
  std::time_t today_t = std::time(nullptr);
  std::tm today = *std::localtime(&today_t);
  bd.date = *std::localtime(&today_t);
  TIME_NULL(today)
  TIME_NULL(bd.date)
  today_t = mktime(&today);

  std::vector<birthday> bd_storage;
  std::cout << "\n**Format: name 00/00/0000**\n\n";

  while(true){

    std::string request;
    std::cout << "Input request: ";
    getline(std::cin, request);
    std::istringstream ss_req(request);

    if (!request.empty()){

      ss_req >> bd.name;
      if(bd.name != "end"){

        ss_req >> std::get_time(&bd.date, "%d/%m/%Y");
        if (!ss_req.fail()){

          int day = bd.date.tm_mday;
          int month = bd.date.tm_mon;
          int year = bd.date.tm_year;
          std::time_t normalize = mktime(&bd.date);
          bd.date = *std::localtime(&normalize);

          if (day == bd.date.tm_mday && month == bd.date.tm_mon && year == bd.date.tm_year)
            if (today_t >= normalize)
              bd_storage.push_back(bd);
            else
              ERROR_DATE
          else
            ERROR_DATE

        }
        else
          ERROR_DATE

      }
      else
        break;

    }
    else
      std::cerr << "\n**Input something**\n\n";

  }

  std::multimap<double, std::pair<std::tm, std::string>> differences;

  for (int i = 0; i < bd_storage.size(); ++i) {

    std::tm date_bd = bd_storage[i].date;
    TIME_NULL(date_bd)
    date_bd.tm_year = today.tm_year;

    if (date_bd.tm_mon < today.tm_mon ||
       (date_bd.tm_mon == today.tm_mon && date_bd.tm_mday < today.tm_mday)) {
        date_bd.tm_year += 1;
    }

    std::time_t date_t = mktime(&date_bd);
    double diff = std::difftime(date_t, today_t);
    differences.insert({diff, {date_bd, bd_storage[i].name}});

  }

  auto key = differences.begin();

  auto diff_it = differences.equal_range(key->first);
  auto it = diff_it.first;

  do{

    std::cout << std::endl;
    if(std::abs(it->first) < 1.0)
      std::cout << "*Today*\n";
  
    std::cout << "Name: " << it->second.second;
    std::cout << "\nBirthday: " << std::put_time(&it->second.first, "%d/%m/%Y");
    ++it;
    std::cout << std::endl;

  }while(it != diff_it.second);

}
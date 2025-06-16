#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

const int date_len = 10;
int fname_len;
int sname_len;

struct statement
{
  std::string first_name = "empty";
  std::string second_name = "empty";
  std::string date = "00.00.0000";
  int payout_sum = 0;
};


bool isLeapYear(int year) {
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      return true;  
  } else {
      return false; 
  }
}

bool date_valid(int& day, int& month, int& year) {
    if (day > 31 || month > 12 || day < 1 || month < 1)
        return false;

    bool leap_year = isLeapYear(year);

    time_t cur_date = time(nullptr);
    tm* local_time = localtime(&cur_date);

    int cur_year = local_time->tm_year + 1900;
    int cur_month = local_time->tm_mon + 1;  // tm_mon от 0 до 11
    int cur_day = local_time->tm_mday;

    if (year > cur_year)
        return false;
    else if (year == cur_year) {
        if (month > cur_month)
            return false;
        else if (month == cur_month && day > cur_day)
            return false;
    }

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (leap_year)
        days_in_month[1] = 29;

    if (day > days_in_month[month - 1])
        return false;

    return true;
}

bool data_valid (statement& data){

  if (data.first_name[0] < 'A' || data.first_name[0] > 'Z') return false;
  if (data.second_name[0] < 'A' || data.second_name[0] > 'Z') return false;

    for (int i = 0; i < data.first_name.length(); ++i)
      if ((data.first_name[i] < 'A' || data.first_name[i] > 'Z') 
      && (data.first_name[i] < 'a' || data.first_name[i] > 'z'))
        return false;

    for (int i = 0; i < data.second_name.length(); ++i)
      if ((data.second_name[i] < 'A' || data.second_name[i] > 'Z') 
      && (data.second_name[i] < 'a' || data.second_name[i] > 'z'))
        return false;

    if (data.payout_sum < 0)
      return false;

    std::string day_s = data.date.substr(0, 2);
    std::string month_s = data.date.substr(3, 2);
    std::string year_s = data.date.substr(6);

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
      std::cerr << "\n**Invalid date**";
      return false; 
    }
    
    return true;
  }

void data_write (statement& data, std::vector<statement>& data_storage){

  std::ofstream data_file("statement.bin", std::ios::app | std::ios::binary);

  if (!data_file.is_open()){

    std::cerr << "\n**File open error**\n\n";
    return;

  }

  data_file.write((char*)&fname_len, sizeof(int));
  data_file.write((char*)&sname_len, sizeof(int));

  data_file.write((char*)data.first_name.c_str(), data.first_name.length());
  data_file.write((char*)data.second_name.c_str(), data.second_name.length());
  data_file.write((char*)data.date.c_str(), data.date.length());
  data_file.write((char*)&data.payout_sum, sizeof(int));

  data_file.close();

  data_storage.push_back(data);

}

void data_output (std::vector<statement> data_storage){
  std::cout << "\n";
  for (int i = 0; i < data_storage.size(); ++i)
    printf("#%d %s %s %s %d\n", i+1, data_storage[i].first_name.c_str(), data_storage[i].second_name.c_str(), data_storage[i].date.c_str(), data_storage[i].payout_sum);
  std::cout << "\n";
}

void data_storage_fill(statement& data, std::vector<statement>& data_storage, bool& is_open){

  std::ifstream size_check ("statement.bin", std::ios::binary | std::ios::ate);

  if (!size_check.is_open()){

    std::cerr << "\n**File open error**\n\n";
    return;

  }
  else
    is_open = true;

  if (size_check.tellg() == 0) {

    std::cerr << "\n**File is empty**\n\n";
    size_check.close();
    return;

  }

  size_check.close();

  std::ifstream storage_fill ("statement.bin", std::ios::binary);
    
  while (true){

    if (!storage_fill.read((char*)&fname_len, sizeof(int))) break;

    storage_fill.read((char*)&sname_len, sizeof(int));

    data.first_name.resize(fname_len);
    data.second_name.resize(sname_len);
      
    storage_fill.read(&data.first_name[0], fname_len);
    storage_fill.read(&data.second_name[0], sname_len);
    storage_fill.read(&data.date[0], date_len);
    storage_fill.read((char*)&data.payout_sum, sizeof(int));

    data_storage.push_back(data);

  }

  storage_fill.close();

}

void data_input (statement& data, bool& input_success){
  std::string data_input;
  while (true){
    std::cout << "\n**Name Subname 00.00.0000 123456789**\n\n";
    std::cout << "Input data: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, data_input);
    std::stringstream data_stream(data_input);
    data_stream >> data.first_name >> data.second_name >> data.date >> data.payout_sum;
    fname_len = data.first_name.length();
    sname_len = data.second_name.length();

    if (data_stream.fail() || data.date.length() < date_len){
      std::cerr << "\n**Input error**\n\n";
      input_success = false;
      return;
    }
    
    break;
  }
}

int main() {

  statement data;
  std::vector<statement> data_storage;
  std::string cmd;

  bool input_success;
  bool is_open = false;

  data_storage_fill(data, data_storage, is_open);

  if (is_open)
    while (true){
      input_success = true;
      fname_len = 0;
      sname_len = 0;

      std::cout << "Input command (add/list): ";
      std::cin >> cmd;

      if (cmd == "add") {
        data_input(data, input_success);
        if (!input_success) continue;
      }

      else if (cmd == "list"){\
        data_output(data_storage);
        continue;
      }

      else {
        
        std::cerr << "\n**Unknown command**\n\n";
        continue;

      }

      if(data_valid(data)){
        data_write(data, data_storage);
        std::cout << "\n**Success write**\n\n";

      } else std::cerr << "\n**ERROR**\n\n";

    }

}
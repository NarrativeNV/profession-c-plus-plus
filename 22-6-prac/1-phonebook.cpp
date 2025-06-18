#include <iostream>
#include <map>
#include <string>

struct note {

  std::string subname;
  std::string p_number;

};

bool request_validate (std::string& request, note& note_form){

  std::string number_part;
  std::string subname_part;
  int start_pos = 0;

  while (start_pos < request.length() && request[start_pos] == ' ')
    ++start_pos;

  while (start_pos < request.length() && request[start_pos] != ' '){
    number_part += request[start_pos];
    ++start_pos;
  }

  if (number_part.find_first_not_of("0123456789-") == std::string::npos)
    note_form.p_number = number_part;
  else
    subname_part = number_part;

  while (start_pos < request.length() && request[start_pos] == ' ')
    ++start_pos;

  while (start_pos < request.length() && request[start_pos] != ' '){
    subname_part += request[start_pos];
    ++start_pos;
  }


  if (!subname_part.empty()){
    if (subname_part.find_first_of("0123456789-") != std::string::npos){
      std::cerr << "\n**Incorrect request**\n\n";
      return false;
    } 

    if (subname_part[0] < 'A' || subname_part[0] > 'Z'){
      std::cerr << "\n**The subname must begin with a capital letter**\n\n";
      return false;
    }

    for (int i = 1; i < subname_part.length(); ++i){

      if (subname_part[i] < 'a' || subname_part[i] > 'z'){
        std::cerr << "\n**Enter the correct Subname**\n\n";
          return false;
      }

    }

    note_form.subname = subname_part;
  }

  return true;

}

bool request_forming (std::string& request, note& note_form){

  std::cout << "Input request: ";
  getline (std::cin, request);

  if (request_validate(request, note_form)) 
    return true;

  return false;

}

int main (){

  std::map<std::string, std::string> num_sub;
  std::multimap<std::string, std::string> sub_num;
  std::string request;


  while(true){

    note note_form;

    while(!request_forming(request, note_form));

    if (!note_form.p_number.empty() && !note_form.subname.empty()){

      auto match_ns = num_sub.find(note_form.p_number);

      if (match_ns == num_sub.end()){

        num_sub.insert(std::make_pair(note_form.p_number, note_form.subname));
        sub_num.insert(std::make_pair(note_form.subname, note_form.p_number));
        std::cout << "\n**Succesfull added**\n\n";

      }

      else 
        std::cerr << "\n**The number already exists**\n\n";

    }

    if (!note_form.p_number.empty() && note_form.subname.empty()) {

      std::map<std::string, std::string>::iterator owner = num_sub.find(note_form.p_number);
      if (owner == num_sub.end())
        std::cerr << "\n**NOT FOUND**\n\n";
      else 
        std::cout << "\n" << owner->first << " -> " << owner->second << "\n\n";

  }

    if (note_form.p_number.empty() && !note_form.subname.empty()){

      std::cout << std::endl;
      bool found = false;
      // std::pair<std::multimap<std::string, std::string>::iterator, 
      // std::multimap<std::string, std::string>::iterator> range = sub_num.equal_range(subname);
      auto mm_range = sub_num.equal_range(note_form.subname);

      if (mm_range.first != mm_range.second)
        for (std::multimap<std::string, std::string>::iterator it = mm_range.first; it != mm_range.second; ++it)
            std::cout << it->first << " -> " << it->second << "\n";      
      else
        std::cerr << "**NOT FOUND**\n";    

      std::cout << std::endl;

    }
  
  }

}

#include <iostream>
#include <map>
#include <string>

bool request_validate (std::string& request){

  if (request[0] < 'A' || request[0] > 'Z'){
    std::cerr << "\n**The subname must begin with a capital letter**\n\n";
    return false;
  }

  for (int i = 1; i < request.length(); ++i){
    if (request[i] < 'a' || request[i] > 'z'){
      std::cerr << "\n**Enter the correct Subname**\n\n";
      return false;
    }
  }

  return true;
}

void request_forming (std::string& request){

  std::cout << "<- ";
  getline(std::cin, request);

  int sep_pos = request.find(' ');

  if (sep_pos != std::string::npos)
    request.resize(sep_pos);

}

int main(){

  std::multimap<std::string, char> reception;
  std::string request;

  while (true){

    while (true){
      request_forming(request);
      if (request_validate(request))
        break;
    }


    if (request == "Next"){

      if (reception.begin() != reception.end()){
        auto it = reception.begin();
        std::cout << "-> " << it->first << std::endl;
        reception.erase(it);
      }
      else 
        std::cerr << "\n**List is empty**\n\n";

    }
    else
      reception.insert({request, '.'});

  }

}
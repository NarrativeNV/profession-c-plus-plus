#include <iostream>
#include <map>
#include <string>

struct anagrams_w{
  std::string f_word;
  std::string s_word;
};

void alphabet_fill (std::map<std::string, std::string>& russian, std::map<std::string, char>& low_key){

  std::string rus_uppercase[33] = {
    "А","Б","В","Г","Д","Е","Ж","З","И","Й","К","Л","М",
    "Н","О","П","Р","С","Т","У","Ф","Х","Ц","Ч","Ш","Щ",
    "Ъ","Ы","Ь","Э","Ю","Я","Ё"
  };

  std::string rus_lowercase[33] = {
    "а","б","в","г","д","е","ж","з","и","й","к","л","м",
    "н","о","п","р","с","т","у","ф","х","ц","ч","ш","щ",
    "ъ","ы","ь","э","ю","я","ё"
  };

  for (int i = 0; i < 33; ++i){
    russian[rus_uppercase[i]] = rus_lowercase[i];
    low_key[rus_lowercase[i]] = '.'; 
  }

}

bool request_validate (const std::string& word, std::map<std::string, std::string>& rus, std::map<std::string, char>& low_key){

  std::string rus_char;

  for (int i = 0; i < word.length(); i += 2) {
    rus_char = word.substr(i, 2);
    if (rus.find(rus_char) == rus.end() && low_key.find(rus_char) == low_key.end())
      return false;
}

  return true;

}

std::string request_forming (const std::string& count){

  std::string request;
  std::string request_buff;
  std::cout << "Input " << count << " russian word: ";
  getline(std::cin, request_buff);

  int sep_pos = request_buff.find(' ');

  if (sep_pos == std::string::npos)
    request = request_buff;
  else
    request = request_buff.substr(0, sep_pos);

  return request;

}

bool ana_map_search(anagrams_w& ana_req, std::multimap<std::string, std::string>& anagram_search){

  std::pair<std::multimap<std::string, std::string>::iterator, std::multimap<std::string, std::string>::iterator> ana_pair = anagram_search.equal_range(ana_req.f_word);

  for (auto it = ana_pair.first; it != ana_pair.second; ++it)
    if (it->second == ana_req.s_word)
      return true;
  
  return false;

}

void symbol_count (const std::string& word, std::map<std::string, int>& symbols_amount){

  for (int i = 0; i < word.length(); i+=2)
    ++symbols_amount[word.substr(i, 2)];

}

void to_lowercase(std::string& word, std::map<std::string, std::string>& rus) {
  for (int i = 0; i < word.length(); i += 2) {

    std::string letter = word.substr(i, 2);

    std::map<std::string, std::string>::iterator it = rus.find(letter);
    if (it != rus.end())
      word.replace(i, 2, it->second);

  }
}

bool ana_check(anagrams_w& ana_req, std::map<std::string, std::string>& rus){

  std::map<std::string, int> f_symbol_amount;
  std::map<std::string, int> s_symbol_amount;

  symbol_count(ana_req.f_word, f_symbol_amount);
  symbol_count(ana_req.s_word, s_symbol_amount);

  if (f_symbol_amount.size() != s_symbol_amount.size())
    return false;

  auto f_it = f_symbol_amount.begin();
  auto s_it = s_symbol_amount.begin();

  for (; f_it != f_symbol_amount.end(); ++f_it, ++s_it)
    if (f_it->first != s_it->first || f_it->second != s_it->second)
      return false;

  return true;
}

int main(){

  std::multimap<std::string, std::string> anagrams;
  std::map<std::string, std::string> russian; 
  std::map<std::string, char> low_key;
  alphabet_fill(russian, low_key);

  while(true){

    anagrams_w ana_req;
    ana_req.f_word = request_forming("first");
    if (ana_req.f_word.empty()) {
      std::cerr << "\n**Empty input**\n\n";
      continue;
    }

    ana_req.s_word = request_forming("second");
    if (ana_req.s_word.empty()) {
      std::cerr << "\n**Empty input**\n\n";
      continue;
    }

    if (request_validate(ana_req.f_word, russian, low_key) && request_validate(ana_req.s_word, russian, low_key)){

      to_lowercase(ana_req.f_word, russian);
      to_lowercase(ana_req.s_word, russian);

      if(ana_req.f_word > ana_req.s_word)
          std::swap(ana_req.f_word, ana_req.s_word);
      
      if (anagrams.begin() != anagrams.end())
        if (ana_map_search(ana_req, anagrams)){
          std::cout << "\n**Words are anagram**\n\n";
          continue;
        }

      if(ana_check(ana_req, russian)){
        anagrams.insert({ana_req.f_word, ana_req.s_word});
        std::cout << "\n**Words are anagram**\n\n";
      }
      else
        std::cerr << "\n**Words are not anagram**\n\n";

    }
    else {
      std::cerr << "\n**Invalid word**\n\n";
      continue;
    }

  }

}
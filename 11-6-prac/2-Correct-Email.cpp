#include <iostream>
using namespace std;

string get_left_adress_part(string leftAdress){
    string leftInit;
    for (int i = 0; leftAdress[i] != '@'; i++){
        leftInit += leftAdress[i];
    }
    return leftInit;
}

string get_right_adress_part(string rightAdress){
    string rightInit;
    int separatePos;
    int rightCount;
    for (int i = 0; rightAdress[i] != '@'; i++){
        separatePos = i;
    }
    separatePos += 2;
    rightCount = rightAdress.length() - separatePos;
    for (int i = separatePos; i < rightAdress.length(); i++){
        rightInit += rightAdress[i];
    }
    return rightInit;
}

bool adress_validate(string adress, char* allowedSymbols, int arrSize){
    if (adress.length() > 64 || adress.empty() ||
        adress.length() > 63 || adress.empty()) return false;
    if (adress.find("..") != std::string::npos || adress.find("..") != std::string::npos) return false;
    if (adress.front() == '.' || adress.back() == '.' ||
        adress.front() == '@' || adress.back() == '@') return false;

    for (int i = 0; i < adress.length(); i++){
        if ((adress[i] < 'a' || adress[i] > 'z') && 
            (adress[i] < 'A' || adress[i] > 'Z') && 
            (adress[i] < '0' || adress[i] > '9')){
            int allowMark = 0;
            for (int j = 0; j < arrSize; j++){
                if (adress[i] == allowedSymbols[j]) allowMark++;
                if (allowMark == 1) break;
            }
                if (allowMark == 0) return false;
            }
    }
    return true;
}

int main(){
    string email;
    const int leftSize = 20;
    const int rightSize = 2;
    char allowedSymbols[] = {'.', '-', '!', '#', '$','%', '&', '`', '*', '+', '/', '=', '?', '^', '_', '\'', '{', '}', '|', '~'};
    while (true){
        cin.clear();
        cout << "Input email adress: ";
        cin >> email;
        if (adress_validate(get_left_adress_part(email), allowedSymbols, leftSize) && adress_validate(get_right_adress_part(email), allowedSymbols, rightSize)) cout << "Yes\n\n";
        else cout << "No\n\n";
    }
}

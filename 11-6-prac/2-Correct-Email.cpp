#include <iostream>
using namespace std;
//char allowedSymbols[] = {'!', '#', '$','%', '&', '`', '*', '+', '-', '/', '=', '?', '^', '_', '\'', '{', '}', '|', '~'};

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
    if (adress.length() > 64) return false;
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
            if (adress[i] == '.' && adress[i+1] == '.') return false;
    }
    return true;
}

int main(){
    string email;
    const int leftSize = 19;
    const int rightSize = 2;
    char allowedLeftSymbols[] = {'!', '.', '#', '$','%', '&', '`', '*', '+', '-', '/', '=', '?', '^', '_', '\'', '{', '}', '|', '~'};
    char allowedRightSymbols[] = {'.', '-'};
    while (true){
        cin.clear();
        cout << "Input email adress: ";
        cin >> email;
        if (adress_validate(get_left_adress_part(email), allowedLeftSymbols, leftSize) && adress_validate(get_right_adress_part(email), allowedRightSymbols, rightSize)) cout << "Yes\n\n";
        else cout << "No\n\n";
    }
}

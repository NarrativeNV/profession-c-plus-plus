#include <iostream>
using namespace std;
//char allowedSymbols[] = {'!', '#', '$','%', '&', '`', '*', '+', '-', '/', '=', '?', '^', '_', '\'', '{', '}', '|', '~'};

//2. Correct-Email
bool is_email(string adress){
    int count = 0;
    if (adress[0] == '.' || adress[0] == '@' || adress[adress.length() - 1] == '.') return false;
    for (int i = 0; i < adress.length(); i++){
        if (adress[i] == '@') {
            count++;
            if (adress[i-1] == ' ' || adress[i-1] == '.' || 
                adress[i+1] == '.' || adress[i+1] == ' ') return false;
            }
    }
    if (count == 1) return true;
    return false;
}

bool leftPart_is_correct(string leftAdress){
    char allowedSymbols[] = {'!', '.', '#', '$','%', '&', '`', '*', '+', '-', '/', '=', '?', '^', '_', '\'', '{', '}', '|', '~',};
    string leftInit;
    for (int i = 0; leftAdress[i] != '@'; i++){
        if ((leftAdress[i] < 'a' || leftAdress[i] > 'z') && 
            (leftAdress[i] < 'A' || leftAdress[i] > 'Z') && 
            (leftAdress[i] < '0' || leftAdress[i] > '9')){
            int allowMark = 0;
            for (int j = 0; j < 20; j++){
                if (leftAdress[i] == allowedSymbols[j]) allowMark++;
                if (allowMark == 1) break;
            }
            if (allowMark == 0) return false;
        }
        if (leftAdress[i] == '.' && leftAdress[i+1] == '.') return false;
        if (i > 64) return false;
        leftInit += leftAdress[i];
    }
    return true;
}

bool rightPart_is_correct(string rightAdress){
    char allowedSymbols[] = {'.', '-',};
    string rightInit;
    int separatePos;
    int rightCount;
    for (int i = 0; rightAdress[i] != '@'; i++){
        separatePos = i;
    }
    separatePos += 2;
    rightCount = rightAdress.length() - separatePos;
    if (rightCount > 63) return false;
    for (int i = separatePos; i < rightAdress.length(); i++){
        if ((rightAdress[i] < 'a' || rightAdress[i] > 'z') && 
            (rightAdress[i] < 'A' || rightAdress[i] > 'Z') && 
            (rightAdress[i] < '0' || rightAdress[i] > '9')){
            int allowMark = 0;
            for (int j = 0; j < 2; j++){
                if (rightAdress[i] == allowedSymbols[j]) allowMark++;
                if (allowMark == 1) break;
            }
            if (allowMark == 0) return false;
        }

        if (rightAdress[i] == '.' && rightAdress[i+1] == '.') return false;
        rightInit += rightAdress[i];
    }
    return true;
}

int main(){
    string email;
    while (true){
        cin.clear();
        cout << "Input email adress: ";
        cin >> email;
        bool email_validation = is_email(email);
        bool leftPart_validation = leftPart_is_correct(email);
        bool rightPart_validation = rightPart_is_correct(email);

        if (email_validation && leftPart_validation && rightPart_validation) cout << "Yes" << "\n\n";
        else cout << "No" << "\n\n";
    }
}
#include <iostream>
using namespace std;

//1. Ceaser Encrypt
string encryptCaesar(string text, int encryptStep){
    string encrypted;
    for (int i = 0; i < text.length(); i++){
        if (text[i] >= 'a' && text[i] <= 'z'){
            text[i] -= 'a';
            text[i] += encryptStep;
            text[i] %= 26;
            text[i] += 'a';
        }
        else if (text[i] >= 'A' && text[i] <= 'Z'){
            text[i] -= 'A';
            text[i] += encryptStep;
            text[i] %= 26;
            text[i] += 'A';
        }
        encrypted += text[i];
    }
    return encrypted;
}

int main(){
    string text;
    int encryptStep;

    cout << "Input text to encrypt: ";
    getline(cin, text);
    cout << "Input encrypt step: ";
    cin >> encryptStep;

    cout << encryptCaesar(text, encryptStep);
}
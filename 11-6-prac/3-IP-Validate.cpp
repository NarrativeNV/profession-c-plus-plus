#include <iostream>
using namespace std;

string get_adress_part(string adressPart, int startPos){
      string octet;
    int dotCounter = 0;
    for (int i = 0; i < adressPart.length(); i++){
        if (adressPart[i] == '.') {
            dotCounter++;
            i++;
        }
        if (dotCounter > startPos) ;
        else if (dotCounter > startPos - 1 ) {
            octet += adressPart[i];
        }
    }
    return octet;
}

bool adress_validate (string octet){
    int octetDigit = 0;

    for (int i = 0; i < octet.length(); i++){
        if (octet[i] < '0' || octet[i] > '9') return false;
        else if (octet[i] == '.' && octet[i+1] == '.') return false;
    }
    if (octet.length() > 3) return false;
    else if (octet.length() == 3){
        if ((octet[0] == '0' && octet[1] == '0')
        || (octet[0] == '0' && octet[1] != '0')) return false;
        octetDigit += 100 * (octet[0] - '0');
        octetDigit += 10 * (octet[1] - '0');
        octetDigit += octet[2] - '0';
    }
    else if (octet.length() == 2){
        if ((octet[0] == '0' && octet[1] == '0')
        || (octet[0] == '0' && octet[1] != '0')) return false;
        octetDigit += 10 * (octet[0] - '0');
        octetDigit += octet[1] - '0';
    }
    else if (octet.length() == 1){
        octetDigit += octet[0] - '0';
    }
    else return false;

    if (octetDigit >= 0 && octetDigit <= 255) return true;

    return false;
}

int main(){
    string ip;
    bool validation = true;
    while (true){
        cout << "Input IPV4 adress: ";
        cin >> ip;
        for (int i = 0; i < 4; i++){
            validation = adress_validate(get_adress_part(ip, i));
            if (!validation) {
                cout << "Invalid\n\n";
                break;
            }
        }
        if (ip[ip.length() - 1] == '.') {
            validation = false;
            cout << "Invalid\n\n";
        }
        if (validation) cout << "Valid\n\n";   
    }
}
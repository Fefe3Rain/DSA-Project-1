#include <iostream>

#include <conio.h> // for _getch()

using namespace std;

int v = 120;

string getpincode() {

    string pincode;

    char ch;
 
    cout << "Enter pincode (only numbers allowed): ";

    while ((ch = _getch()) != '\r') { // Enter key corresponds to '\r' in Windows

        if (ch >= '0' && ch <= '9') { // Only allow numeric characters

            pincode += ch;

            cout << '*'; // Print * for each valid input

        } else if (ch == '\b') { // Handle backspace

            if (!pincode.empty()) {

                cout << "\b \b"; // Erase the last '*'

                pincode.pop_back();

            }

        } else {

            // Ignore non-numeric characters and don't output anything

        }

    }

    cout << endl;
 
    return pincode;

}

string encrypt(string pin);

string decrypt(string pin);

int main() {

    string pincode = getpincode();
 
    cout << "pincode entered: " << pincode << endl;

    pincode=encrypt(pincode);

    cout << "Encrypted pincode entered: " << pincode << endl;

    pincode=decrypt(pincode);

    cout << "Decrypted pincode entered: " << pincode << endl;
 
    return 0;

}

string encrypt(string pin){

for (int i = 0;i<pin.size();i++)

    pin[i]=pin[i] + v;

return pin;

}

string decrypt(string pin){

for (int i = 0;i<pin.size();i++)

    pin[i]=pin[i]-v;

return pin;

}
#define byte win_byte_override
#include "Registration.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <cstdlib>

#undef byte

using namespace std;

int main(){
    Information x;
    Register Acc;
    Acc.Load();
    while(true){
        system("cls");
        cout << "Please insert a card.\n";
        ifstream fp("E:\\pin.code.txt");
        if(fp)
            break;
    }
    ifstream fp("E:\\pin.code.txt");
    string line;
    while (getline(fp, line)){
        if(line.empty()){
            while (true) {
                do {
                    system("cls");
                    cout << "Welcome to the Registration Page!\n";
                    cout << "Please fill in your information.\n";
                    cout << "Full Name (FN LN): ";
                    getline(cin, x.Name);
                    cout << "Birthday (MM/DD/YYYY): ";
                    getline(cin, x.Birthday);
                    cout << "Contact Number (09XXXXXXXXX): ";
                    getline(cin, x.Con_Number);
                } while (Acc.AntiDup(x.Name, x.Birthday, x.Con_Number));

                x.Acc_Number = Acc.Acc_No_Generator(x.Name, x.Birthday, x.Con_Number);
                cout << "Generating Account Number...\n";
                Sleep(1500);
                cout << "Your account number is: " << x.Acc_Number << endl;
                system("pause");

                string confirm;
                do {
                    cout << "Please enter a 6 digit Pin Code: ";
                    x.Pin_code = Acc.Get_Pin_Code();
                    cout << "Please confirm your Pin Code: ";
                    confirm = Acc.Get_Pin_Code();
                } while (confirm != x.Pin_code);

                cout << "Pin code is now saved and encrypted: " << x.Pin_code << endl;
                system("pause");

                do {
                    cout << "Please Deposit an initial amount of balance (5000.00 min.): ";
                    cin >> x.Balance;
                } while (x.Balance < 5000.00);

                cout << "Processing...";
                Sleep(1500);
                cout << "\nCongratulations! Account number: " << x.Acc_Number << " is successfully added.\n";
                system("pause");

                Acc.Add(x);
                Acc.Save();
                break;
            }
        } else {

        }
    }
    return 0;
}
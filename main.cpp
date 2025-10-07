#include "Registration.h"
#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdlib>
#include <string>
#include <cmath>
#include <conio.h>

using namespace std;

int main(){
    ifstream fp;
    Information x;
    Register Acc;
    Transact Trans;
    Node* p;
    Acc.Load();
    while (true){
        while(true){
            system("cls");
            cout << "Please insert a card.\n";
            fp.open("D:\\pin.code.txt");
            if (fp) break;
        }
        string line;
        if (!getline(fp, line)){
            system("cls");
            system("pause");
            do {
                system("cls");
                cout << "Welcome to the Registration Page!\n";
                cout << "Please fill in your information.\n";
                cout << "Full Name (FN LN): ";
                char c;
                while ((c = getch()) != '\r') {
                    if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == ' ') {
                        x.Name += c;
                        cout << c;
                    } else if (c == '\b') {
                        if (!x.Name.empty()) {
                            cout << "\b \b";
                            x.Name.pop_back();
                        }
                    }
                }
                cout << endl;
                cout << "Birthday (MM/DD/YYYY): ";
                char b;
                while ((b = getch()) != '\r') {
                    if (b >= '0' && b <= '9' || b == '/') {
                        x.Birthday += b;
                        cout << b;
                    } else if (b == '\b') {
                        if (!x.Birthday.empty()) {
                            cout << "\b \b";
                            x.Birthday.pop_back();
                        }
                    }
                }
                cout << endl;
                cout << "Contact Number (09XXXXXXXXX): ";
                char n;
                while ((n = getch()) != '\r') {
                    if (n >= '0' && n <= '9') {
                        x.Con_Number += n;
                        cout << n;
                    } else if (n == '\b') {
                        if (!x.Con_Number.empty()) {
                            cout << "\b \b";
                            x.Con_Number.pop_back();
                        }
                    }
                }
                cout << endl;
            } while (Acc.AntiDup(x.Name, x.Birthday, x.Con_Number));

            x.Acc_Number = Acc.Acc_No_Generator(x.Name, x.Birthday, x.Con_Number);
            cout << "Generating Account Number...\n";
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
            } while (x.Balance < 5000.00 || fmod(x.Balance, 100.0) != 0.0);

            cout << "Processing...";

            Acc.Add(x);
            Acc.Save();

            ofstream fp("D:\\pin.code.txt");
            fp << x.Acc_Number << "," << x.Pin_code << endl;

            cout << "\nCongratulations! Account number: " << x.Acc_Number << " is successfully added.\n";
            system("pause");
        } else {
            system("cls");
            cout << "Welocme to Transaction Page!\n";
            system("pause");
            Trans.load();
            if(Trans.Enter_Pin()){
                do {
                    cout << "Please confirm your PIN for Security Purposes: ";
                    string PIN = Trans.Get_Pin_Code();
                    p = Trans.Locate(PIN);
                    if (p == NULL){
                        cout << "You entered the wrong pin\n";
                        system("pause");
                    } else {
                        cout << "Welcome " << p->Data.Name << "!\n";
                        cout << "Your account number is: " << p->Data.Acc_Number << endl;
                        system("pause");
                        break;
                    }
                } while (p == NULL);
                while(true){
                    switch(trans_menu()){
                        case 1:
                            Trans.Balance_Inq(p);
                            break;
                        case 2:
                            Trans.Withdraw(p);
                            break;
                        case 3:
                            Trans.Deposit(p);
                            break;
                        case 4:
                            Trans.Fund_Trans(p);
                            break;
                        case 5:
                            Trans.Change_PIN(p);
                            Acc.Save();
                            break;
                        case 6:
                            system("cls");
                            cout << "Ejecting ATM...\nThank you for using our services!\n";
                            system("pause");
                            Trans.save(p);
                            exit(0);
                        default:
                            system("cls");
                            cout << "Invalid Input, Please try again,\n";
                            system("pause");
                    }
                }
            }
        }
        fp.close();
    }
    return 0;
}
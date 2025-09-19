#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int mainmenu();

int main(){
    while(true){
        system("cls");
        cout << "Please insert a card.\n";
        ifstream fp("E:\\pin.code.txt");
        if(fp)
            break;
    }
    while(true){
        switch(mainmenu()){
            case 1:
                break;
            case 2:
                break;
            case 3:
                system("cls");
                cout << "Thank you for using our services. Ejecting card...\n";
                exit(0);
            default:
                system("cls");
                cout << "Invalid input! Please try again!\n";
                system("pause");
        }
    }
    return 0;
}

int mainmenu(){
    int op;
    system("cls");
    cout << "WELCOME TO BANK!\n";
    cout << "AVAIL SERVICES:\n";
    cout << "1.) Register (For new clients).\n";
    cout << "2.) Transaction (Services for clients).\n";
    cout << "3.) Eject ATM Card.\n";
    cout << "Select an option(1 - 2): ";
    cin >> op;
    return op;
}
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int mainmenu();

int main(){
    ofstream fp("");
    while(!fp){
        system("cls");
        cout << "Please insert a card.\n";
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
                return;
        }
    }
    return 0;
}

int mainmenu(){
    int op;
    system("cls");
    cout << "WELCOME TO BANK!\n";
    cout << "AVAIL SERVICES:\n";
    cout << "1.) Register.\n";
    cout << "2.) Transaction.\n";
    cout << "Select an option(1 - 2): ";
    cin >> op;
    return op;
}
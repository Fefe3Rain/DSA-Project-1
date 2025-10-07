#include "Transaction.h"
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <sstream>

Transact::Transact() : head(NULL), tail(NULL) {}

Transact::~Transact() {
    Node *post, *temp;
    post = head;
    while (post != NULL){
        Node *temp = post;
        post = post->next;
        delete(temp);
    }
    head = NULL;
    tail = NULL;
}

string Transact::encrypt(string pin){
    for (int i = 0; i < pin.size(); i++)
        pin[i] = pin[i] * v + v;
    return pin;
}
string Transact::decrypt(string pin){
    for (int i = 0; i < pin.size(); i++)
        pin[i] = pin[i] / v - v;
    return pin;
}
string Transact::Get_Pin_Code(){
    string pin;
    char c;

    while((c = getch()) != '\r'){
        if(c >= '0' && c <= '9'){
            pin += c;
            cout << "*";
        } else if(c == '\b'){
            if (!pin.empty()){
                cout << "\b \b";
                pin.pop_back();
            }
        } else {
            // Ignore non numeric characters and output nothing
        }
    }
    cout << endl;
    pin = encrypt(pin);
    return pin;
}
Node* Transact::Locate(string PIN){
    Node* p = head;
    while(p != NULL && PIN != p->Data.Pin_code){
        p = p->next;
    }
    return p;
}
bool Transact::Enter_Pin(){
    int i = 3;
    do {
        system("cls");
        cout << "Please Enter your Pin code (You only have " << i << " attempts): ";
        string enterpin = Get_Pin_Code();
        Node *p = Locate(enterpin);
        if (p == NULL){
            cout << "The pin you entered is not found!\n";
            cout << "Please try again.\n";
            system("pause");
            i--;
        } else {
            return true;
        }
    } while (i > 0);
    if (i == 0){
        system("cls");
        cout << "Sorry you've reached the maximum number of attempts to input your correct pin\n";
        cout << "Please try again later...\n";
        cout << "Ejecting ATM...";
        exit(0);
    }
    return false;
}
void Transact::Balance_Inq(Node* p){
    system("cls");
    cout << "Balance Inquiry.\n";
    cout << "Name: " << p->Data.Name << "\tAccount Number: " << p->Data.Acc_Number << endl;
    cout << "Your current balance: " << p->Data.Balance << endl;
    system("pause");
}
void Transact::Withdraw(Node* p){
    string amt;
    double amnt;
    char c;

    do{
        system("cls");
        cout << "Withdraw\n";
        cout << "Enter an amount: ";
        while((c = getch()) != '\r'){
            if(c >= '0' && c <= '9'){
                amt += c;
                cout << c;
            } else if(c == '\b'){
                if (!amt.empty()){
                    cout << "\b \b";
                    amt.pop_back();
                }
            } else {
                // Ignore non numeric characters and output nothing
            }
        }
        cout << endl;
        amnt = stof(amt);
        if (amnt > p->Data.Balance){
            cout << "Insufficient funds.\n";
            system("pause");
        } else if (fmod(amnt, 100.0) != 0.0) {
            cout << "Exact amount only\n";
            system("pause");
        } else {
            cout << "================RECEIPT================\n";
            cout << "Account Number:   " << p->Data.Acc_Number << endl;
            cout << "Name:             " << p->Data.Name << endl;
            cout << "Contact Number:   " << p->Data.Con_Number << endl;
            cout << "Previous Balance: " << p->Data.Balance << endl;
            cout << "Amount Withdrawn: " << amnt << endl;
            p->Data.Balance -= amnt;
            cout << "Remaining Balance:" << p->Data.Balance << endl;
            amnt = 0;
            system("pause");
            save(p);
        }
    } while (amnt != 0);
}
void Transact::Deposit(Node* p){
    string amt;
    double amnt;
    char c;

    do{
        system("cls");
        cout << "Deposit\n";
        cout << "Enter an amount: ";
        while((c = getch()) != '\r'){
            if(c >= '0' && c <= '9'){
                amt += c;
                cout << c;
            } else if(c == '\b'){
                if (!amt.empty()){
                    cout << "\b \b";
                    amt.pop_back();
                }
            } else {
                // Ignore non numeric characters and output nothing
            }
        }
        cout << endl;
        amnt = stof(amt);
        if (fmod(amnt, 100.0) != 0.0) {
            cout << "Exact amount only\n";
            system("pause");
        } else {
            cout << "================RECEIPT================\n";
            cout << "Account Number:   " << p->Data.Acc_Number << endl;
            cout << "Name:             " << p->Data.Name << endl;
            cout << "Contact Number:   " << p->Data.Con_Number << endl;
            cout << "Previous Balance: " << p->Data.Balance << endl;
            cout << "Deposited Amount: " << amnt << endl;
            p->Data.Balance += amnt;
            cout << "Current Balance:  " << p->Data.Balance << endl;
            amnt = 0;
            system("pause");
            save(p);
        }
    } while (amnt != 0);
}
void Transact::Fund_Trans(Node* p){
    Node* r = head;
    string amt;
    double amnt;
    string receiver;
    char rc;
    char c;

    do{
        system("cls");
        cout << "Fund Transfer\n";
        cout << "Enter the Account number that you want to transfer funds: ";
        while((rc = getch()) != '\r'){
            if(rc >= '0' && c <= '9'){
                receiver += rc;
                cout << rc;
            } else if(rc == '\b'){
                if (!amt.empty()){
                    cout << "\b \b";
                    amt.pop_back();
                }
            } else {
                // Ignore non numeric characters and output nothing
            }
        }
        cout << endl;
        while(r != NULL && receiver != r->Data.Acc_Number){
            r = r->next;
        }
        cout << "Enter an amount: ";
        while((c = getch()) != '\r'){
            if(c >= '0' && c <= '9'){
                amt += c;
                cout << c;
            } else if(c == '\b'){
                if (!amt.empty()){
                    cout << "\b \b";
                    amt.pop_back();
                }
            } else {
                // Ignore non numeric characters and output nothing
            }
        }
        cout << endl;
        amnt = stof(amt);
        if (amnt > p->Data.Balance){
            cout << "Insufficient funds.\n";
            system("pause");
        } else if (fmod(amnt, 100.0) != 0.0) {
            cout << "Exact amount only\n";
            system("pause");
        } else {
            cout << "================RECEIPT================\n";
            cout << "Account Number:   " << p->Data.Acc_Number << endl;
            cout << "Name:             " << p->Data.Name << endl;
            cout << "Contact Number:   " << p->Data.Con_Number << endl;
            cout << "Previous Balance: " << p->Data.Balance << endl;
            cout << "Deducted Amount:  " << amnt << endl;
            p->Data.Balance -= amnt;
            cout << "Remaining Balance:" << p->Data.Balance << endl;
            cout << "Account Number:   " << r->Data.Acc_Number << endl;
            cout << "Name:             " << r->Data.Name << endl;
            cout << "Contact Number:   " << r->Data.Con_Number << endl;
            cout << "Previous Balance: " << r->Data.Balance << endl;
            cout << "Deposited Amount: " << amnt << endl;
            r->Data.Balance += amnt;
            cout << "Remaining Balance:" << r->Data.Balance << endl;
            amnt = 0;
            system("pause");
            save(p);
        }
    } while (amnt != 0);
}
void Transact::Change_PIN(Node* p){
    system("cls");
    cout << "Change pin\n";
    cout << "Enter a new Pin.\n";
    p->Data.Pin_code = Get_Pin_Code();
    save(p);
    cout << "Your pin code has been successfully changed!\n";
    system("pause");
}
void Transact::Add(Information x){
    Node *newNode;
    newNode = new Node(x);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}
void Transact::save(Node* p) {
    ofstream fp(FILENAME);
    ofstream atm("D:\\pin.code.txt");
    Node *post = head, *s = p;
    if (!fp && !atm) {
        cout << "Error opening file for saving!\n";
        system("pause");
        return;
    }
    while (post != NULL) {
        fp << post->Data.Acc_Number << "," << post->Data.Name <<
        "," << post->Data.Birthday << "," << post->Data.Con_Number << 
        "," << post->Data.Pin_code << "," << post->Data.Balance << endl;
        post = post->next;
    }
    fp.close();
    atm << s->Data.Acc_Number << "," << s->Data.Pin_code;
    atm.close();
}

void Transact::load() {
    Information d;
    ifstream fp(FILENAME);
    if (!fp) {
        cout << "No saved records found.\n";
        system("pause");
        return;
    }
    string line;
    while (getline(fp, line)) {
        if (line.empty())
            continue;
        stringstream ss(line);
        string balance;
        getline(ss, d.Acc_Number, ',');
        getline(ss, d.Name, ',');
        getline(ss, d.Birthday, ',');
        getline(ss, d.Con_Number, ',');
        getline(ss, d.Pin_code, ',');
        getline(ss, balance, ',');

        d.Balance = stof(balance);

        decrypt(d.Pin_code);
        Add(d);
    }
    fp.close();
}

int trans_menu(){
    int op;
    system("cls");
    cout << "WELCOME to Transaction Page!\n";
    cout << "Transaction Services:\n";
    cout << "1.) Balance Inquiry\t2.) Withdraw Amount\n";
    cout << "3.) Deposit Amount \t4.) Fund Transfer\n";
    cout << "5.) Change Pin Code\t6.) Eject ATM\n";
    cout << "Please Select an option: ";
    cin >> op;
    return op;
}
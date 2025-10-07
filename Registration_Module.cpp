#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>

using namespace std;

#define FILENAME "Account_Records.txt"
#define v 120

struct Information{
    string Acc_Number, Name, Birthday, Con_Number, Pin_code;
    float Balance;
};
struct Node{
    Information Data;
    struct Node *next;
    struct Node *prev;
    Node(Information x) : Data(x), next(NULL), prev(NULL) {}
};

class Register{
    private:
        Node *head;
        Node *tail;
        string Name_Number(string fullname);
        string Birth_Number(string bday);
        string Last2_Digits(string con_num);
        string encrypt(string pin);
        string decrypt(string pin);
    public:
        Register() : head(NULL), tail(NULL) {}
        ~Register(){
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
        string Acc_No_Generator(string fullname, string bday, string con_num);
        string Get_Pin_Code();
        bool AntiDup(string fullname, string bday, string con_num);
        void Add(Information x);
        void Save();
        void Load();
};

int main(){
    Information x;
    Register Acc;
    Acc.Load();
    while(true){
        do{
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
        do{
            cout << "Please Deposit an initial amount of balance (5000.00 min.): ";
            cin >> x.Balance;
        }while(x.Balance < 5000.00);
        cout << "Processing...";
        cout << "\nCongratulations! Account number: " << x.Acc_Number << " is successfully added to the system." << endl;
        system("pause");
        Acc.Add(x);
        Acc.Save();
        break;
    }
    return 0;
}

string Register::Name_Number(string fullname){
    int count = 0, fn = 0;
    bool firstDone = false;
    for (char c : fullname){
        if (c != ' ')
            count++;
        else{
            fn = count;
            count = 0;
            firstDone = true;
        }
        if (count > 9) 
            count - 1;
    }
    return to_string(count);
}
string Register::Birth_Number(string bday) {
    string birthNum = "";
    if (bday.size() > 4) {
        birthNum += bday[1];
        birthNum += bday[4]; 
    }
    return birthNum;
}
string Register::Last2_Digits(string con_num){
    string last2 = con_num.substr(con_num.length() - 2);
    return last2;  
}
string Register::Acc_No_Generator(string fullname, string bday, string con_num) {
    string fln = Name_Number(fullname);
    string bn = Birth_Number(bday);
    string l2 = Last2_Digits(con_num);

    string acc_no = fln + bn + l2;
    return acc_no;
}
string Register::Get_Pin_Code(){
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
string Register::encrypt(string pin){
    for (int i = 0; i < pin.size(); i++)
        pin[i] = pin[i] * v + v;
    return pin;
}
string Register::decrypt(string pin){
    for (int i = 0; i < pin.size(); i++)
        pin[i] = pin[i] / v - v;
    return pin;
}
bool Register::AntiDup(string fullname, string bday, string con_num){
    Node *post = head;
    while (post != NULL){
        if (post->Data.Name == fullname && post->Data.Birthday == bday && post->Data.Con_Number == con_num){
            cout << "Account already exists! Delete this account/Create a new one!\n";
            system("pause");
            return true;
        }
        post = post->next;
    }
    return false;
}
void Register::Add(Information x){
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
void Register::Save() {
    ofstream fp(FILENAME);
    Node *post = head;
    if (!fp) {
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
}
void Register::Load() {
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
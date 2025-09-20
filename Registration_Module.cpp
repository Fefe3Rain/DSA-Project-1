#include <iostream>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <string>
#include <conio.h>

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
        string Last4_Digits(string con_num);
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
        void Add(Information x);
        void Save();
        void Load();
};

int main(){
    Information x;
    Register Acc;
    Acc.Load();
    while(true){
        system("cls");
        cout << "Welcome to the Registration Page!\n";
        cout << "Please fill in your information.\n";
        cout << "Full Name (FN LN): ";
        cin.ignore();
        getline(cin, x.Name);
        cout << "Birthday (MM/DD/YYYY): ";
        getline(cin, x.Birthday);
        cout << "Contact Number (09XXXXXXXXX): ";
        getline(cin, x.Con_Number);
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
        cout << "Please Deposit an initial amount of balance (5000.00 min.): ";
        cin >> x.Balance;
        cout << "Processing...";
        Sleep(1500);
        cout << "\nCongratulations! Account number: " << x.Acc_Number << " is successfully added to the system." << endl;
        system("pause");
        Acc.Add(x);
        Acc.Save();
        break;
    }
    return 0;
}

string Register::Name_Number(string fullname){
    int count = 0, fn = 0, ln = 0;
    bool firstDone = false;
    for (char c : fullname){
        if (c != ' ')
            count++;
        else {
            fn = count;
            count = 0;
            firstDone = true;
        }
    }
    ln = count;
    return to_string(fn) + to_string(ln);
}
string Register::Birth_Number(string bday){
    string birthNum = "";
    for (char c : bday)
        if (c != '/')
            birthNum += c;
    return birthNum;
}
string Register::Last4_Digits(string con_num){
    string last4 = con_num.substr(con_num.length() - 4);
    return last4;  
}
string Register::Acc_No_Generator(string fullname, string bday, string con_num) {
    string fln = Name_Number(fullname);
    string bn = Birth_Number(bday);
    string l4 = Last4_Digits(con_num);

    string acc_no = fln + bn + l4;
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
    ifstream fp(FILENAME); // Use the correct filename
    if (!fp) {
        cout << "No saved records found.\n";
        system("pause");
        return;
    }
    string line;
    while (getline(fp, line)) {
        if (line.empty())
            continue;
        size_t pos = 0, prev = 0;
        string fields[6];
        int idx = 0;
        while ((pos = line.find(',', prev)) != string::npos && idx < 5) {
            fields[idx++] = line.substr(prev, pos - prev);
            prev = pos + 1;
        }
        fields[idx] = line.substr(prev); // Last field (Balance)
        d.Acc_Number = fields[0];
        d.Name = fields[1];
        d.Birthday = fields[2];
        d.Con_Number = fields[3];
        d.Pin_code = fields[4];
        d.Balance = stof(fields[5]);
        decrypt(d.Pin_code);
        Add(d);
    }
    fp.close();
}
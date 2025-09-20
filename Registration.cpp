#include "Registration.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>

using namespace std;

Register::Register() : head(NULL), tail(NULL) {}

Register::~Register() {
    Node* post = head;
    while (post != NULL) {
        Node* temp = post;
        post = post->next;
        delete temp;
    }
    head = tail = NULL;
}

string Register::Name_Number(string fullname) {
    int count = 0, fn = 0;
    for (char c : fullname) {
        if (c != ' ')
            count++;
        else {
            fn = count;
            count = 0;
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

string Register::Last2_Digits(string con_num) {
    return con_num.substr(con_num.length() - 2);
}

string Register::Acc_No_Generator(string fullname, string bday, string con_num) {
    return Name_Number(fullname) + Birth_Number(bday) + Last2_Digits(con_num);
}

string Register::Get_Pin_Code() {
    string pin;
    char c;
    while ((c = getch()) != '\r') {
        if (c >= '0' && c <= '9') {
            pin += c;
            cout << "*";
        } else if (c == '\b') {
            if (!pin.empty()) {
                cout << "\b \b";
                pin.pop_back();
            }
        }
    }
    cout << endl;
    pin = encrypt(pin);
    return pin;
}

string Register::encrypt(string pin) {
    for (int i = 0; i < pin.size(); i++)
        pin[i] = pin[i] * v + v;
    return pin;
}

string Register::decrypt(string pin) {
    for (int i = 0; i < pin.size(); i++)
        pin[i] = pin[i] / v - v;
    return pin;
}

bool Register::AntiDup(string fullname, string bday, string con_num) {
    Node* post = head;
    while (post != NULL) {
        if (post->Data.Name == fullname &&
            post->Data.Birthday == bday &&
            post->Data.Con_Number == con_num) {
            cout << "Account already exists! Delete this account/Create a new one!\n";
            system("pause");
            return true;
        }
        post = post->next;
    }
    return false;
}

void Register::Add(Information x) {
    Node* newNode = new Node(x);
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
    Node* post = head;
    if (!fp) {
        cout << "Error opening file for saving!\n";
        system("pause");
        return;
    }
    while (post != NULL) {
        fp << post->Data.Acc_Number << ","
           << post->Data.Name << ","
           << post->Data.Birthday << ","
           << post->Data.Con_Number << ","
           << post->Data.Pin_code << ","
           << post->Data.Balance << endl;
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
        if (line.empty()) continue;
        size_t pos = 0, prev = 0;
        string fields[6];
        int idx = 0;
        while ((pos = line.find(',', prev)) != string::npos && idx < 5) {
            fields[idx++] = line.substr(prev, pos - prev);
            prev = pos + 1;
        }
        fields[idx] = line.substr(prev);
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

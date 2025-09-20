#ifndef REGISTER_H
#define REGISTER_H

#include <string>
using namespace std;

#define FILENAME "Account_Records.txt"
#define v 120

struct Information {
    string Acc_Number, Name, Birthday, Con_Number, Pin_code;
    float Balance;
};

class Register {
private:
    struct Node {
        Information Data;
        Node* next;
        Node* prev;
        Node(Information x) : Data(x), next(NULL), prev(NULL) {}
    };

    Node* head;
    Node* tail;
    string Name_Number(string fullname);
    string Birth_Number(string bday);
    string Last2_Digits(string con_num);
    string encrypt(string pin);
    string decrypt(string pin);

public:
    Register();
    ~Register();

    string Acc_No_Generator(string fullname, string bday, string con_num);
    string Get_Pin_Code();
    bool AntiDup(string fullname, string bday, string con_num);
    void Add(Information x);
    void Save();
    void Load();
};

#endif
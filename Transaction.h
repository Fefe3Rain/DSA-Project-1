#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Registration.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

#define FILENAME "Account_Records.txt"
#define v 120

struct Node{
    Information Data;
    struct Node *next;
    struct Node *prev;
    Node(Information x) : Data(x), next(NULL), prev(NULL) {}
};

class Transact {
    private:
        Node *head;
        Node *tail;
        string encrypt(string pin);
        string decrypt(string pin);
    public: 
        Transact();
        ~Transact();
        string Get_Pin_Code();
        Node* Locate(string PIN);
        bool Enter_Pin();
        void Balance_Inq(Node* p);
        void Withdraw(Node* p);
        void Deposit(Node* p);
        void Fund_Trans(Node* p);
        void Change_PIN(Node* p);
        void Add(Information x);
        void save(Node* p);
        void load();
};

int trans_menu();

#endif
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

#define FILENAME "Account_Records.txt"

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
        cout << "Name: ";
        cin.ignore();
        getline(cin, x.Name);
        cout << "Birthday (Month Day, Year): ";
        getline(cin, x.Birthday);
        cout << "Contact Number (09XXXXXXXXX): ";
        getline(cin, x.Con_Number);
        
    }
    return 0;
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
    cout << "Account number: " << x.Acc_Number << " added to the record." << endl;
    system("pause");
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
    cout << "Records saved successfully.\n";
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
        Add(d);
    }
    fp.close();
}
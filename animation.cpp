#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string bday = "06/08/2006";
    string birthNum = "";
    for (char c : bday)
        if (c != '/')
            birthNum += c;
    cout << birthNum;
    return 0;
}

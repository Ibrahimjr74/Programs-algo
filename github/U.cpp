#include <iostream>
using namespace std;
void logginMenu();
void userloggin();
void HEUCmicrofinanceMenuTop();
int main() {
    logginMenu();
    return 0;
}
void logginMenu() {
line:
    cout << "====================================================" << endl;
    int x;
    cout << "Login as :" << endl;
    cout << "\t1. user" << endl;
    cin >> x;
    if(x==1) {
        userloggin();
    }
}
void userloggin() {
    cout << "====================================================" << endl;
    char name[20];
    int id;
    char Address[20];
    string pass;
    cout<<"Name:"<<endl;
    cin >>name;
    cout << "Input ID(number):" << endl;
    cin >> id;
    cout <<"Address:"<<endl;
    cin >>Address;
    cout << "Input Password:" << endl;
    cin >> pass;
    HEUCmicrofinanceMenuTop();
}
void HEUCmicrofinanceMenuTop()
{   cout << "====================================================" << endl;
    int option;
    cout << "Select an Option: " << endl;
    cout << "\t2. Deposit money " << endl;
    cout << "\t3. Loan payment withdrawal " << endl;
    cout << "\t4. Check account balance " << endl;
    cout << "\t5.upgrading member ship" << endl;
    cout <<"\t6.log out "<<endl;
    cin >> option;
line:
    switch(option) {
    case 2:
        cout <<"Enter the amount to deposit:"<<endl;
        cout <<"Enter date <DD/MM/YYYY>:"<<endl;
        break;
    case 3:
        cout <<"Enter your member Id:"<<endl;
        cout <<"Enter loan period:"<<endl;
        cout<<"Enter amount to withdraw:"<<endl;
        break;
    case 4:
        cout <<"Enter your ID:";
        cout <<"Your balance is:";
        break;
    case 5:
        cout <<"Enter the amount to upgrade:";
        break;
    case 6:
        logginMenu();
        break;
    default:
        goto line;
        break;
    }
}
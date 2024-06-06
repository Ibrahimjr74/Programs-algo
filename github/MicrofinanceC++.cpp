#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
struct User{
	int number;
	string id;
	string name;
	string address;
	string contact;
	double balance;
	double salary;
	double contribution;
};
struct Loan{
	string id;
	double amount;
	double interest_rate;
	int duration;
	double monthly_rate;
	double total_payment;
};
struct Deposit{
	string id;
	double amount;
	string month;
	string year;
};
const int MAX_USERS = 100;
const int MAX_LOANS = 100;
const int MAX_DEPOSIT = 100;
User users[MAX_USERS];
Loan loans[MAX_LOANS];
Deposit deposit[MAX_DEPOSIT];

int usersQuantity = 0;
int loansQuantity = 0;
int depositQuantity = 0;

void saveUsers();
void loadUsers();
void saveLoan();
void loadLoans();
void registerUser();
void depositSalary(string id);
void loadDeposit();
void saveDeposit();
void changeContribution(string id);
void applyLoan(string id);
void repayLoan(string id);
void stocp(string s, char* cp){
	memset(cp, 0, strlen(cp));
	for(int i = 0; i < s.size(); i++){
		cp[i] = s[i];
	} //'\n' '\0'
}
int main(){
	//cout << "A number " << 34 << " " << 10.2;
	/*char buffer[200];
	float balance = 100.5;
	sprintf(buffer, "%f", balance);
	//sprintf(buffer, "A text: This is a text %d decimal %f fractional %c character", 20, 10.5, 'c');
	cout << buffer;*/
	
	User user;
	string id;
	loadUsers();
	loadDeposit();
	loadLoans();
	int opt;
	do{
		cout << "1. Register as a new user" << endl;
		cout << "2. Deposit a salary" << endl;
		cout << "3. Apply loan" << endl;
		cout << "4. Repay loan" << endl;
		cout << "5. Change contribution of a user" << endl;
		cout << "6. Quit" << endl;
		
		cin >> opt;
		switch(opt){
			case 1:
				registerUser();
				break;
			case 2:
				cout << "Enter your id" << endl;
				cin >> id;
				depositSalary(id);
				break;
			case 3:
				cout << "Enter your id" << endl;
				cin >> id;
				applyLoan(id);
				break;
			case 4:
				cout << "Enter your id" << endl;
				cin >> id;
				repayLoan(id);
				break;
			case 5:
				cout << "Enter your id" << endl;
				cin >> id;
				changeContribution(id);
				break;
			case 6:
				goto quit;
			default:
				cout << "Unkown input. Try again." << endl;
		}
	} while(opt != 6);
	quit:
		saveUsers();
		saveLoan();
		saveDeposit();
}
void saveUsers(){
	ofstream ofs;
	ofs.open("users.txt");
	ofs << "Number  ID   Name Address  Balance   Contact   Salary    Contribution\n"; 
	string number, id, name, address, contact, balance, salary, contribution;
	for(int i = 0; i < usersQuantity; i++){
		char s[300];
		memset(s, '\0', sizeof(char)); sprintf(s, "%d", users[i].number); number = s;
		id = users[i].id;
		name = users[i].name;
		address = users[i].address;
		contact = users[i].contact;
		memset(s, '\0', sizeof(char) * 300); sprintf(s, "%f", users[i].balance); balance = s;
		memset(s, '\0', sizeof(char) * 300); sprintf(s, "%f", users[i].salary); salary = s;
		memset(s, '\0', sizeof(char) * 300); sprintf(s, "%f", users[i].contribution); contribution = s;
		ofs << number << "\t" << id << "\t" << name << "\t" << address << "\t" << balance << "\t" << contact << "\t" << salary << "\t" << contribution << "\n";
	}
	ofs.close();
}
void loadUsers(){
	int i = 0;
	ifstream ifs;
	ifs.open("users.txt");
	char character = ifs.get();
	int number = 0;
	while(character != '\n' && number++ < 10000){
	 character = ifs.get(); 
	
	}

	character = ifs.get();
	User user;
	while(!ifs.eof() && number++ < 10000){
		string numberS = "", id = "", name = "", address = "", contact = "", balance = "", salary = "", contribution = "";
		while(character != '\t' && number++ < 10000){ numberS += character; character = ifs.get();  number++; } character = ifs.get();
		while(character != '\t' && number++ < 10000){ id += character; character = ifs.get();  } character = ifs.get();
		while(character != '\t' && number++ < 10000){ name += character; character = ifs.get();  } character = ifs.get();
		while(character != '\t' && number++ < 10000){ address += character; character = ifs.get(); } character = ifs.get();
		while(character != '\t' && number++ < 10000){ balance += character; character = ifs.get();  } character = ifs.get();
		while(character != '\t' && number++ < 10000){ contact += character; character = ifs.get(); } character = ifs.get();
		while(character != '\t' && number++ < 10000){ salary += character; character = ifs.get(); } character = ifs.get();
		while(character != '\n' && number++ < 10000){ contribution += character; character = ifs.get(); } character = ifs.get();
		if(number >= 10000){ break; }
		char s[200];
		stocp(numberS, s); users[i].number = atoi(s);
		users[i].id = id;
		users[i].name = name;
		users[i].address = address;
		users[i].contact = contact;
		stocp(balance, s); users[i].balance = atof(s);
		stocp(salary, s); users[i].salary = atof(s);
		stocp(contribution, s); users[i].contribution = atof(s);
		i++;
	}

	usersQuantity = i;
}
void registerUser(){
	User user;
	bool idTaken;
	cout << "Enter ID" << endl; cin >> users[usersQuantity].id;
	cout << "Enter name" << endl; cin >> users[usersQuantity].name;
	cout << "Enter address" << endl; cin >> users[usersQuantity].address;
	cout << "Enter contact" << endl; cin >> users[usersQuantity].contact;
	cout << "Enter salary" << endl; cin >> users[usersQuantity].salary;
	cout << "Enter contribution %" << endl; cin >> users[usersQuantity].contribution;
	do{
		idTaken = false;
		for(int i = 0; i < usersQuantity; i++){
			if(users[i].id == users[usersQuantity].id){
				idTaken = true;
				cout << "This ID has been taken. Try another one" << endl;
				cin >> users[usersQuantity].id;
				break;
			}
		}
	} while(idTaken);
	users[usersQuantity].number = usersQuantity;
	users[usersQuantity].balance = 100;
	usersQuantity++;
	saveUsers();
}
void loadDeposit(){
	int i = 0;
	ifstream ifs;
	ifs.open("deposit.txt");

	char character = ifs.get();
	User user;
	int number = 0;
	while(!ifs.eof() && number++ < 10000){
		string id = "", amount = "", month = "", year = "";
		while(character != '\t' && number++ < 10000){ id += character; character = ifs.get();  number++; } character = ifs.get();
		while(character != '\t' && number++ < 10000){ amount += character; character = ifs.get();  } character = ifs.get();
		while(character != '\t' && number++ < 10000){ month += character; character = ifs.get();  } character = ifs.get();
		while(character != '\n' && number++ < 10000){ year += character; character = ifs.get(); } character = ifs.get();
		
		if(number >= 10000){ break; }
		char s[200];
		deposit[i].id = id;
		stocp(amount, s); deposit[i].amount = atof(s);
		stocp(month, s); deposit[i].month = atoi(s);
		stocp(year, s); deposit[i++].year = atoi(s);
	}

	depositQuantity = i;
	ifs.close();
}
void saveDeposit(){
	ofstream ofs;
	ofs.open("deposit.txt");
	string id, amount, month, year;
	for(int i = 0; i < depositQuantity; i++){
		char s[300];
		id = deposit[i].id;
		memset(s, '\0', sizeof(char)); sprintf(s, "%f", deposit[i].amount); amount = s;
		month = deposit[i].month;
		year = deposit[i].year;
		ofs << id << "\t" << amount << "\t" << month << "\t" << year << "\n";
	}
	ofs.close();
}
void depositSalary(string id){
	//User user;
	for(int i = 0; i < usersQuantity; i++){
		if(users[i].id == id){
			users[i].balance += (users[i].contribution / 100) * users[i].salary;
			deposit[depositQuantity].id = id;
			deposit[depositQuantity].amount = users[i].salary * (users[i].contribution / 100);
			cout << "Enter the month when this got deposited" << endl;
			cin >> deposit[depositQuantity].month;
			cout << "Enter the year when this got deposited" << endl;
			cin >> deposit[depositQuantity++].year;
			cout << "Your current balance is " << users[i].balance << endl;
			saveUsers();
			saveDeposit();
			return;
		}
	}
	cout << "ID not found" << endl;
}
void changeContribution(string id){
	for(int i = 0; i < usersQuantity; i++){
		if(users[i].id == id){
			double newContribution;
			cout << "Enter your new contribution?" << endl;
			cin >> newContribution;
			users[i].contribution = newContribution;
			saveUsers();
			return;
		}
	}
	cout << "ID not found" << endl;
}
void loadLoans(){
	int i = 0;
	ifstream ifs;
	ifs.open("loan.txt");

	char character = ifs.get();
	User user;
	int number = 0;
	while(!ifs.eof() && number++ < 10000){
		string id="", amount = "", interest_rate = "", duration = "", monthly_rate = "", total_payment = "";
		while(character != '\t' && number++ < 10000){ id += character; character = ifs.get();  number++; } character = ifs.get();
		while(character != '\t' && number++ < 10000){ amount += character; character = ifs.get();  number++; } character = ifs.get();
		while(character != '\t' && number++ < 10000){ interest_rate += character; character = ifs.get();  } character = ifs.get();
		while(character != '\t' && number++ < 10000){ duration += character; character = ifs.get();  } character = ifs.get();
		while(character != '\t' && number++ < 10000){ monthly_rate += character; character = ifs.get();  } character = ifs.get();
		while(character != '\n' && number++ < 10000){ total_payment += character; character = ifs.get(); } character = ifs.get();
		
		if(number >= 10000){ break; }
		char s[200];
		loans[i].id = id;
		stocp(amount, s); loans[i].amount = atof(s);
		stocp(interest_rate, s); loans[i].interest_rate = atof(s);
		stocp(duration, s); loans[i].duration = atoi(s);
		stocp(monthly_rate, s); loans[i].monthly_rate = atof(s);
		stocp(total_payment, s); loans[i++].total_payment = atof(s);
	}

	loansQuantity = i;
	ifs.close();
}
void saveLoan(){
	ofstream ofs;
	ofs.open("loan.txt");
	string id, amount, interest_rate, duration, monthly_rate, total_payment;
	for(int i = 0; i < loansQuantity; i++){
		char s[300];
		id = loans[i].id;
		memset(s, '\0', sizeof(char) * 300); sprintf(s, "%f", loans[i].amount); amount = s;
		
		memset(s, '\0', sizeof(char) * 300); sprintf(s, "%f", loans[i].interest_rate); interest_rate = s;
		memset(s, '\0', sizeof(char) * 300); sprintf(s, "%d", loans[i].duration); duration = s;
		memset(s, '\0', sizeof(char) * 300); sprintf(s, "%f", loans[i].monthly_rate); monthly_rate = s;
		memset(s, '\0', sizeof(char) * 300); sprintf(s, "%f", loans[i].total_payment); total_payment = s;
		ofs << id << "\t" << amount << "\t" << interest_rate << "\t" << duration << "\t" << monthly_rate << "\t" << total_payment << "\n";
		//ofs << number << "\t" << id << "\t" << name << "\t" << address << "\t" << balance << "\t" << contact << "\t" << salary << "\t" << contribution << "\n";
	}
	ofs.close();
}
void applyLoan(string id){
	for(int i = 0; i < usersQuantity; i++){
		if(users[i].id == id){
			for(int j = 0; j < loansQuantity; j++){
				if(loans[j].id == id){
					if(loans[j].amount > 0){
						cout << "You need to have your previous loan repaid before you apply for a loan" << endl;
						return;
					}
				}
			}
			cout << "Avaliable balance " << users[i].balance << endl;
			cout << "Enter loan amount (up to 4 times your balance): " << endl;
			Loan loan;
			cin >> loan.amount;
			if(loan.amount > 4 * users[i].balance || loan.amount > 300000){
				cout << "Loan amount exceeds limit" << endl;
				return;
			}
			if(loan.amount <= 60000){
				loan.duration = 12;
			} else if(loan.amount > 60000 && loan.amount <= 300000){
				loan.duration = 30;
			}
			loan.interest_rate = 1.09; // monthly interest rate of 9
			loan.total_payment = loan.amount * pow((1 + loan.interest_rate / loan.duration), loan.duration);
			
			users[i].balance += loan.amount;
			loans[loansQuantity].id = id;
			loans[loansQuantity].amount = loan.amount;
			loans[loansQuantity].interest_rate = 1.09;
			loans[loansQuantity].duration = loan.duration;
			loans[loansQuantity].monthly_rate = loan.total_payment / loan.duration;
			loans[loansQuantity++].total_payment = loan.total_payment;
			saveUsers();
			saveLoan();
			return;
		}
	}
	cout << "ID not found" << endl;
}
void repayLoan(string id){
	for(int i = 0; i  < usersQuantity; i++){
		if(users[i].id == id){
			for(int j = 0; j < loansQuantity; j++){
				if(loans[j].id == id){
					cout << "Your monthly payment is " << loans[j].monthly_rate << endl;
					char choiceToPay;
					cout << "Do you want to pay right now? (Y/N)" << endl;
					cin >> choiceToPay;
					if(choiceToPay == 'Y'){
						loans[j].amount -= loans[j].monthly_rate;
						loans[j].duration--;
						if(loans[j].duration == 0){
							cout << "Loan fully repaid" << endl;
						}
						saveLoan();
					}
					return;
				}
			}
			cout << "You haven't applied for a loan" << endl;
			return;
		}	 
	}
	cout << "ID not found" << endl;
}


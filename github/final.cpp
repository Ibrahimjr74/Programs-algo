#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;
const double interest_rate = 0.07;
const int MAX_USERS = 100;
const double CONTRIB_RATES[] = { 10.0, 7.5, 5.0, 2.5, 1.0};
const int MAX_DEPOSIT =100;
const string file_name="my file.txt"; 
struct User {
	string u_id;
	string name;
	string address;
	string deparment;
	double salary;
	double contrib;
	double deposit;
	double remaining_loan_amount;
	double remaining_time;
};
User users[MAX_USERS];
int num_of_users = 0;   //initial number of users
int year=2015; //starting year of system
fstream file;
void load_from_file()
{
	file.open(file_name, ios::in);
	if(file.is_open())
	{
		cout<<"Opened file\n";
		file.seekg(0);
		file.read( (char*)&year, sizeof(year) );		//reay the year from last running
		file.read( (char*)&num_of_users, sizeof(num_of_users) );		//reay the year from last running
		cout<<"We had "<<num_of_users<<" users in year "<<year<<endl;
		for(int i=0;i<num_of_users;i++)            // quit on EOF
		{
			file.read( (char*)&users[i], sizeof(users[i]) );  // read a single user
		}
		file.close();
	}
	else
		cout<<"No file found to load history\n";
}

void save_to_file()
{
	file.open(file_name, ios::out);
	if(file.is_open())
	{
		file.seekg(0);
		file.write( (char*)&year, sizeof(year) );  // write the year for next opening
		file.write( (char*)&num_of_users, sizeof(num_of_users) );  // write the year for next opening
		for(int i=0;i<num_of_users;i++)           // for all users in the array
		{
			file.write( (char*)&users[i], sizeof(users[i]) );  // write a single user
		}
		file.close();
	}
	else
		cout<<"No file found to Save history\n";

}

int find(string uid)
{
	for(int i=0;i<num_of_users; i++)
	{
		if(users[i].u_id == uid)
			return i;
	}
	return -1;
}
int findUser()
{
	string uid="";
	int idx=-1, option;
	do
	{
		cout<<"Enter the ID:";
		cin>>uid;
		idx = find(uid);
		if(idx == -1)
		{
			cout<<"No user with this ID!\n Enter 0 to enter again OR 1 to Exit:";
			cin>>option;
			if(option == 1)
				return -1;
		}
		else
		 return idx;
	}while(idx == -1);
	return idx;
}
void addUser()
{
	int option=0;
	string uid="";
	cout<<"Enter new ID: ";
	cin>>uid;
	while(find(uid) != -1)
	{
		cout<<"Ther exists User with this ID,\n Enter 0 to enter again OR 1 to Exit:";
		cin>>option;
		if(option)
			return;
		cout<<"Enter new ID: ";
		cin>>uid;
	}
	users[num_of_users].u_id = uid;
	cout<<"Enter new Name: ";
	cin>>users[num_of_users].name;
	cout<<"Enter new Address: ";
	cin>>users[num_of_users].address;
	cout<<"Enter new Department: ";
	cin>>users[num_of_users].deparment;
	cout<<"Enter new Salary: ";
	cin>>users[num_of_users].salary;
	cout<<"Choose contribution rate in percentage of salary:\n 1 , 5 , 10, OR 15 :";
	cin>>users[num_of_users].contrib;
	users[num_of_users].contrib /= 100;
	users[num_of_users].deposit = 0;
	users[num_of_users].remaining_loan_amount = 0;
	users[num_of_users].remaining_time = 0;
	num_of_users++;
}
void deleteUser()
{
	int id = findUser(), option = 0;
	if(id == -1)
		return;
	if(users[id].remaining_loan_amount)
	{
		cout<<users[id].name<<" has remaining loan amoun of "<<users[id].remaining_loan_amount<<" to be repayed wnth in "<<users[id].remaining_time<<" years\n Enter 0 to clear dept and remove user OR 1 to exit:";
		cin>>option;
		if(option)
			return;
	}
	cout<<users[id].name<<" has been removed";
	num_of_users--;	
	for(int i=id;i<num_of_users;i++)
		users[i] = users[i+1];
}
void updateUser()
{
	int id = findUser();
	if(id == -1)
		return;
	cout<<"####################\nName: "<<users[id].name<<"\nAddress: "<<users[id].address<<"\nDepartment: "<<users[id].deparment<<"\nSalary: "<<users[id].salary<<"\nDeposit: "<<users[id].deposit<<endl;
	if(users[id].remaining_loan_amount)
		cout<<"\nRemaining payment on loan: "<<users[id].remaining_loan_amount<<endl;
	cout<<"Enter new Name: ";
	cin>>users[id].name;
	cout<<"Enter new Address: ";
	cin>>users[id].address;
	cout<<"Enter new Department: ";
	cin>>users[id].deparment;
	cout<<"Enter new Salary: ";
	cin>>users[id].salary;
	cout<<"ENter new contribution rate in percentage of salary 1 , 5 , 10, OR 15 :";
	cin>>users[id].contrib;
	users[num_of_users].contrib /= 100;
	users[id].remaining_time = users[id].remaining_loan_amount/(users[id].salary * users[id].contrib);
}
void pushTime()
{
	for(int i=0;i<num_of_users;i++)
	{
		if(users[i].remaining_loan_amount)
		{
			if(users[i].remaining_loan_amount > users[i].salary * users[i].contrib)
			{
				users[i].remaining_loan_amount -=  users[i].salary * users[i].contrib;
				users[i].remaining_loan_amount *= (1+interest_rate);
				users[i].remaining_time = users[i].remaining_loan_amount/(users[i].salary * users[i].contrib);
			}
			else
			{
				users[i].deposit = users[i].salary * users[i].contrib - users[i].remaining_loan_amount;
				users[i].remaining_loan_amount = 0;
			}
		}
		else
			users[i].deposit += users[i].salary * users[i].contrib;                                                
	}
	year++;	
}
void askLoan()
{
	int id = findUser(), option = 0;
	if(id == -1)
		return;
	if(users[id].remaining_loan_amount)
		cout<<users[id].name<<" already have unsetteled load with remaining amount of "<<users[id].remaining_loan_amount<<" to be repayed wnth in "<<users[id].remaining_time<<" yeras\n### LOAN NOT APPROAVED ###\n";
	else if (users[id].deposit == 0)
	{
		cout<<users[id].name<<" has no deposit, ### LOAN NOT APPROAVED ###\n";
	}
	else		//cheack load requierements and grnat
	{
		do
		{
			cout<<"Enter amount of loan below your limit ("<<users[id].deposit * 4 <<"): ";
			cin>>users[id].remaining_loan_amount;
			if(users[id].remaining_loan_amount < users[id].deposit * 4)
			{
				cout<<"Loan of "<<users[id].remaining_loan_amount<<" have been GRANTED to "<<users[id].name;
				users[id].remaining_loan_amount -= users[id].deposit;
				users[id].deposit = 0;
				users[id].remaining_time = users[id].remaining_loan_amount/(users[id].salary * users[id].contrib);
				cout<<"\n to be repayed wnth in "<<users[id].remaining_time<<" years"<<endl;
				break;
			}
			else
			{
				users[id].remaining_loan_amount = 0;
				cout<<"loan amoun is above limit, choose 1 to re-enter another amount OR 0 to Exit:";
				cin>>option;
			}
		} while (option);
	}
}
void mainMenu()
{
	string uid="";
	int idx=-1;
	int option=0 ;
	load_from_file();
	while(option != 7)
	{
		cout<<"Microfinance system ("<<year<<" E.C.)";
		cout<<"We have total of "<<num_of_users<<" users,\nChoos an action from the options bellow:"<<endl;
		cout<<"1.Add new"<<endl;
		cout<<"2.Delete user"<<endl;
		cout<<"3.Show user history"<<endl;
		cout<<"4.Update user information"<<endl;
		cout<<"5.Ask for a loan"<<endl;
		cout<<"6.Push time one year"<<endl;
		cout<<"7.exit"<<endl;
		cin>>option;
		switch(option) {
		case 1:
			addUser();
			break;
		case 2:
			deleteUser();
			break;
		case 3:
			idx = findUser();
			if(idx != -1)
				cout<<"####################\nName: "<<users[idx].name<<"\nAddress: "<<users[idx].address<<"\nDepartment: "<<users[idx].deparment<<"\nSalary: "<<users[idx].salary<<"\nDeposit: "<<users[idx].deposit<<endl;
				if(users[idx].remaining_loan_amount)
					cout<<"Remaining payment on loan: "<<users[idx].remaining_loan_amount<<"\n to be repayed wnth in "<<users[idx].remaining_time<<" years"<<endl;
				cout<<"####################\n\n";
			break;
		case 4:
			updateUser();
			break;
		case 5:
			askLoan();
			break;
		case 6:
			pushTime();
			break;
		case 7:
			save_to_file();
			break;
		default:
			cout<<"invalid option:"<<endl;
		}
	}
}


int main() {
	cout<<"welcome to HEUC Microfinance "<<endl;
	mainMenu(); 
	return 0;
}


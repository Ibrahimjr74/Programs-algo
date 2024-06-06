#include<iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_USERS = 100;
const int MAX_DESTINATIONS = 100;

struct User {
    char name[50];
    int age;
    char gender;
    int ID;
};

struct Destination {
    char name[50];
    char description[100];
    double rating;
};

void registerUser(User users[], int &userCount);
void addDestination(Destination destinations[], int &destinationCount);
void displayUsersAndDestinations(const User users[], int userCount, const Destination destinations[], int destinationCount);
void selectionSortByName(User arr[], int n);
void bubbleSortByName(User arr[], int n);
void insertionSortByID(User arr[], int n);
void bubbleSortByID(User arr[], int n);
void linearSearchByName(const User arr[], int n, const string &targetName);
void binarySearchByID(const User arr[], int left, int right, int targetID);
void linearSearchByGender(const User arr[], int n, char targetGender);

void displayMenu() {
    cout << "===== Tourism Management System =====" << endl;
    cout << "1. Register a user" << endl;
    cout << "2. Add a destination" << endl;
    cout << "3. Display users and destinations" << endl;
    cout << "4. Sort user list" << endl;
    cout << "5. Search for a user" << endl;
    cout << "6. Exit" << endl;
    cout << "====================================" << endl;
}

void registerUser(User users[], int &userCount) {
    if (userCount == MAX_USERS) {
        cout << "Cannot register more users. Maximum limit reached." << endl;
        return;
    }

    User newUser;
    cout << "Enter the name of the user: ";
    cin.getline(newUser.name, 50);

    cout << "Enter the age of the user: ";
    cin >> newUser.age;
    cin.ignore();

    cout << "Enter the gender of the user (M/F): ";
    cin >> newUser.gender;
    cin.ignore();

    cout << "Enter the ID of the user: ";
    cin >> newUser.ID;
    cin.ignore();

    users[userCount++] = newUser;
    cout << "User registered successfully." << endl;
}

void addDestination(Destination destinations[], int &destinationCount) {
    if (destinationCount == MAX_DESTINATIONS) {
        cout << "Cannot add more destinations. Maximum limit reached." << endl;
        return;
    }

    Destination newDestination;
    cout << "Enter the name of the destination: ";
    cin.getline(newDestination.name, 50);

    cout << "Enter the description of the destination: ";
    cin.getline(newDestination.description, 100);

    cout << "Enter the rating of the destination (1-5): ";
    cin >> newDestination.rating;
    cin.ignore();

    destinations[destinationCount++] = newDestination;
    cout << "Destination added successfully." << endl;
}

void displayUsersAndDestinations(const User users[], int userCount, const Destination destinations[], int destinationCount) {
    if (userCount == 0 && destinationCount == 0) {
        cout << "No users and destinations to display." << endl;
        return;
    }

    cout << "Users:" << endl;
    for (int i = 0; i < userCount; ++i) {
        cout << "Name: " << users[i].name << endl;
        cout << "Age: " << users[i].age << endl;
        cout << "Gender: " << users[i].gender << endl;
        cout << "ID: " << users[i].ID << endl;
        cout << "-------------------------" << endl;
    }

    cout << "Destinations:" << endl;
    for (int i = 0; i < destinationCount; ++i) {
        cout << "Name: " << destinations[i].name << endl;
        cout << "Description: " << destinations[i].description << endl;
        cout << "Rating: " << destinations[i].rating << endl;
        cout << "-------------------------" << endl;
    }
}
void  linearSearchByGender(const User arr[], int n, char targetGender) {
    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (arr[i].gender == targetGender) {
            cout << "User found:" << endl;
            cout << "Name: " << arr[i].name << endl;
            cout << "Age: " << arr[i].age << endl;
            cout << "Gender: " << arr[i].gender << endl;
            cout << "ID: " << arr[i].ID << endl;
            found = true;
        }
        else{
        	return;
		}
        break;  // Uncomment this line if you only want to display the first match
    }
}



void binarySearchByID(const User arr[], int left, int right, int targetID) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].ID == targetID) {
            cout << "User found:" << endl;
            cout << "Name: " << arr[mid].name << endl;
            cout << "Age: " << arr[mid].age << endl;
            cout << "Gender: " << arr[mid].gender << endl;
            cout << "ID: " << arr[mid].ID << endl;
            return; // Return once found
        } else if (arr[mid].ID < targetID) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout << "User not found." << endl;
}

int main() {
    User users[MAX_USERS];
    int userCount = 0;

    Destination destinations[MAX_DESTINATIONS];
    int destinationCount = 0;

    int choice;
    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            registerUser(users, userCount);
            break;
        case 2:
            addDestination(destinations, destinationCount);
            break;
        case 3:
            displayUsersAndDestinations(users, userCount, destinations, destinationCount);
            break;
        case 4:
            if (userCount > 0)
            {
                int sortChoice;
s:
                cout << "Sort Options:\n"
                     << "1. Sort alphabetically by name A-Z\n"
                     << "2. Sort alphabetically by name Z-A\n"
                     << "3. Sort by ID in ascending order\n"
                     << "4. Sort by ID in descending order\n"
                     << "Enter your choice: ";
                cin >> sortChoice;

                switch (sortChoice)
                {
                case 1:
                    selectionSortByName(users, userCount);
                    break;
                case 2:
                    bubbleSortByName(users, userCount);
                    break;
                case 3:
                    insertionSortByID(users, userCount);
                    break;
                case 4:
                    bubbleSortByID(users, userCount);
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
                    goto s;
                }

                displayUsersAndDestinations(users, userCount, destinations, destinationCount);
            }
            else
            {
                cout << "No users to sort. Register a user first.\n";
            }
            break;
        case 5:
            int searchChoice;
            cout << "Search Options:\n"
                 << "1. Search by user name\n"
                 << "2. Search by user ID\n"
                 << "3. Search by gender\n"
                 << "Enter your choice: ";
            cin >> searchChoice;
            cin.ignore();
            switch (searchChoice) {
            case 1:
            {
                string targetName;
                cout << "Enter the name to search: ";
                getline(cin, targetName);
                linearSearchByName(users, userCount, targetName);
            }
            break;
            case 2:
            {
                int targetID;
                cout << "Enter the ID to search: ";
                cin >> targetID;
                binarySearchByID(users, 0, userCount - 1, targetID);
            }
            break;
            case 3:
            {
                char targetGender;
                cout << "Enter the gender to search (M/F): ";
                cin >> targetGender;
                linearSearchByGender(users, userCount, targetGender);
            }
            break;
            cout << "Invalid choice. Please try again." << endl;
            break;
            }
            break;
        case 6:
            cout << "Exiting program." << endl;
            return 0;

        }

        cout << endl;
    }
}

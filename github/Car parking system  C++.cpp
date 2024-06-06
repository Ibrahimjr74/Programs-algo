#include <iostream>
#include<ctime>
using namespace std;
struct Car {
    int slot;  // Add the slot field
    int time;
    int date;
    string plate;
    Car* next = NULL;
    Car* prev = NULL;
};
Car* head = NULL;
void display_car(Car* car) {
    cout << "Slot: " << car->slot << endl;
    cout << "Time parking: " << car->time << endl;
    cout << "Date: " << __DATE__ << endl;
    cout << "Plate: " << car->plate << endl;
}
void insert_front(Car* new_node) {
    if (head == NULL) {
        new_node->slot = 1;
        head = new_node;
        cout << "Car parked at slot " << new_node->slot << " successfully." << endl;
    } else {
        cout << "Parking lot is already occupied. Cannot insert more cars." << endl;

    }
}
void insert_middle(Car* prev_node, Car* new_node) {
    if (prev_node == NULL) {
        cout << "The given previous node cannot be NULL" << endl;
        return;
    }
    if (prev_node->slot + 1 > 9) {
        cout << "goto the end slot. Cannot insert more cars." << endl;
        return;
    }

    new_node->next = prev_node->next;
    prev_node->next = new_node;
    new_node->prev = prev_node;
    if (new_node->next != NULL) {
        new_node->next->prev = new_node;
    }

    new_node->slot = prev_node->slot + 1;
    cout << "Car parked at slot " << new_node->slot << " successfully." << endl;
}



void insert_end(Car* new_node) {
    if (head == NULL) {
        new_node->slot = 10;
        head = new_node;
        cout << "Car parked at slot " << new_node->slot << " successfully." << endl;
    } else {
        Car* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        new_node->slot = temp->slot;
        temp->next = new_node;
        new_node->prev = temp;
        cout << "Car parked at slot " << new_node->slot << " successfully." << endl;
    }
}
void delete_node(Car* del_node) {
    if (head == NULL || del_node == NULL) {
        return;
    }
    if (head == del_node) {
        head = del_node->next;
    }
    if (del_node->next != NULL) {
        del_node->next->prev = del_node->prev;
    }
    if (del_node->prev !=NULL) {
        del_node->prev->next = del_node->next;
    }
    delete del_node;
}
void sortCars(bool ascending, bool sortByTime) {
    Car* temp = head;
    Car* sortedList = NULL;
    while (temp != NULL) {
        Car* next = temp->next;

        if (sortByTime) {
            if (ascending) {
                while (sortedList != NULL && sortedList->time > temp->time) {
                    sortedList = sortedList->next;
                }
            } else {
                while (sortedList != NULL && sortedList->time < temp->time) {
                    sortedList = sortedList->next;
                }
            }
        } else {
            if (ascending) {
                while (sortedList != NULL && sortedList->slot > temp->slot) {
                    sortedList = sortedList->next;
                }
            } else {
                while (sortedList != NULL && sortedList->slot < temp->slot) {
                    sortedList = sortedList->next;
                }
            }
        }
        temp->next = sortedList;
        temp->prev = NULL;
        if (sortedList != NULL) {
            sortedList->prev = temp;
        }
        sortedList = temp;

        temp = next;
    }

    head = sortedList;
}
int search(Car* head, const std::string& value) {
    Car* temp = head;
    int pos = 1;

    while (temp != NULL) {
        if (temp->plate == value) {
            return pos;
        }
        temp = temp->next;
        pos++;
    }

    return -1;
}
void display_all() {
    Car* temp = head;
    while (temp != NULL) {
        display_car(temp);
        cout << "---------------------" << endl;
        temp = temp->next;
    }
}
float calculate_fee(Car* car,int time) {
	float fee = 0.0; // the initial fee
    if (car->time <= 60) { // if the parking time is less than or equal to 60 minutes
        fee = 15.0; // the fee is 5.0
    }
    else { // if the parking time is more than 60 minutes
        fee = 15.0 + (car->time - 60) * 0.1; // the fee is 5.0 plus 0.1 for each extra minute
    }
    return fee;
}

void display_menu() {
    cout << "Welcome to the car parking system!" << endl;
    cout << "Please choose an option below:" << endl;
    cout << "\t1. Park a car" << endl;
    cout << "\t2. Sort" << endl;
    cout << "\t3. Search for a car" << endl;
    cout << "\t4. Unpark" << endl;
    cout << "\t5. Display all cars" << endl;
    cout << "\t6. Exit the system" << endl;
}

int main() {
    const int MAX = 10;
    int count = 0;
    bool exit = false;
    int option;
    char ch2,ch3;
    bool reserved = false; // Move the reserved flag outside the loop

    while (!exit) {
        display_menu();
        cin >> option;

        switch (option) {
        case 1:
            if (count < MAX) {
                cout << "Choose your position:" << endl;
                cout << "F.insert-Front" << endl;
                cout << "M.insert-middle" << endl;
                cout << "E.insert-End" << endl;
                cin >> ch2;
                if (ch2 == 'F') {
                    Car* car = new Car();
                    cout << "Enter the plate number: ";
                    cin >> car->plate;
                    cout << "Enter the parking time in minutes: ";
                    cin >> car->time;
                    insert_front(car);
                    break;
                    if (!reserved) {
                        cout << "Slot is reserved." << endl;
                        reserved = true; // Set reserved to true only once
                        cout << "The car has been parked successfully." << endl;

                    }

                } else if (ch2 == 'M') {
                    Car* car = new Car();
                    cout << "Enter the plate number: ";
                    cin >> car->plate;
                    cout << "Enter the parking time in minutes: ";
                    cin >> car->time;
                    int slot;

                    cout   << "Enter the slot after which to park the car: ";
                    cin >> slot;
                    Car* temp = head;
                    while (temp != NULL && temp->slot != slot) {
                        temp = temp->next;
                    }
                    insert_middle(temp, car);
                    break;
                }
            }
            if (ch2 == 'E') {
                Car* car = new Car();
                cout << "Enter the plate number: ";
                cin >> car->plate;
                cout << "Enter the parking time in minutes: ";
                cin >> car->time;
                insert_end(car);
                break;
                if (!reserved) {
                    cout << "Slot is reserved." << endl;
                    reserved = true;
                }
                cout << "The car has been parked successfully." << endl;


            } else {
                cout << "Invalid option. Please choose F, A, or E." << endl;
            }


        case 2:
        {

            cout << "A. Ascending order sort\n";
            cout << "D. Descending order sort \n";
            cin >> ch3;

            if (ch3 == 'A' || ch3 == 'a') {
                sortCars(false, true);
                cout << "Cars sorted in ascending order." << endl;
                display_all();
            } else if (ch3 == 'D' || ch3 == 'd') {
                sortCars(true, true);
                cout << "Cars sorted in descending order." << endl;
                display_all();
            } else {
                cout << "Invalid choice. Please enter A or D." << endl;
            }
            break;
        }

        case 3: {
            Car* car = new Car();
            cout << "Enter the plate number: ";
            cin >> car->plate;

            int pos = search(head, car->plate);
            if (pos != -1) {
                cout <<" your car found!\n";
                cout << "Your car is located at slot " << pos << "." << endl;
                display_all();
            } else if(delete_node) {
                cout <<" this car had left before this\n" <<__TIME__<< " At this Date\n"<<__DATE__<<endl;
            }

            break;
        }
        case 4:
      char now;
          {
        Car* car = new Car();
            if (count < MAX) {

                cout << "Enter the plate number of the car to unpark: ";
                std::string plate;
                cin >> plate;

                int pos = search(head, plate);

                if (pos != -1) {
                    Car* carToDelete = head;
                    for (int i = 1; i < pos; i++) {
                        carToDelete = carToDelete->next;
                    }
                    delete_node(carToDelete);
                   
                    time_t current_time = car->time;
                    tm* time_info = std::localtime(&current_time);
                    int currentMinutes = time_info->tm_hour * 60 + time_info->tm_min;
                    int totalTimeParked = currentMinutes - carToDelete->time;

  
                    float fee = calculate_fee(carToDelete, totalTimeParked);
                    cout << "lane passed at " <<time << " minutes." << endl;
                    cout <<" your service fee is " << fee<<"$"<< endl;
                } else {
                    
            cout << "There is no car with plate number " << plate << "." << endl;
                }
            } else {
                cout << "Sorry, the parking lot is empty." << endl;
            }
            break;
        }

           case 5:
            cout << "Here you have the list:" << endl;
            display_all();
            break;

        case 6:
            cout << "Thank you for using the car parking system. Goodbye!" << endl;
            exit = true;
            break;

        default:
            cout << "Sorry, that is not a valid option. Please try again." << endl;
            break;
        }
    }
    return 0;
}

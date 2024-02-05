#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Contact {
private:
    string fname;
    string lname;
    string phone_no;
    int hisaab;
public:
    void admin_menu();
    void customer_menu();
    void add_hisaab();
    void search(string name);
    void show_hisaab();
    void delete_hisaab();
};

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void setTextColor(int color) {
    cout << "\033[1;" << color << "m";
}

void Contact::admin_menu() {
    clearScreen();
    setTextColor(10);
    cout << "\n\n\t1. Add Hisaab\n\t2. Search Hisaab\n\t3. Show Hisaab\n\t4. Delete Hisaab\n\t5. Exit\n\t> ";
}

int checker(string phone_no) {
    return (phone_no.length() == 10) ? 1 : 0;
}

void Contact::add_hisaab() {
    ofstream file("contact.txt", ios::app);
    cout << "\n \t Enter the first Name : ";
    cin >> fname;
    cout << "\n\tEnter Last Name : ";
    cin >> lname;
    cout << "\n\tEnter 10-Digit Phone Number : ";
    cin >> phone_no;
    cout << "\n \t Enter the amount ";
    cin >> hisaab;

    if (!checker(phone_no)) {
        cout << "\t Error: Number is invalid" << endl;
        add_hisaab(); 
        return;
    }

    if (file.is_open()) {
        file << fname << " " << lname << ":" << phone_no << " " << hisaab << "\n";
        cout << "\nHisaab saved successfully" << endl;
    } else {
        cout << "Error: File is not opened, please try again" << endl;
    }
    file.close(); 
}

void Contact::search(string name) {
    ifstream file("contact.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open file" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find(name) != string::npos) {
            cout << "The details of the hisaab are as follows :" << endl;
            cout << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "The details are not available" << endl;
    }
    file.close();
}

void Contact::customer_menu() {
    clearScreen();
    setTextColor(11);
    string getname;
    cout << "\t \t Enter your name to know your pending hisaab : ";
    cin.ignore();
    getline(cin, getname);
    search(getname);
}

void Contact::show_hisaab() {
    ifstream file("contact.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open file" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void Contact::delete_hisaab() {
    string name;
    cout << "Enter the name to delete the hisaab : ";
    cin >> name;

    ifstream input("contact.txt");
    ofstream temp("temp.txt");

    if (!input.is_open() || !temp.is_open()) {
        cout << "Error: Unable to open files" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(input, line)) {
        if (line.find(name) != string::npos) {
            cout << "The details of the hisaab are as follows :" << endl;
            cout << line << endl;
            found = true;
            char ans;
            cout << "Do you want to delete the hisaab Y/N : ";
            cin >> ans;
            if (ans == 'Y' || ans == 'y') {
                cout << "The hisaab Deleted successfully" << endl;
            } else if (ans == 'N' || ans == 'n') {
                temp << line << endl; 
            } else {
                cout << "Invalid input " << endl;
            }
        } else {
            temp << line << endl;
        }
    }

    input.close();
    temp.close();

    if (!found) {
        cout << "Record not found" << endl;
    } else {
        remove("contact.txt");
        rename("temp.txt", "contact.txt");
    }
}

int main() {
    clearScreen();
    setTextColor(14);
    cout << "\n\t\t\t\t\t\tHISAAB MANAGEMENT SYSTEM";
    int choice1;
    int flag = 0;
    Contact number;

    do {
        cout << "\n\n\t1.Admin\n\t2.Customer\n\t3.Exit" << endl;
        cout << "Enter the choice ";
        cin >> choice1;

        switch (choice1) {
            case 1:
                int key;
                cout << "Enter the passcode of the admin: ";
                cin >> key;

                if (key == 2987) {
                    cout << "Access granted " << endl;
                    flag = 1;
                    number.admin_menu();
                } else {
                    cout << "Access denied, try again" << endl;
                    flag = 0;
                }
                break;

            case 2:
                number.customer_menu();
                break;

            case 3:
                break;

            default:
                cout << "Enter the valid option" << endl;
        }

    } while (choice1 != 3 && flag != 1);

    if (choice1 != 3) {
        int choice2;
        int flag1 = 0;

        do {
            number.admin_menu();
            cout << "Enter the choice ";
            cin >> choice2;

            switch (choice2) {
                case 1:
                    number.add_hisaab();
                    break;

                case 2:
                    {
                        string Name;
                        cout << "Enter the Name to get the details : ";
                        cin.ignore();
                        getline(cin, Name);
                        number.search(Name);
                    }
                    break;

                case 3:
                    number.show_hisaab();
                    break;

                case 4:
                    number.delete_hisaab();
                    break; 

                case 5:
                    flag1 = 1;
                    break;

                default:
                    cout << "Enter a valid input" << endl;
            }

            if (flag1 == 1) break;

            char ans;
            cout << "Do you want to continue Y/N : ";
            cin >> ans;

            if (ans != 'Y' && ans != 'y') break;

        } while (choice2 != 5);
    }
    return 0; 
}

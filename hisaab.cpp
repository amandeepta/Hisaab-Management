#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class contact {
private:
    string fname;
    string lname;
    string phone_no;
    int hisaab;
public:
    // Function declarations
    void admin_menu();
    void customer_menu();
    void add_hisaab();
    void search(string name);
    void show_hisaab();
    void delete_hisaab();
};

// Function to clear the screen
void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ANSI escape code to clear screen
}

// Function to set text color
void setTextColor(int color) {
    cout << "\033[1;" << color << "m"; // ANSI escape code to set text color
}

// Function to display the admin menu
void contact::admin_menu() {
    clearScreen();
    setTextColor(10); // Set text color to green
    cout << "\n\n\t1. Add Hisaab\n\t2. Search Hisaab\n\t3. Show hisaab\n\t4. Delete Hisaab\n\t5. Exit\n\t> ";
}

// Function to check if the phone number is valid
int checker(string phone_no) {
    if (phone_no.length() == 10) {
        cout << "\t Number is valid" << endl; // Add newline character here
        return 1;
    } else {
        cout << "\t Error Number is invalid " << endl; // Add newline character here
        return 0;
    }
}

// Function to add a new entry to the hisaab
void contact::add_hisaab() {
    ofstream file("contact.txt", ios::app);
    cout << "\n \t Enter the first Name : ";
    cin >> fname;
    cout << "\n\tEnter Last Name : ";
    cin >> lname;
    cout << "\n\tEnter 10-Digit Phone Number : ";
    cin >> phone_no;
    cout << "\n \t Enter the amount ";
    cin >> hisaab;

    if (checker(phone_no) == 0) {
        add_hisaab(); // Recursive call if phone number is invalid
    }
    if (file.is_open()) {
        file << fname << " " << lname << ":" << phone_no << " " << hisaab << "\n";
        cout << "\nHisaab saved successfully" << endl;
    } else {
        cout << "File is not opened try again" << endl;
    }
    file.close(); // Close the file after using it
}

// Function to search for a hisaab entry by name
void contact::search(string name) {
    ifstream file;
    file.open("contact.txt");

    int flag = 0;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find(name) != string::npos) {
                cout << "The details of the hisaab are as follows :" << endl;
                cout << line << endl;
                flag = 1;
            }
        }
        if (flag == 0) cout << "The details are not available" << endl;
    }
    file.close(); // Close the file after using it
}

// Function to display the customer menu and search for pending hisaab
void contact :: customer_menu() {
    clearScreen();
    setTextColor(11); // Set text color to light cyan
    string getname;
    cout << "\t \t Enter your name to know your pending hisaab : ";
    cin.ignore();
    getline(cin,getname);
    search(getname);
} 

// Function to display all hisaab entries
void contact::show_hisaab() {
    ifstream file;
    file.open("contact.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
    }
    file.close(); // Close the file after using it
}

// Function to delete a hisaab entry
void contact::delete_hisaab() {
    string name;
    cout << "Enter the name to delete the hisaab : ";
    cin >> name;

    ifstream input("contact.txt");
    ofstream temp("temp.txt");

    int flag = 0;
    string line;

    while (getline(input, line)) {
        if (line.find(name) != string::npos) {
            cout << "The details of the hisaab are as follows :" << endl;
            cout << line << endl;
            flag = 1;
            char ans;
            cout << "Do you want to delete the hisaab Y/N : ";
            cin >> ans;
            if (ans == 'Y' || ans == 'y') {
                // Do nothing here, so line will not be written to temp.txt
                cout << "The hisaab Deleted successfully" << endl;
            } else if (ans == 'N' || ans == 'n') {
                temp << line << endl; // Write the line to temp.txt
            } else {
                cout << "wrong input " << endl;
            }
        } else {
            temp << line << endl; // Write the line to temp.txt
        }
    }

    input.close(); // Close the input file after using it
    temp.close(); // Close the temp file after using it

    // Remove the old file
    remove("contact.txt");
    // Rename temp file to original file
    rename("temp.txt", "contact.txt");

    if (flag == 0) cout << "Record not found " << endl;
}

// Main function
int main() {
    clearScreen();
    setTextColor(14); // Set text color to yellow
    cout << "\n\t\t\t\t\t\tHISAAB MANAGEMENT SYSTEM";
    int choice1;
    int flag = 0;
    contact number;

    do {
        cout << "\n\n\t1.Admin\n\t2.Customer\n\t3.Exit" << endl;
        cout << "Enter the choice ";
        cin >> choice1;

        switch (choice1) {
        case 1:
            int key;
            cout << "enter the passcode of the admin ";
            cin >> key;

            if (key == 2987) {
                cout << "Access granted " << endl;
                flag = 1;
                number.admin_menu();
                break;
            } else {
                cout << "Access denied try again " << endl;
                flag = 0;
                break;
            }

        case 2:
            number.customer_menu();
            break;

        case 3:
            break;

        default:
            cout << "Enter the valid option" << endl;
        }

        if (flag == 1) break;

    } while (choice1 != 3);

    if (choice1 == 3) return 0;

    if (flag == 1) {
        int choice2;
        int flag1 = 0;
        do {
            system("cls");
            string Name;
            number.admin_menu();
            cout << "Enter the choice ";
            cin >> choice2;
            

            switch (choice2) {
            case 1:
                number.add_hisaab();
                break;

            case 2:
                cout << "Enter the Name to get the details : ";
                cin.ignore();
                getline(cin, Name);
                number.search(Name);
                break;

            case 3:
                number.show_hisaab();
                break;

            case 4:
                number.delete_hisaab();
                break; 
            
            case 5 :
                flag1 = 1;
                break;

            default:
                cout << "Enter a valid input" << endl;
            }

            if (flag1 == 1) break;
            
            char ans;
            cout << "Do you want to continue Y/N : ";
            cin >> ans;

            if (ans == 'Y') continue;
            if (ans == 'N') break;
            else cout << "Try again" << endl;

        } while (choice2 != 5);

    }
    return 0; 
}

/*
 UCSC Extension, C++ Comprehensive, Spring 2016
 Project #3
 Project Name: using of Linked-list to build a database to manage Employees
 input file name: tnDbaseProj3.txt
 Compiler: XCode Version 7.2, Mac OS 10.10.5
 Due Date: May 28, 2016
 Student: Truc Ngo
 truc.dinh.ngo@gmail.com
 */

#include <iostream>
#include <fstream>
#include <ctype.h> /* toupper() */
#include <cstring> /* atoi() */
#include <iomanip> /* setw() */
#include <cstdlib> /* atoi() */

using namespace std;
int loadDatabaseFile();
int readDatabaseFile();
string convert_tolowerCase(string input);
void convert_tolowerCase(char * input, int size);
void format_employee_name(char * input, int size);
string format_salary(int number);

enum EMPLOYEE_DATABASE_MENU {ADD_EMPLOYEE='A', DELETE_EMPLOYEE='D', SEARCH_EMPLOYEE='S',
    LIST_ALL_EMPLOYEES='L', SAVE_EMPLOYEE_DATABASE='W',
    EXIT_EMPLOYEE_DATABASE='E'};

class Node {
public:
    string name;
    int age;
    int salary;
    Node * next;
};

class Employee {
public:
    int buildDatabase(string databaseFilename);
    void displayControlPanel();
    void addOneEmployee();
    int deleteOneEmployee();
    void searchForOneEmployee();
    void listAllEmployees();
    int saveEmployeeDatabase(string databaseFilename);
    void exitEmployeeDatabase(Employee *EmpPtr);
private:
    Node * headPtr = NULL;
    Node * tailPtr = NULL;
};



/* Display the Control Panel of the Employee Database Application */
void Employee::displayControlPanel() {
    cout << endl << "Menu options: ";
    cout << endl << "1. A)DD_EMPLOYEE" << "\n" <<
    "2. D)ELETE_EMPLOYEE" << "\n" <<
    "3. S)EARCH_EMPLOYEE" << "\n" <<
    "4. L)IST_ALL_EMPLOYEES" << "\n" <<
    "5. W)SAVE_EMPLOYEE_DATABASE" << "\n" <<
    "6. E)XIT_EMPLOYEE_DATABASE";
    cout << endl << "Enter your choice: ";
}


/* Display all employees in database */
void Employee::listAllEmployees() {
    int counter = 1;
    cout << setw(5)  << left << "#" <<
    setw(40) << left << "Employee Name" <<
    setw(15) << left << "Age" <<
    setw(20) << left << "Salary" << endl;
    for (int i = 0; i <70; i++) {
        cout << "=";
    }
    cout << endl;
    
    Node *tempNode;
    tempNode = headPtr;
    if (tempNode == NULL) {
        cout << "Database is Empty.";
    }
    while (tempNode != NULL)
    {
        cout     << left << counter << setw(4) << "." <<
        setw(40) << left << tempNode->name <<
        setw(15) << left << tempNode->age <<
        setw(20) << left << format_salary(tempNode->salary) << endl;
        tempNode = tempNode->next;
        ++counter;
    }
}

/* Build up linked-list based on database text file */
int Employee::buildDatabase(string databaseName) {
    string record;
    string delimiter = ";";
    ifstream fileHandle;
    fileHandle.open(databaseName, ios::in);
    
    if (!fileHandle) {
        cout << "Cannot open: " << databaseName << endl;
        return 1;
    }

    while (!fileHandle.eof()) {
        getline(fileHandle, record);
        // Quick fix to handle case where the record contains newline character "endl"
        // which was saved to "end" of database by saveEmployeeDatabase()
        if (record.length() < 2) break;
        // {name = recordFields[0], age = recordFields[1], salary = recordFields[2]}
        string recordFields[3];
        size_t position = 0;
        for (int i=0; i<3; i++) {
            position = record.find(delimiter);
            recordFields[i] = record.substr(0, position);
            record.erase(0, position + delimiter.length());
        }
        Node * newNode = new Node;
        // If list is empty
        if (headPtr == NULL)
        {
            newNode->name = recordFields[0];
            newNode->age = std::atoi(recordFields[1].c_str());
            newNode->salary = std::atoi(recordFields[2].c_str());
            newNode->next = NULL;
            headPtr = tailPtr = newNode;
            headPtr->next = tailPtr;
            tailPtr->next = NULL;
        }
        // If list already has a head node
        else
        {
            newNode->name = recordFields[0];
            newNode->age = std::atoi(recordFields[1].c_str());
            newNode->salary = std::atoi(recordFields[2].c_str());
            // If newNode's name is "less" than that of the headNode then
            // Swap with headNode
            if ((headPtr->name).compare(newNode->name) > 0) {
                Node * currentNode = headPtr;
                newNode->next = headPtr;
                currentNode = newNode;
                newNode = headPtr;
                headPtr = currentNode;
            // If newNode's name > tailNode, add newNode after TailNode
            } else if ((newNode->name).compare(tailPtr->name) >= 0) {
                tailPtr->next = newNode;
                tailPtr = newNode;
            } else {
                Node *tempNode = headPtr;
                Node *previousNode = headPtr;
                while (tempNode != NULL) {
                    // If newNode's name is "less" than that of the currentNode
                    if ((newNode->name).compare(tempNode->name) <= 0) {
                        previousNode->next = newNode;
                        newNode->next = tempNode;
                        break;
                    // Continue iterating through the list
                    } else {
                        previousNode = tempNode;
                        tempNode = tempNode->next;
                    }
                }
            }
            /*
             This code section was for building linklist w/o sorting
             newNode->next = NULL;
             tailPtr->next = newNode;
             tailPtr = newNode;
             */
        }
    
    }
    fileHandle.close();
    return 0;
}


/* Search for an employee in database */
/* employeeName is case insensitive */
void Employee::searchForOneEmployee() {
    const int NAME_SIZE = 50;
    cin.clear();
    char employee_name[NAME_SIZE];
    cout << "Name of Employee you'd like to search (case insensitive): ";
    cin.get();
    //cin.get(employee_name, sizeof(employee_name));
    cin.getline(employee_name, sizeof(employee_name));
    cin.clear();
    
    // Search for employee
    Node *tempNode;
    tempNode = headPtr;
    
    while (tempNode != NULL)
    {
        if (convert_tolowerCase(tempNode->name) == convert_tolowerCase(employee_name)) {
            cout << employee_name << ": is found in database." << endl;
            cout << "Name = " << tempNode->name <<
            "; Age = " << tempNode->age <<
            "; Salary = " << tempNode->salary << endl;
            return;
        } else {
            tempNode = tempNode->next;
        }
    }
    cout << employee_name << ": is not found in database." << endl;
}

/* Add one employee to database */
void Employee::addOneEmployee() {
    const int NAME_SIZE = 50;
    char employee_name[NAME_SIZE];
    int age;
    int salary;
    cout << "Enter Name (case insensitive): ";
    // Used to dispose newLine char from the previous cin
    cin.get();
    cin.getline(employee_name, sizeof(employee_name));
    cin.clear();
    cout << "Enter Age: ";
    // No need to use cin.get() here because cin.getline() discards the new line char
    cin >> age;
    cout << "Enter Salary: ";
    // Used to dispose newLine char from the previous cin
    cin.get();
    cin >> salary;
    Node * previousNode = headPtr;
    Node * currentNode = headPtr;
    Node * newNode = new Node;
    format_employee_name(employee_name, NAME_SIZE);

    newNode->name = employee_name;
    newNode->age = age;
    newNode->salary = salary;
    newNode->next = NULL;
    
    // If database is empty
    if (headPtr == NULL && tailPtr == NULL) {
        headPtr = newNode;
        tailPtr = newNode;
    // If newNode's employee-name is alphabetically higher than that of tailNode
    } else if ((newNode->name).compare(tailPtr->name) >= 0) {
        tailPtr->next = newNode;
        tailPtr = newNode;
    // If newNode's employee-name is alphabetically lower than that of headNode
    // then swap headNode with newNode
    } else if ((newNode->name).compare(headPtr->name) < 0) {
        newNode->next = headPtr;
        currentNode = newNode;
        newNode = headPtr;
        headPtr = currentNode;
    // If newNode's employee-name is alphabetically higher than that of headNode
    // Keep moving the node pointer
    } else if ((newNode->name).compare(currentNode->name) >= 0) {
        // If newNode's field name is alphabetically higher than that of headNode
        // Keep moving the currentNode pointer until newNode is less than or equal to current pointer
        while ((newNode->name).compare(currentNode->name) >= 0) {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        // If newNode's employee name is now greater than currentNode's name
        Node * tempNode = previousNode->next;
        previousNode->next = newNode;
        newNode->next = tempNode;
    }
    cout << employee_name << ": has been added to database." << endl;
}

/* Delete one employee off the database;
 1./ Use employeeName as key
 2./ employeeName is case insensitive */
int Employee::deleteOneEmployee() {
    const int NAME_SIZE = 50;
    cin.clear();
    cout << "Name of Employee (case insensitive): ";
    char entered_name[NAME_SIZE];
    char copied_entered_name[NAME_SIZE];
    cin.get();
    cin.get(entered_name, sizeof(entered_name));
    cin.clear();
    // Save the name that you entered
    for (int i=0; i < NAME_SIZE; i++)
    {
        copied_entered_name[i] = (entered_name[i]);
    }
    // Convert name to lower case
    convert_tolowerCase(entered_name, NAME_SIZE);
    bool memberHasBeenDeleted = false;
    // Search for employee
    Node *currentNode, *previousNode;
    currentNode = headPtr;
    previousNode = headPtr;
    
    if (headPtr == NULL && tailPtr == NULL) {
        cout << "Database is empty!" << endl;
        return 0;
    }
    
    // If employee name is stored at the headNode
    if (convert_tolowerCase(currentNode->name) == entered_name) {
        headPtr = currentNode->next;
        delete currentNode;
        memberHasBeenDeleted = true;
        cout << copied_entered_name << ": has been deleted." << endl;
        if (headPtr == NULL) {
            tailPtr = NULL;
        }
    // Search for employee in the linkList
    } else {
        while (currentNode != NULL)
        {
            if (convert_tolowerCase(currentNode->name) == entered_name) {
                previousNode->next = currentNode->next;
                // Update tailNode after deletion of lastNode
                if (convert_tolowerCase(tailPtr->name) == entered_name) {
                    tailPtr = previousNode;
                }
                delete currentNode;
                cout << copied_entered_name << ": has been deleted." << endl;
                memberHasBeenDeleted = true;
                break;
            } else {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
        }
    }
    if (!memberHasBeenDeleted)
        cout << copied_entered_name << ": not found in database." << endl;
    return 0;
}

/* Save database to hard-disk */
int Employee::saveEmployeeDatabase(string databaseName) {
    char delimeter = ';';
    ofstream fileHandle;
    fileHandle.open(databaseName);
    
    if (!fileHandle) {
        cout << "Cannot open: " << databaseName << endl;
        return 1;
    }
    if (fileHandle) {
        Node * currentNode = headPtr;
        while (currentNode != NULL) {
            fileHandle << currentNode->name << delimeter <<
            currentNode->age << delimeter <<
            currentNode->salary << endl;
            currentNode = currentNode->next;
        }
    }
    cout << "Data has been saved to Database." << endl;
    fileHandle.close();
    return 0;
}


/* Clean up memory and Exit Program */
void Employee::exitEmployeeDatabase(Employee *EmpPtr) {
    Node *tempNode = headPtr;
    while (tempNode != NULL) {
        Node* nextNode = tempNode->next;
        delete tempNode;
        tempNode = nextNode;
    }
    headPtr = NULL;
    tailPtr = NULL;
    delete headPtr;
    delete tailPtr;
    delete EmpPtr;
}



/* MAIN PROGRAM */
/* How to compile this program: g++ -o output CppProject3.cpp */
/* How to execute: ./output database.txt */

int main(int argc, const char * argv[]) {
    ifstream fileHandler;
    Employee * employee = NULL;
    if (argc != 2) {
        cout << "Usage: database file as argument is required." << endl;
        return 1;
    } else {
        employee = new Employee();
    }
    
    cout << "Employee Management Database" << endl;
    char employeeControlCommand;
    employee->buildDatabase(argv[1]);
    employee->displayControlPanel();
    
    while (cin >> employeeControlCommand || !cin.eof()) {
        switch (toupper(employeeControlCommand)) {
            case ADD_EMPLOYEE:
                employee->addOneEmployee();
                employee->displayControlPanel();
                break;
            case DELETE_EMPLOYEE:
                employee->deleteOneEmployee();
                employee->displayControlPanel();
                break;
            case SEARCH_EMPLOYEE:
                employee->searchForOneEmployee();
                employee->displayControlPanel();
                break;
            case LIST_ALL_EMPLOYEES:
                employee->listAllEmployees();
                employee->displayControlPanel();
                break;
            case SAVE_EMPLOYEE_DATABASE:
                employee->saveEmployeeDatabase(argv[1]);
                employee->displayControlPanel();
                break;
            case EXIT_EMPLOYEE_DATABASE:
                employee->exitEmployeeDatabase(employee);
                return 0;
            default:
                cout << endl << "Please enter an valid command! Now Try again." << endl;
                cout << endl << "Enter your choice: ";
        }
    }
}

/* Load database file */
/* This code section is for Debug purposes */
int loadDatabaseFile() {
    ofstream fileHandle("tnDbase.txt");
    if (!fileHandle) {
        cout << endl << "Cannot open output file!";
        return 1;
    }
    fileHandle << "Patrick Stroud;48;140565" << endl;
    fileHandle << "Ursula Spencer;27;36450" << endl;
    fileHandle << "Clifton Stillman;65;99900" << endl;
    fileHandle << "William Reynolds;37;77550" << endl;
    fileHandle << "Dean Niles;53;120000" << endl;
    fileHandle << "John Kaufman;53;69597" << endl;
    fileHandle << "Paul Kane;51;169650" << endl;
    fileHandle << "Paul Goldsmith;60;200000" << endl;
    fileHandle << "Larry Godwin;45;59500" << endl;
    fileHandle << "Kurt Lamm;39;90000" << endl;
    fileHandle << "Susan Carltom;42;85000" << endl;
    fileHandle << "Cameron Wu;29;50589";
    
    fileHandle.close();
    return 0;
}

/* Read database file */
/* This code section is for Debug purposes */
/* References:
 https://linuxconfig.org/c-code-on-how-to-read-characters-from-a-file
 */

int readDatabaseFile() {
    ifstream fileHandle;
    fileHandle.open("tnDbase.txt", ios::in);
    if (!fileHandle) {
        cout << endl <<"Cannot open file!";
        return 1;
    }
    char ch;
    while (!fileHandle.eof()) {
        fileHandle.get(ch);
        cout << ch;
    }
    fileHandle.close();
    return 0;
}

/* Convert a string to lower case: string as input */
string convert_tolowerCase (string inputString) {
    for (int i = 0; inputString[i] != '\0'; ++i)
        inputString[i] = tolower(inputString[i]);
    return inputString;
}

/* Convert a string to lower case: character array as input */
void convert_tolowerCase (char * input, int size) {
    for (int i=0; i < size; i++)
    {
        input[i] = tolower(input[i]);
    }
}

/* Format name of employee after user typed in to conform to format of database */
/* ie. "jOhN smiTh" will be converted to "John Smith" */
/* to be used in addOneEmployee() */
void format_employee_name(char * input, int size) {
    // Converty all character to lower case
    for (int i=0; i < size; i++)
    {
        input[i] = tolower(input[i]);
    }
    // Convert first character to upperCase
    input[0] = toupper(input[0]);
    // Find the last "space" location
    int first_space_char_marker = 0;
    for (int i = 1; i < size; i++) {
        if (input[i] == char(32)) {
            first_space_char_marker = i;
            //break; - without break, it will return the first "space" location
        }
    }
    // Convert to upperCase the next non-space character
    for (int i = first_space_char_marker; i < size; i++) {
        if (input[i] != char(32)) {
            input[i] = toupper(input[i]);
            break;
        }
    }
}

/* format salary with ",' for each 1000 */
/* ie., 1000000000 will become 1,000,000,000 */
string format_salary(int number) {
    const string decimal_delimeter = ".";
    // number->string->char array
    string number_as_string = to_string(number);
    const char * number_as_char_ptr = number_as_string.c_str();
    size_t number_of_character_in_string = strlen(number_as_char_ptr);
    
    // If there is at least 4 chars
    if (number_of_character_in_string > 3) {
        // 8 % 3 = 2; remainder = 2
        int remainder = number_of_character_in_string % 3;
        // Create a new String that contains the first 2 chars
        // 12345778 -> 12
        string formatted_number_as_string =  number_as_string.substr(0, remainder);
        if ((number_of_character_in_string % 3) != 0)
            formatted_number_as_string.append(",");
        // Create a new String
        // 12345678 -> 345678
        string temp_number = number_as_string.substr(remainder, number_as_string.length());
        const char * numberPtr2 = temp_number.c_str();
        int counter = 0;
        int delimeter_counter = 1;
        for (int i = 0; numberPtr2[i] != '\0'; i++) {
            counter++;
            formatted_number_as_string.append(string(1, numberPtr2[i]));
            if ((i != 0) && (counter%3 == 0) && (delimeter_counter < int(number_of_character_in_string/3))) {
                delimeter_counter++;
                formatted_number_as_string.append(",");
            }
        }
        return formatted_number_as_string;
    }
    return number_as_string;
}


/* testcase1: delete a node at the bottom - then add a node at the bottom
testcase2: add 2 employees with the same name - then delete both of them - then add a new employee - then view the list */
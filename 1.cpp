 #include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

class student
{
private:
    int id;
    string name;
    int age;
    string course;

public:
    void menu();
    void addRecord();
    void displayRecord();
    void modifyRecord();
    void searchRecord();
    void deleteRecord();
};

// ================= MENU =================

void student::menu()
{
    int choice;

    do
    {
        cout << "\n\t\t====================================" << endl;
        cout << "\t\t       STUDENT MANAGEMENT SYSTEM" << endl;
        cout << "\t\t====================================" << endl;

        cout << "\t\t1. Enter New Record" << endl;
        cout << "\t\t2. Display Record" << endl;
        cout << "\t\t3. Modify Record" << endl;
        cout << "\t\t4. Search Record" << endl;
        cout << "\t\t5. Delete Record" << endl;
        cout << "\t\t6. Exit" << endl;

        cout << "\n\t\tEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addRecord();
                break;

            case 2:
                displayRecord();
                break;

            case 3:
                modifyRecord();
                break;

            case 4:
                searchRecord();
                break;

            case 5:
                deleteRecord();
                break;

            case 6:
                cout << "\n\t\tThank you!" << endl;
                break;

            default:
                cout << "\n\t\tInvalid choice!" << endl;
        }

    } while(choice != 6);
}

// ================= ADD RECORD =================

void student::addRecord()
{
    cout << "\n\t\t===== ENTER NEW RECORD =====" << endl;

    cout << "\t\tEnter Student ID: ";
    cin >> id;

    cin.ignore();

    cout << "\t\tEnter Student Name: ";
    getline(cin, name);

    cout << "\t\tEnter Age: ";
    cin >> age;

    cin.ignore();

    cout << "\t\tEnter Course: ";
    getline(cin, course);

    ofstream file("students.txt", ios::app);

    if(!file)
    {
        cout << "\n\t\tFile could not be opened!" << endl;
        return;
    }

    file << id << "|" << name << "|" << age << "|" << course << endl;

    file.close();

    cout << "\n\t\tRecord Added Successfully!" << endl;
}

// ================= DISPLAY RECORD =================

void student::displayRecord()
{
    ifstream file("students.txt");

    if(!file)
    {
        cout << "\n\t\tNo records found!" << endl;
        return;
    }

    string line;
    bool found = false;

    cout << "\n\t\t========== STUDENT RECORDS ==========" << endl;

    while(getline(file, line))
    {
        if(line.empty())
            continue;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        if(p1 == string::npos ||
           p2 == string::npos ||
           p3 == string::npos)
        {
            continue;
        }

        id = stoi(line.substr(0, p1));
        name = line.substr(p1 + 1, p2 - p1 - 1);
        age = stoi(line.substr(p2 + 1, p3 - p2 - 1));
        course = line.substr(p3 + 1);

        cout << "\n\t\tStudent ID : " << id << endl;
        cout << "\t\tName       : " << name << endl;
        cout << "\t\tAge        : " << age << endl;
        cout << "\t\tCourse     : " << course << endl;

        cout << "\t\t------------------------------------" << endl;

        found = true;
    }

    file.close();

    if(!found)
    {
        cout << "\n\t\tNo records found!" << endl;
    }
}

// ================= MODIFY RECORD =================

void student::modifyRecord()
{
    int searchID;
    bool found = false;

    cout << "\n\t\t===== MODIFY RECORD =====" << endl;

    cout << "\t\tEnter Student ID: ";
    cin >> searchID;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if(!file)
    {
        cout << "\n\t\tNo records found!" << endl;
        return;
    }

    string line;

    while(getline(file, line))
    {
        if(line.empty())
            continue;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        if(p1 == string::npos ||
           p2 == string::npos ||
           p3 == string::npos)
        {
            continue;
        }

        int fileID = stoi(line.substr(0, p1));

        if(fileID == searchID)
        {
            found = true;

            id = fileID;

            cin.ignore();

            cout << "\t\tEnter New Name: ";
            getline(cin, name);

            cout << "\t\tEnter New Age: ";
            cin >> age;

            cin.ignore();

            cout << "\t\tEnter New Course: ";
            getline(cin, course);

            temp << id << "|" << name << "|" << age << "|" << course << endl;
        }
        else
        {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        cout << "\n\t\tRecord Modified Successfully!" << endl;
    else
        cout << "\n\t\tStudent ID not found!" << endl;
}

// ================= SEARCH RECORD =================

void student::searchRecord()
{
    int searchID;
    bool found = false;

    cout << "\n\t\t===== SEARCH RECORD =====" << endl;

    cout << "\t\tEnter Student ID: ";
    cin >> searchID;

    ifstream file("students.txt");

    if(!file)
    {
        cout << "\n\t\tNo records found!" << endl;
        return;
    }

    string line;

    while(getline(file, line))
    {
        if(line.empty())
            continue;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        if(p1 == string::npos ||
           p2 == string::npos ||
           p3 == string::npos)
        {
            continue;
        }

        int fileID = stoi(line.substr(0, p1));

        if(fileID == searchID)
        {
            id = fileID;
            name = line.substr(p1 + 1, p2 - p1 - 1);
            age = stoi(line.substr(p2 + 1, p3 - p2 - 1));
            course = line.substr(p3 + 1);

            cout << "\n\t\tRecord Found!" << endl;
            cout << "\t\tStudent ID : " << id << endl;
            cout << "\t\tName       : " << name << endl;
            cout << "\t\tAge        : " << age << endl;
            cout << "\t\tCourse     : " << course << endl;

            found = true;
            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\n\t\tStudent ID not found!" << endl;
    }
}

// ================= DELETE RECORD =================

void student::deleteRecord()
{
    int deleteID;
    bool found = false;

    cout << "\n\t\t===== DELETE RECORD =====" << endl;

    cout << "\t\tEnter Student ID: ";
    cin >> deleteID;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if(!file)
    {
        cout << "\n\t\tNo records found!" << endl;
        return;
    }

    string line;

    while(getline(file, line))
    {
        if(line.empty())
            continue;

        size_t p1 = line.find('|');

        if(p1 == string::npos)
            continue;

        int fileID = stoi(line.substr(0, p1));

        if(fileID == deleteID)
        {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if(found)
        cout << "\n\t\tRecord Deleted Successfully!" << endl;
    else
        cout << "\n\t\tStudent ID not found!" << endl;
}

// ================= MAIN =================

int main()
{
    student project;

    project.menu();

    return 0;
}
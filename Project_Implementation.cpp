#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <vector>

using namespace std;

vector<string>search(string filename, string searchterm);
string line;
void showmenu();
void regist();
void messStatus();
void eraseFileLine();
vector<string>totalBill();
string totalInOut();
void sort();

int main()
{
    int option;
    char choice;
    vector<string> data;
    string reg;
    do {
        showmenu();
        cout << "Enter Option" << endl;
        cin >> option;

        switch (option)
        {
        case 1:
            regist();
            break;
        case 2:
            cout << "Enter reg to search:";
            cin >> reg;
            data = search("data.csv", reg);
            break;
        case 3:messStatus();
            break;
        case 4: eraseFileLine();
            break;
        case 5:totalInOut();
            break;
        case 6:totalBill();
            break;
        default:
            cout << "No such option available" << endl;
            break;
        }
        cout << "Do you want to perform any other function(Y/N): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    cout << "Thanks for using the App" << endl;
}

void showmenu()
{
    cout << "****************************************" << endl;
    cout << "1.Register a new student " << endl;
    cout << "2.Search a student record " << endl;
    cout << "3.Change student mess status (In/Out) " << endl;
    cout << "4.Delete a student record " << endl;
    cout << "5.Show a total number of In/Out students. " << endl;
    cout << "6.Calculate total bill. " << endl;
    cout << "****************************************" << endl;

}

void regist()
{
    fstream file;
    string name;
    string reg;
    string status;
    file.open("data.csv");

    string days = "0", bill = "0";

    cout << "Enter Reg number: " << endl;
    cin >> reg;

    vector<string>record;
    bool found_record = false;
    string field_one;
    string field_two;
    string field_three;
    string field_four;
    string field_five;

    while (getline(file, field_one, ',') && !found_record)
    {
        getline(file, field_two, ',');
        getline(file, field_three, ',');
        getline(file, field_four, ',');
        getline(file, field_five, '\n');

        if (field_one == reg)
        {
            found_record = true;
            record.push_back(field_one);
            record.push_back(field_two);
            record.push_back(field_three);
            record.push_back(field_four);
            record.push_back(field_five);
        }


    }
    file.close();
    file.open("data.csv", ios::app);
    if (found_record)
    {

        cout << "Reg No: " << record[0] << " is already registered" << endl;

    }
    else
    {

        cout << "Enter Student's name: " << endl;
        cin.ignore();
        getline(cin, name);
        cout << "Enter in/out status" << endl;
        cin >> status;
        cout << endl;

        if (status == "in" || status == "In")
        {
            days = "1";
            bill = "300";
        }

        if (!file.is_open())
        {
            cout << "error";
        }
        else
        {
            file << reg << "," << name << "," << bill << "," << status << "," << days << "," << endl;
            cout << "Updated Successfuly" << endl;
            file.close();
            sort();
        }
    }
}

vector<string>search(string filename, string searchterm)
{
    vector<string>record;
    ifstream file;
    file.open("data.csv");

    bool found_record = false;
    string field_one;
    string field_two;
    string field_three;
    string field_four;
    string field_five;

    while (getline(file, field_one, ',') && !found_record)
    {
        getline(file, field_two, ',');
        getline(file, field_three, ',');
        getline(file, field_four, ',');
        getline(file, field_five, '\n');

        if (field_one == searchterm)
        {
            found_record = true;
            record.push_back(field_one);
            record.push_back(field_two);
            record.push_back(field_three);
            record.push_back(field_four);
            record.push_back(field_five);
        }

    }
    if (found_record)
        cout << "Reg No: " << record[0] << " Name: " << record[1] << " Bill: " << record[2] << " Status: " << record[3] << " Days: " << record[4] << endl;
    else
        cout << "No record found,Student needs to be registered " << endl;
    return record;

}

void messStatus()
{
    string searchterm;
    fstream file;
    char choice;
    string status;

    cout << "Enter reg to view status: ";
    cin >> searchterm;

    bool found_record = false;


    string word, line;
    vector<vector<string> > arr;
    vector<string> row_data;
    fstream file1("data.csv", ios::in);
    while (getline(file1, line))
    {
        row_data.clear();
        stringstream str(line);
        while (getline(str, word, ','))
        {
            row_data.push_back(word);
        }
        arr.push_back(row_data);
    }

    int rows = arr.size();
    int index = 0;

    for (int i = 0; i < rows; i++) {
        if (arr[i][0] == searchterm) {
            found_record = true;
            index = i;
        }
    }

    if (found_record) {
        cout << "Status: " << arr[index][3] << endl;
        cout << "Do you want to change the mess status(Y/N)" << endl;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            cout << "What status do you want" << endl;
            cin >> status;
            if (status == arr[index][3])
                cout << "Status is already " << status << endl;
            else {
                if (status == "in" || status == "In") {
                    arr[index][3] = status;


                    int num = stoi(arr[index][2]);
                    num = num + 300;

                    stringstream number;
                    number << num;
                    arr[index][2] = number.str();

                    int days = stoi(arr[index][4]);
                    days++;

                    stringstream day;
                    day << days;
                    arr[index][4] = day.str();

                    cout << "Updated." << endl;
                }
                else if (status == "out" || status == "Out") {
                    arr[index][3] = status;
                    cout << "Updated" << endl;
                }
                else {
                    cout << "Not a valid status." << endl;
                }
            }
        }
        else
        {
            cout << "Thanks" << endl;
        }
    }
    else
    {
        cout << "No record found" << endl;
    }

    fstream fout;

    fout.open("newdata.csv", ios::out);


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fout << arr[i][j] << ",";
        }
        fout << "\n";
    }

    file1.close();
    fout.close();

    remove("data.csv");
    rename("newdata.csv", "data.csv");

}

void sort()
{
    string word, line;
    vector<vector<string>> arr;
    vector<string> row_data;
    fstream file("data.csv", ios::in);
    while (getline(file, line))
    {
        row_data.clear();
        stringstream str(line);
        while (getline(str, word, ','))
        {
            row_data.push_back(word);
        }
        arr.push_back(row_data);
    }

    int rows = arr.size();

    for (int i = 1; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = i + 1; k < rows; k++)
            {
                if (arr[i][0] > arr[k][0])
                {
                    string temp = arr[i][0];
                    arr[i][0] = arr[k][0];
                    arr[k][0] = temp;


                    string temp1 = arr[i][1];
                    arr[i][1] = arr[k][1];
                    arr[k][1] = temp1;



                    string temp2 = arr[i][2];
                    arr[i][2] = arr[k][2];
                    arr[k][2] = temp2;



                    string temp3 = arr[i][3];
                    arr[i][3] = arr[k][3];
                    arr[k][3] = temp3;

                    string temp4 = arr[i][4];
                    arr[i][4] = arr[k][4];
                    arr[k][4] = temp4;

                }
            }
        }
    }

    fstream fout;

    fout.open("newdata.csv", ios::out);


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            fout << arr[i][j] << ",";
        }
        fout << "\n";
    }

    file.close();
    fout.close();

    remove("data.csv");
    rename("newdata.csv", "data.csv");
}


void eraseFileLine() {
    string line, reg;
    cout << "Please Enter the reg you want to delete: ";
    cin >> reg;
    ifstream myfile;
    myfile.open("data.csv");
    ofstream temp;
    temp.open("temp.csv");
    while (getline(myfile, line))
    {
        if (line.substr(0, reg.size()) != reg)
            temp << line << endl;
    }
    cout << "The record with the reg: " << reg << " has been deleted " << endl;
    myfile.close();
    temp.close();
    remove("data.csv");
    rename("temp.csv", "data.csv");
}

vector<string>totalBill()
{
    vector<string>record;
    string searchterm;
    ifstream file;
    file.open("data.csv");
    cout << "Enter reg to view Bill: ";
    cin >> searchterm;
    bool found_record = false;
    string field_one;
    string field_two;
    string field_three;
    string field_four;
    string field_five;

    while (getline(file, field_one, ',') && !found_record)
    {
        getline(file, field_two, ',');
        getline(file, field_three, ',');
        getline(file, field_four, ',');
        getline(file, field_five, '\n');

        if (field_one == searchterm)
        {
            found_record = true;
            record.push_back(field_one);
            record.push_back(field_two);
            record.push_back(field_three);
            record.push_back(field_four);
            record.push_back(field_five);
        }

    }
    if (found_record)
        cout << "Total Bill is : " << record[2] << endl;
    else {
        cout << "No record found" << endl;
    }

    return record;

}

string totalInOut()
{
    int inCount = 0, outCount = 0;


    string word, line;
    vector<vector<string>> arr;
    vector<string> row_data;
    fstream file("data.csv", ios::in);
    while (getline(file, line))
    {
        row_data.clear();
        stringstream str(line);
        while (getline(str, word, ','))
        {
            row_data.push_back(word);
        }
        arr.push_back(row_data);
    }

    int rows = arr.size();


    for (int i = 1; i < rows; i++)
    {

        if (arr[i][3] == "in")
        {
            inCount++;
        }
        else if (arr[i][3] == "out")
        {
            outCount++;
        }

    }

    cout << "Total number of in student are " << inCount << endl;
    cout << "Total number of out students " << outCount << endl;

    return line;
}

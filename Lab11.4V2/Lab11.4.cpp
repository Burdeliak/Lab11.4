#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

// ������� ��� �������� ���� ����� � ���������
string getFileName() {
    string fileName;
    cout << "Enter the file name (default is 'AVTO'): ";
    cin >> fileName;
    if (fileName.empty()) {
        fileName = "AVTO";
    }
    return fileName;
}

// ������� ��� ��������� ������ ��� ����� �� �������� � ����
void addCarRecord(const string& fileName) {
    ofstream file(fileName, ios::app); // ³������� ����� ��� ������ � ����
    if (!file.is_open()) {
        cerr << "Error opening the file!" << endl;
        return;
    }

    string company, carModel;
    double price;
    cout << "Enter the company name: ";
    cin.ignore();
    getline(cin, company);

    file << company;

    char choice;
    do {
        cout << "Enter the car model: ";
        getline(cin, carModel);
        cout << "Enter the car price: ";
        while (!(cin >> price)) {
            cin.clear(); // ������� ���� ������
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // �������� ����������� ���
            cout << "Invalid input! Please enter a numeric value for the price: ";
        }
        file << " " << carModel << " " << price;

        cout << "Do you want to add another car? (y/n): ";
        cin >> choice;
        cin.ignore(); // �������� ������

    } while (choice == 'y' || choice == 'Y');

    file << endl;
    file.close();
    cout << "Record added to the file." << endl;
}

// ������� ��� ���������� �� ������ ����������� ���� ����� ����� � ����� ����
void findAndRecordMaxPrices(const string& inputFileName, const string& outputFileName) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening files!" << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string company, carModel;
        double price, maxPrice = -1;
        bool isFirstEntry = true;

        iss >> company; // ������� ����� �����
        outputFile << company;

        while (iss >> carModel >> price) {
            outputFile << " " << carModel << " " << price;
            if (isFirstEntry || price > maxPrice) {
                maxPrice = price;
                isFirstEntry = false;
            }
        }

        if (!isFirstEntry) {
            outputFile << " Max price: " << maxPrice;
        }

        outputFile << endl;
    }

    inputFile.close();
    outputFile.close();
    cout << "Maximum prices recorded in file: " << outputFileName << endl;
}

// ���� ��������
void menu() {
    string fileName, outputFileName;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Enter car data\n";
        cout << "2. Find the maximum price for each company and save to a new file\n";
        cout << "3. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            fileName = getFileName();
            addCarRecord(fileName);
            break;
        case 2:
            cout << "Enter the input file name: ";
            cin >> fileName;
            cout << "Enter the output file name: ";
            cin >> outputFileName;
            findAndRecordMaxPrices(fileName, outputFileName);
            break;
        case 3:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}

// ������� �������
int main() {
    menu();
    return 0;
}

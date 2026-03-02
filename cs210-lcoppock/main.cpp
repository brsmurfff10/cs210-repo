#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <cctype>

using namespace std;

class ItemTracker {
public:
    ItemTracker(const string& inputFileName) {
        LoadData(inputFileName);
        WriteBackupFile("frequency.dat");
    }

    int GetItemFrequency(const string& item) const {
        string key = ToLower(item);
        auto it = itemFrequency.find(key);
        if (it != itemFrequency.end()) {
            return it->second;
        }
        return 0;
    }

    void PrintAllFrequencies() const {
        for (const auto& pair : itemFrequency) {
            cout << Capitalize(pair.first) << " " << pair.second << endl;
        }
    }

    void PrintHistogram() const {
        for (const auto& pair : itemFrequency) {
            cout << Capitalize(pair.first) << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

private:
    map<string, int> itemFrequency;

    void LoadData(const string& inputFileName) {
        ifstream inputFile(inputFileName);
        if (!inputFile.is_open()) {
            cerr << "ERROR: Could not open input file: " << inputFileName << endl;
            return;
        }

        string item;
        while (inputFile >> item) {
            item = ToLower(item);
            itemFrequency[item]++;
        }

        inputFile.close();
    }

    void WriteBackupFile(const string& backupFileName) const {
        ofstream outFile(backupFileName);
        if (!outFile.is_open()) {
            cerr << "ERROR: Could not create backup file: " << backupFileName << endl;
            return;
        }

        for (const auto& pair : itemFrequency) {
            outFile << Capitalize(pair.first) << " " << pair.second << endl;
        }

        outFile.close();
    }

    static string ToLower(const string& s) {
        string result = s;
        for (char& c : result) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }

    static string Capitalize(const string& s) {
        if (s.empty()) return s;
        string result = s;
        result[0] = static_cast<char>(toupper(static_cast<unsigned char>(result[0])));
        return result;
    }
};

// --- MENU --- //
void PrintMenu() {
    cout << "\nGrocery Item Tracker Tool\n";
    cout << "1. Look up item frequency\n";
    cout << "2. Print all item frequencies\n";
    cout << "3. Print histogram\n";
    cout << "4. Exit\n";
    cout << "Enter your choice (1-4): ";
}

int GetValidatedChoice() {
    int choice;
    while (true) {
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number 1-4: ";
        }
        else {
            return choice;
        }
    }
}

int main() {
    ItemTracker tracker("CS210_Project_Three_Input_File.txt"); // input file name here (modified for submission)

    while (true) {
        PrintMenu();
        int choice = GetValidatedChoice();

        if (choice == 1) {
            cout << "Enter the item to look for: ";
            string item;
            getline(cin, item);

            int freq = tracker.GetItemFrequency(item);
            cout << item << " appears " << freq << " time(s)." << endl;
        }
        else if (choice == 2) {
            cout << "\nItem Frequencies:\n";
            tracker.PrintAllFrequencies();
        }
        else if (choice == 3) {
            cout << "\nHistogram:\n";
            tracker.PrintHistogram(); // print histogram of item frequencies
        }
        else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        }
    }

    return 0;
}
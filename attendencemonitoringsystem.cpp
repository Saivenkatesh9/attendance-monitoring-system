#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

class AttendanceSystem {
private:
    string filename;

public:
    AttendanceSystem(const string& file) : filename(file) {}

    void markAttendance(const string& studentID) {
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        string dateTime(buffer);

        ofstream outFile(filename, ios::app);

        if (!outFile) {
            cerr << "Error opening file." << endl;
            return;
        }

        outFile << studentID << "," << dateTime << endl;

        outFile.close();

        cout << "Attendance marked successfully for " << studentID << " at " << dateTime << endl;
    }

    void displayAttendanceReport(const string& studentID) {
        ifstream inFile(filename);

        if (!inFile) {
            cerr << "Error opening file." << endl;
            return;
        }

        string line;
        int count = 0;

        while (getline(inFile, line)) {
            size_t pos = line.find(studentID);
            if (pos != string::npos) {
                cout << line << endl;
                count++;
            }
        }

        cout << "Total attendance records for " << studentID << ": " << count << endl;

        inFile.close();
    }
};

int main() {
    AttendanceSystem attendanceSystem("attendance.txt");

    int choice;
    string studentID;

    do {
        cout << "\nAttendance Monitoring System\n";
        cout << "1. Mark Attendance\n";
        cout << "2. Display Attendance Report\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Student ID: ";
                cin >> studentID;
                attendanceSystem.markAttendance(studentID);
                break;
            case 2:
                cout << "Enter Student ID: ";
                cin >> studentID;
                attendanceSystem.displayAttendanceReport(studentID);
                break;
            case 3:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 3);

    return 0;
}

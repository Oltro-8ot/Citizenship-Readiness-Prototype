// main.cpp
#include <iostream>
#include <fstream>
#include <limits>
#include <ctime>
#include <cstdlib>

#include "Quiz.h"
#include "StudyGuide.h"

using namespace std;

void viewHistory() {
    ifstream fin("history.txt");
    if (!fin) {
        cout << "\nNo score history found yet.\n";
        return;
    }

    cout << "\n===== SCORE HISTORY =====\n\n";

    string line;
    while (getline(fin, line))
        cout << line << "\n";

    fin.close();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Quiz quiz("questions.txt", 10);

    bool running = true;
    while (running) {
        cout << "\n==== U.S. NATURALIZATION STUDY SYSTEM ====\n";
        cout << "1. Study Guide (10 random questions)\n";
        cout << "2. Free Response Quiz\n";
        cout << "3. Multiple Choice Quiz\n";
        cout << "4. View Score History\n";   // NEW OPTION
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                StudyGuide sg(quiz.getAllData(), quiz.getTotalQuestions(), 10);
                sg.run();
                break;
            }
            case 2:
                quiz.startFreeResponseQuiz();
                break;

            case 3:
                quiz.startMultipleChoiceQuiz();
                break;

            case 4:
                viewHistory();
                break;

            case 5:
                cout << "Good luck on your naturalization journey!\n";
                running = false;
                break;

            default:
                cout << "Invalid choice.\n";
                break;
        }
    }

    return 0;
}

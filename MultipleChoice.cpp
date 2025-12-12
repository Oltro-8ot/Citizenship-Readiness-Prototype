// MultipleChoice.cpp
#include "MultipleChoice.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MultipleChoiceQuestion::MultipleChoiceQuestion(const QuestionData& data,
                                               QuestionData* pool,
                                               int poolSize)
    : Question(data.question, data.answer) {

    // First, put correct answer in position 0
    options[0] = data.answer;

    // Pick 3 random *different* wrong answers from pool
    int chosen[3] = { -1, -1, -1 };
    int count = 0;

    while (count < 3 && poolSize > 1) {
        int idx = rand() % poolSize;
        // don't use its own answer and no duplicates
        if (pool[idx].answer != answer) {
            bool already = false;
            for (int i = 0; i < count; i++) {
                if (chosen[i] == idx) {
                    already = true;
                    break;
                }
            }
            if (!already) {
                chosen[count] = idx;
                options[count + 1] = pool[idx].answer;
                count++;
            }
        }
    }

    // If not enough distractors (weird case), fill with generic ones
    for (int i = 1; i < 4; i++) {
        if (options[i].empty()) {
            options[i] = "None of the above";
        }
    }

    // Now shuffle options and track correctIndex
    shuffleOptions();
}

void MultipleChoiceQuestion::shuffleOptions() {
    // simple shuffle using swaps
    // but track where the correct answer goes
    // Initially, options[0] is the correct answer
    string correctAns = options[0];

    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        string temp = options[i];
        options[i] = options[j];
        options[j] = temp;
    }

    // find the index of the correct answer
    correctIndex = 0;
    for (int i = 0; i < 4; i++) {
        if (options[i] == correctAns) {
            correctIndex = i;
            break;
        }
    }
}

bool MultipleChoiceQuestion::ask() {
    cout << "\nQUESTION (Multiple Choice):\n";
    cout << text << "\n";

    char labels[4] = { 'A', 'B', 'C', 'D' };
    for (int i = 0; i < 4; i++) {
        cout << labels[i] << ") " << options[i] << "\n";
    }

    cout << "Enter your choice (A-D): ";
    string input;
    getline(cin, input);

    if (input.empty()) {
        cout << "Invalid input.\n";
        cout << "Correct answer: " << answer << "\n";
        return false;
    }

    char c = toupper(static_cast<unsigned char>(input[0]));
    int idx = -1;
    if (c == 'A') idx = 0;
    else if (c == 'B') idx = 1;
    else if (c == 'C') idx = 2;
    else if (c == 'D') idx = 3;

    if (idx == -1) {
        cout << "Invalid choice.\n";
        cout << "Correct answer: " << answer << "\n";
        return false;
    }

    if (idx == correctIndex) {
        cout << "Correct!\n";
        return true;
    } else {
        cout << "Incorrect.\nCorrect answer: " << answer << "\n";
        return false;
    }
}

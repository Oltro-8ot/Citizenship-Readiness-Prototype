// StudyGuide.cpp
#include "StudyGuide.h"
#include <iostream>
#include <cstdlib>

using namespace std;

StudyGuide::StudyGuide(QuestionData* d, int total, int countToShow)
    : data(d), totalQuestions(total), showCount(countToShow) {
    if (showCount > totalQuestions) showCount = totalQuestions;
}

void StudyGuide::shuffleIndices(int* indices, int size) {
    for (int i = 0; i < size; i++) {
        int j = rand() % size;
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
}

void StudyGuide::run() {
    if (!data || totalQuestions == 0) {
        cout << "No study questions loaded.\n";
        return;
    }

    int* indices = new int[totalQuestions];
    for (int i = 0; i < totalQuestions; i++) {
        indices[i] = i;
    }

    shuffleIndices(indices, totalQuestions);

    cout << "\n===== STUDY GUIDE MODE =====\n";
    cout << "You will see " << showCount << " random questions.\n";

    for (int i = 0; i < showCount; i++) {
        int idx = indices[i];
        cout << "\nStudy Question " << (i + 1) << ":\n";
        cout << data[idx].question << "\n";
        cout << "Answer: ";
        string dummy;
        getline(cin, dummy);

        cout << "Answer: " << data[idx].answer << "\n";

        cout << "Type 'next' and press ENTER to continue, or 'q' to quit: ";
        string cmd;
        getline(cin, cmd);
        if (!cmd.empty() && (cmd[0] == 'q' || cmd[0] == 'Q')) {
            break;
        }
    }

    delete[] indices;
}

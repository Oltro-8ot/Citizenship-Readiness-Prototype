// Quiz.cpp
// Implements Quiz class: loads questions, runs quizzes, uses recursion,
// saves score history, and supports both free-response and multiple-choice.

#include "Quiz.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

// -------------------------------------------------------------
// Constructor loads the questions from file into a dynamic array
// -------------------------------------------------------------
Quiz::Quiz(const string& filename, int quizCount)
    : allData(nullptr), totalQuestions(0), numQuizQuestions(quizCount) 
{
    loadFromFile(filename);

    // Make sure quizCount does not exceed number of questions
    if (numQuizQuestions > totalQuestions) {
        numQuizQuestions = totalQuestions;
    }
}

// -------------------------------------------------------------
// Destructor: clean up dynamically allocated question data
// -------------------------------------------------------------
Quiz::~Quiz() {
    delete[] allData;
}

// -------------------------------------------------------------
// Load questions from file "Q: ...", "A: ..."
// Stores each in QuestionData array (up to 50 questions)
// -------------------------------------------------------------
void Quiz::loadFromFile(const string& filename) {
    ifstream fin(filename.c_str());
    if (!fin) {
        cout << "Could not open questions file: " << filename << "\n";
        return;
    }

    int capacity = 50;
    allData = new QuestionData[capacity];
    totalQuestions = 0;

    string line;
    string q, a;

    // File format:
    // Q: What is the supreme law?
    // A: The Constitution
    //
    // Blank line between entries optional
    while (getline(fin, line)) {

        // Check if this line starts with “Q:”
        if (line.rfind("Q:", 0) == 0) {
            q = line.substr(2);  // remove "Q:"

            // Next line should be the answer
            if (getline(fin, line) && line.rfind("A:", 0) == 0) {
                a = line.substr(2); // remove "A:"

                if (totalQuestions < capacity) {
                    allData[totalQuestions].question = q;
                    allData[totalQuestions].answer   = a;
                    totalQuestions++;
                }
            }
        }
    }

    fin.close();

    if (totalQuestions == 0) {
        cout << "No questions loaded from file.\n";
    } else {
        cout << "Loaded " << totalQuestions << " questions from file.\n";
    }
}

// -------------------------------------------------------------
// Simple shuffle: swaps random indices in array
// -------------------------------------------------------------
void Quiz::shuffleIndices(int* indices, int size) {
    for (int i = 0; i < size; i++) {
        int j = rand() % size;
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
}

// -------------------------------------------------------------
// Recursively ask each question and return total correct answers
// -------------------------------------------------------------
int Quiz::runRecursive(Question** arr, int index, int total) {
    if (index == total) {
        return 0; // base case
    }

    bool correct = arr[index]->ask();
    int add = correct ? 1 : 0;

    return add + runRecursive(arr, index + 1, total);
}

// -------------------------------------------------------------
// FREE RESPONSE QUIZ
// Creates dynamic FreeResponseQuestion objects,
// asks 10 randomized questions using recursion,
// prints and saves score history.
// -------------------------------------------------------------
void Quiz::startFreeResponseQuiz() {

    if (totalQuestions == 0) {
        cout << "No questions available.\n";
        return;
    }

    // Create and shuffle indices for random question selection
    int* indices = new int[totalQuestions];
    for (int i = 0; i < totalQuestions; i++) {
        indices[i] = i;
    }
    shuffleIndices(indices, totalQuestions);

    // Create dynamic array of polymorphic Question pointers
    Question** arr = new Question*[numQuizQuestions];

    for (int i = 0; i < numQuizQuestions; i++) {
        int idx = indices[i];
        arr[i] = new FreeResponseQuestion(
            allData[idx].question,
            allData[idx].answer
        );
    }

    cout << "\n===== FREE RESPONSE QUIZ =====\n";
    
    // Recursive quiz loop
    int correct = runRecursive(arr, 0, numQuizQuestions);

    // Pass/fail evaluation
    PassFail pf(correct, numQuizQuestions);
    printResult(pf);

    // *** Save score to history ***
    pf.saveHistory("Free Response");

    // Clean up memory
    for (int i = 0; i < numQuizQuestions; i++) {
        delete arr[i];
    }
    delete[] arr;
    delete[] indices;
}

// -------------------------------------------------------------
// MULTIPLE-CHOICE QUIZ
// Uses MultipleChoiceQuestion which auto-generates distractors.
// -------------------------------------------------------------
void Quiz::startMultipleChoiceQuiz() {

    if (totalQuestions == 0) {
        cout << "No questions available.\n";
        return;
    }

    // Random index shuffle
    int* indices = new int[totalQuestions];
    for (int i = 0; i < totalQuestions; i++) {
        indices[i] = i;
    }
    shuffleIndices(indices, totalQuestions);

    Question** arr = new Question*[numQuizQuestions];

    // Build MC questions using random distractors from the pool
    for (int i = 0; i < numQuizQuestions; i++) {
        int idx = indices[i];
        arr[i] = new MultipleChoiceQuestion(
            allData[idx],        // Q + Answer
            allData,             // full dataset for distractors
            totalQuestions       // pool size
        );
    }

    cout << "\n===== MULTIPLE CHOICE QUIZ =====\n";
    
    // Recursion to ask questions
    int correct = runRecursive(arr, 0, numQuizQuestions);

    PassFail pf(correct, numQuizQuestions);
    printResult(pf);

    // *** Save score history ***
    pf.saveHistory("Multiple Choice");

    for (int i = 0; i < numQuizQuestions; i++) {
        delete arr[i];
    }
    delete[] arr;
    delete[] indices;
}

// -------------------------------------------------------------
// Provide access to entire question bank
// -------------------------------------------------------------
QuestionData* Quiz::getAllData() const {
    return allData;
}

int Quiz::getTotalQuestions() const {
    return totalQuestions;
}

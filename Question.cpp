// Question.cpp
#include "Question.h"
#include <iostream>
#include <algorithm>

using namespace std;

static string toLowerTrim(const string& s) {
    string result;
    // copy non-newline chars
    for (char c : s) {
        if (c != '\r' && c != '\n')
            result.push_back(static_cast<char>(tolower(static_cast<unsigned char>(c))));
    }
    // trim spaces
    size_t start = result.find_first_not_of(' ');
    size_t end   = result.find_last_not_of(' ');
    if (start == string::npos) return "";
    return result.substr(start, end - start + 1);
}

Question::Question(const string& t, const string& a)
    : text(t), answer(a) {}

Question::~Question() {
    // nothing for now
}

const string& Question::getText() const {
    return text;
}

const string& Question::getAnswer() const {
    return answer;
}

FreeResponseQuestion::FreeResponseQuestion(const string& t, const string& a)
    : Question(t, a) {}

bool FreeResponseQuestion::ask() {
    cout << "\nQUESTION (Free Response):\n";
    cout << text << "\n";
    cout << "Your answer: ";

    string user;
    getline(cin, user);

    string userNorm = toLowerTrim(user);
    string ansNorm  = toLowerTrim(answer);

    if (userNorm == ansNorm) {
        cout << "Correct!\n";
        return true;
    } else {
        cout << "Incorrect.\nCorrect answer: " << answer << "\n";
        return false;
    }
}

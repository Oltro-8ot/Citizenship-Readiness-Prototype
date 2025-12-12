// PassFail.cpp
#include "PassFail.h"
#include <iostream>
#include <fstream>

using namespace std;

PassFail::PassFail(int c, int t)
    : correct(c), total(t) {}

// ------------------------
// Calculate % score
// ------------------------
double PassFail::getPercent() const {
    if (total == 0) return 0.0;
    return (static_cast<double>(correct) / total) * 100.0;
}

// ------------------------
// Pass/fail evaluation
// ------------------------
bool PassFail::isPass() const {
    return correct >= 6; // USCIS passing requirement
}

// ------------------------
// Write score history to file
// ------------------------
void PassFail::saveHistory(const string& mode) const {
    ofstream fout("history.txt", ios::app);  // append mode
    if (!fout) return;

    fout << "Mode: " << mode << "\n";
    fout << "Score: " << correct << "/" << total << "\n";
    fout << "Percent: " << getPercent() << "%\n";
    fout << "Result: " << (isPass() ? "PASS" : "FAIL") << "\n";
    fout << "-----------------------------\n";
    fout.close();
}

// ------------------------
// Print results to screen
// ------------------------
void printResult(const PassFail& pf) {
    cout << "\n===== QUIZ RESULTS =====\n";
    cout << "Score: " << pf.correct << " / " << pf.total << "\n";
    cout << "Percent: " << pf.getPercent() << "%\n";
    cout << "Status: " << (pf.isPass() ? "PASS" : "FAIL") << "\n";
}

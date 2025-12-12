// PassFail.h
#pragma once
#include <string>

class PassFail {
private:
    int correct;      // number of correct answers
    int total;        // total quiz questions

public:
    PassFail(int c, int t);

    double getPercent() const; // calculate percentage
    bool isPass() const;       // return true if passing score

    void saveHistory(const std::string& mode) const;
    // Writes results to "history.txt"

    friend void printResult(const PassFail& pf);
};

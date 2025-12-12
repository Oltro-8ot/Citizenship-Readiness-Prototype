// Question.h
#pragma once
#include <string>
using namespace std;

// Simple struct to hold raw question data
struct QuestionData {
    string question;
    string answer;
};

// Base class for all question types
class Question {
protected:
    string text;
    string answer;
public:
    Question(const string& t, const string& a);
    virtual ~Question(); // virtual for polymorphism

    virtual bool ask() = 0; // pure virtual – must be overridden

    const string& getText() const;
    const string& getAnswer() const;
};

// Free-response question (derived from Question)
class FreeResponseQuestion : public Question {
public:
    FreeResponseQuestion(const string& t, const string& a);
    virtual bool ask() override;
};

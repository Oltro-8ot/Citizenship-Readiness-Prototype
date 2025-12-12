// MultipleChoice.h
#pragma once
#include "Question.h"

class MultipleChoiceQuestion : public Question {
private:
    string options[4];
    int correctIndex; // 0–3

    void shuffleOptions();
public:
    MultipleChoiceQuestion(const QuestionData& data,
                           QuestionData* pool,
                           int poolSize);

    virtual bool ask() override;
};

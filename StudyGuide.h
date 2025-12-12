// StudyGuide.h
#pragma once
#include "Question.h"

class StudyGuide {
private:
    QuestionData* data;
    int totalQuestions;
    int showCount;

    void shuffleIndices(int* indices, int size);
public:
    StudyGuide(QuestionData* d, int total, int countToShow = 10);
    void run();
};

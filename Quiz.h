// Quiz.h
#pragma once
#include <string>
#include "Question.h"
#include "MultipleChoice.h"
#include "PassFail.h"

class Quiz {
private:
    QuestionData* allData;
    int totalQuestions;
    int numQuizQuestions;

    void loadFromFile(const std::string& filename);
    void shuffleIndices(int* indices, int size);

    int runRecursive(Question** arr, int index, int total);

public:
    Quiz(const std::string& filename, int quizCount = 10);
    ~Quiz();

    void startFreeResponseQuiz();
    void startMultipleChoiceQuiz();

    QuestionData* getAllData() const;
    int getTotalQuestions() const;
};

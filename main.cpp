#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class for all types of questions
class QuestionAnswer {
public:
    virtual ~QuestionAnswer() {}
};

// A QUESTION that expects an integer answer ranging from 1 to 5
class IntQuestion : public QuestionAnswer {
public:
    int answer;
    IntQuestion(int Answer) : answer(Answer) {}
};

class StringQuestion : public QuestionAnswer {
public:
    string answer;
    StringQuestion(string Answer) : answer(Answer) {}
};

// A true-false QUESTION that expects a Boolean answer
class TrueFalseQuestion : public QuestionAnswer {
public:
    bool answer;
    TrueFalseQuestion(bool Answer) : answer(Answer) {}
};

// A question SET consisting of various questions of type (1) or (2), or another question SET (3)
class QuestionSet : public QuestionAnswer {
private:
    vector<QuestionAnswer*> questionAnswers;
    vector<string> questions;
    int studentID;
public:
    void addQuestion(string question) {
        questions.push_back(question);
    }

    void addQuestionAnswer(QuestionAnswer* questionAnswer) {
        questionAnswers.push_back(questionAnswer);
    }

    const vector<QuestionAnswer*>& getQuestionAnswer() const {
        return questionAnswers;
    }

    const vector<string> getQuestions() const {
        return questions;
    }

    void setAssessmentID(int sID) {
        studentID = sID;
    }

    int getAssessmentID() {
        return studentID;
    }
};

class Professor {
private:
    string name;
    vector<string> subscribedStudents; // student's object names
    QuestionSet assessment;
    vector<QuestionAnswer*> correct_answers;
    bool studentsNotified = 0;
    void studentPerformance(string assessmentName) {

    }

public:
    Professor(string Name) : name(Name) {}
    string getName() {
        return name;
    }

    void notifyStudents() {
        studentsNotified = 1;
        for (int i = 0; i < subscribedStudents.size(); i++) {
            cout << subscribedStudents[i] << " has been notified" << endl;
        }

    }

    void addSubscribedStudent(string studentName) {
        subscribedStudents.push_back(studentName);
    }

    void gradeAndDisplayAssessment(QuestionSet studentAssessment) {
        vector<QuestionAnswer*> studentAnswers = studentAssessment.getQuestionAnswer();

        cout << "Grading assessment for student ID: " << studentAssessment.getAssessmentID() << endl;

        int score = 0;
        int total = studentAnswers.size();

        cout << "Question-wise assessment:" << endl;
        for (int i = 0; i < studentAnswers.size(); i++) {
            QuestionAnswer* studentAnswerBase = studentAnswers[i];
            QuestionAnswer* correctAnswerBase = correct_answers[i];

            // Perform dynamic casting to specific question types
            IntQuestion* studentIntAnswer = dynamic_cast<IntQuestion*>(studentAnswerBase);
            IntQuestion* correctIntAnswer = dynamic_cast<IntQuestion*>(correctAnswerBase);

            StringQuestion* studentStringAnswer = dynamic_cast<StringQuestion*>(studentAnswerBase);
            StringQuestion* correctStringAnswer = dynamic_cast<StringQuestion*>(correctAnswerBase);

            TrueFalseQuestion* studentBoolAnswer = dynamic_cast<TrueFalseQuestion*>(studentAnswerBase);
            TrueFalseQuestion* correctBoolAnswer = dynamic_cast<TrueFalseQuestion*>(correctAnswerBase);

            // Check if the casting was successful before comparing answers
            if (studentIntAnswer && correctIntAnswer) {
                if (studentIntAnswer->answer == correctIntAnswer->answer) {
                    score++;
                    cout << "Question " << i + 1 << ": Correct" << endl;
                }
                else {
                    cout << "Question " << i + 1 << ": Incorrect" << endl;
                }
            }
            else if (studentStringAnswer && correctStringAnswer) {
                if (studentStringAnswer->answer == correctStringAnswer->answer) {
                    score++;
                    cout << "Question " << i + 1 << ": Correct" << endl;
                }
                else {
                    cout << "Question " << i + 1 << ": Incorrect" << endl;
                }
            }
            else if (studentBoolAnswer && correctBoolAnswer) {
                if (studentBoolAnswer->answer == correctBoolAnswer->answer) {
                    score++;
                    cout << "Question " << i + 1 << ": Correct" << endl;
                }
                else {
                    cout << "Question " << i + 1 << ": Incorrect" << endl;
                }
            }
            else {
                cout << " answer type error" << endl;
            }
        }

        cout << "Total score: " << score << "/" << total << endl;
        cout << endl;
    }


    void setCorrectAssessmentAnswers(QuestionAnswer* answer) {
        correct_answers.push_back(answer);
    }

    vector<QuestionAnswer*> getCorrectAssessmentAnswers() {
        vector<QuestionAnswer*> returnedAnswers;
        for (int i = 0; i < correct_answers.size(); i++) {
            returnedAnswers.push_back(correct_answers[i]);
        }
        return returnedAnswers;
    }

    void setProfessorAssessment(QuestionSet Assessment) {
        assessment = Assessment;
        for (int i = 0; i < assessment.getQuestionAnswer().size(); i++) {
            QuestionAnswer* answer = assessment.getQuestionAnswer()[i];
            correct_answers.push_back(answer);
        }
    }

    QuestionSet getProfessorAssessment() {
        return assessment;
    }

    bool isNotified() {
        return studentsNotified;
    }
};

template<typename T>
class System {
private:
    vector<string> professors;
    vector<T> assessments;
    vector<vector<QuestionSet>> completed_assessments;
public:
    //void storeAssessment(vector<string> assessment_questions, T assessment_answers, string professor_name) {
    void storeAssessment(T Assessment) {
        assessments.push_back(Assessment);
    }

    void addProfessorToSystem(string profName) {
        professors.push_back(profName);
        completed_assessments.push_back(vector<QuestionSet>());
    }

    std::vector<string> getProfessors() {
        return professors;
    }

    vector<T> getAssessmentAnswers(string professor_name) {
        int profIdx = 0;
        for (int i = 0; i < professors.size(); i++) {
            if (professors[i] == professor_name) {
                profIdx = i;
            }
            else {
                cout << "Error getting assessmnet answers from the system" << endl;
            }
        }
        vector<T> answers;
        answers = assessments[profIdx].getQuestionAnswer();
        return answers;
    }

    vector<string> getAssessmentQuestions(string professor_name) {
        int pIndex = 0;
        vector<string> assessmentQuestions;
        for (int i = 0; i < professors.size(); i++) {
            if (professor_name == professors[i]) {
                pIndex = i;
            }
        }

        for (string x : assessments[pIndex].getQuestions()) {
            assessmentQuestions.push_back(x);
        }
        return assessmentQuestions;
    }

    void setCompletedAssessmentFromStudent(QuestionSet studentsTest, string professorName) {
        int pIdx = 0;
        for (int i = 0; i < professors.size(); i++) {
            if (professorName == professors[i]) {
                pIdx = i;
            }
        }

        completed_assessments[pIdx].push_back(studentsTest);
    }

    vector<QuestionSet> getCompletedAssessment(string professorName) {
        int pIdx = 0;
        vector<QuestionSet> returnedAssessments;
        for (int i = 0; i < professors.size(); i++) {
            if (professors[i] == professorName) {
                pIdx = i;
                break;
            }
        }

        for (int i = 0; i < completed_assessments[pIdx].size(); i++) {
            returnedAssessments.push_back(completed_assessments[pIdx][i]);
        }

        return returnedAssessments;
    }
};

template <typename T>
class Student {
private:
    int ID;
    //vector<string> assessment_questions;
    QuestionSet currentAssessment;
public:
    Student(int id) : ID(id) {}

    void setAssessmentQuestions(vector<string> AssessmentQuestions) {
        for (string x : AssessmentQuestions) {
            currentAssessment.addQuestion(x);
        }
    }

    vector<string> getAssessmentQuestions() {
        return currentAssessment.getQuestions();
    }

    void questionAnswer(QuestionAnswer* Answer) {
        currentAssessment.addQuestionAnswer(Answer);
    }

    vector<QuestionAnswer*> getQuestionAnswer() {
        return currentAssessment.getQuestionAnswer();
    }

    QuestionSet submitAssessment() {
        return this->currentAssessment;
    }
};

int main() {
    System<QuestionSet> system;
    Professor professor1("professor1");
    system.addProfessorToSystem("professor1");
    //system.storeProfessors("professor1");

    Student<QuestionSet> student1(1);
    Student<QuestionSet> student2(2);
    Student<QuestionSet> student3(3);
    Student<QuestionSet> student4(4);
    Student<QuestionSet> student5(5);

    professor1.addSubscribedStudent("student1");
    professor1.addSubscribedStudent("student2");
    professor1.addSubscribedStudent("student3");
    professor1.addSubscribedStudent("student4");
    professor1.addSubscribedStudent("student5");

    StringQuestion A1Q1("3");
    IntQuestion A1Q2(4);
    StringQuestion A1Q3("Red");
    TrueFalseQuestion A1Q4(1);

    QuestionAnswer* A1_Q1 = &A1Q1;
    QuestionAnswer* A1_Q2 = &A1Q2;
    QuestionAnswer* A1_Q3 = &A1Q3;
    QuestionAnswer* A1_Q4 = &A1Q4;

    QuestionSet assessment1;                                                                        // first assessment
    assessment1.addQuestion("What's a number that is greater than 2 but less than 4?");
    assessment1.addQuestion("What's a number that is greater than 3 but less than 5?");
    assessment1.addQuestion("What color comes before orange in ROYGBIV?");
    assessment1.addQuestion("Is the iPhone made by Apple? (Answer True or False)");

    assessment1.addQuestionAnswer(A1_Q1);
    assessment1.addQuestionAnswer(A1_Q2);
    assessment1.addQuestionAnswer(A1_Q3);
    assessment1.addQuestionAnswer(A1_Q4);

    cout << "\t\tTESTING QuestionAnswers\t\t" << endl;
    vector<QuestionAnswer*> test = assessment1.getQuestionAnswer();
    for (QuestionAnswer* i : test) {
        if (IntQuestion* x = dynamic_cast<IntQuestion*>(i)) {
            cout << "Int answer = " << x->answer << endl;
        }
        else if (StringQuestion* x = dynamic_cast<StringQuestion*>(i)) {
            cout << "String answer = " << x->answer << endl;
        }
        else if (TrueFalseQuestion* x = dynamic_cast<TrueFalseQuestion*>(i)) {
            cout << "Bool answer = " << x->answer << endl;
        }
        else {
            cout << "End of assessment" << endl;
        }
    }

    cout << endl;

    professor1.setProfessorAssessment(assessment1);                             // Adds assessment to professor / associates it with professor
    professor1.notifyStudents();

    vector<string> assessment1_questions = assessment1.getQuestions();
    for (string x : assessment1_questions) {
        cout << x << endl;
    }                                                                // test

    QuestionSet professorTest = professor1.getProfessorAssessment();
    cout << "Testing answers from professor " << professor1.getName() << endl;
    for (QuestionAnswer* i : professorTest.getQuestionAnswer()) {
        if (IntQuestion* x = dynamic_cast<IntQuestion*>(i)) {
            cout << "Int answer = " << x->answer << endl;
        }
        else if (StringQuestion* x = dynamic_cast<StringQuestion*>(i)) {
            cout << "String answer = " << x->answer << endl;
        }
        else if (TrueFalseQuestion* x = dynamic_cast<TrueFalseQuestion*>(i)) {
            cout << "String answer = " << x->answer << endl;
        }
        else {
            cout << "End of assessment" << endl;
        }
    }


    system.storeAssessment(professor1.getProfessorAssessment());

    cout << "professor names = " << endl;
    vector<string> test_prof = system.getProfessors();
    for (string x : test_prof) {
        cout << x << endl;
    }

    cout << "Assessment questions from system = " << endl;
    vector<string> testing_questions_vec = system.getAssessmentQuestions("professor1");
    for (string x : testing_questions_vec) {
        cout << x << endl;
    }

    vector<string> student_assessment1_questions = system.getAssessmentQuestions("professor1");
    student1.setAssessmentQuestions(student_assessment1_questions);

    StringQuestion studentAnswer1("3");
    IntQuestion studentAnswer2(8);
    StringQuestion studentAnswer3("Red");
    TrueFalseQuestion studentAnswer4(1);

    QuestionAnswer* SA1 = &studentAnswer1;
    QuestionAnswer* SA2 = &studentAnswer2;
    QuestionAnswer* SA3 = &studentAnswer3;
    QuestionAnswer* SA4 = &studentAnswer4;

    student1.questionAnswer(SA1);
    student1.questionAnswer(SA2);
    student1.questionAnswer(SA3);
    student1.questionAnswer(SA4);

    QuestionSet student1_Assessment = student1.submitAssessment();
    student1_Assessment.setAssessmentID(1);

    system.setCompletedAssessmentFromStudent(student1_Assessment, "professor1");

    /*vector<string> assessment1_student_questions = student1_Assessment.getQuestions();
    vector<QuestionAnswer*> assessment1_student_answers = student1_Assessment.getQuestionAnswer();
    cout << "----------- Student Questions and Answers -----------" << endl;
    for (int i = 0; i < assessment1_student_questions.size(); i++) {
        cout << assessment1_student_questions[i] << endl;
        QuestionAnswer* currAnswer = assessment1_student_answers[i];
        if (IntQuestion* x = dynamic_cast<IntQuestion*>(currAnswer)) {
            cout << "Int answer = " << x->answer << endl;
        }
        else if (StringQuestion* x = dynamic_cast<StringQuestion*>(currAnswer)) {
            cout << "String answer = " << x->answer << endl;
        }
        else if (TrueFalseQuestion* x = dynamic_cast<TrueFalseQuestion*>(currAnswer)) {
            cout << "Bool answer = " << x->answer << endl;
        }
        else {
            cout << "End of assessment" << endl;
        }
    }*/

    vector<QuestionSet> completedAssessments = system.getCompletedAssessment("professor1");

    // Loop through completed assessments and display questions and answers
    for (int i = 0; i < completedAssessments.size(); i++) {
        cout << "Assessment ID: " << completedAssessments[i].getAssessmentID() << endl;

        // Display questions
        cout << "Questions:" << endl;
        const vector<string>& questions = completedAssessments[i].getQuestions();
        for (const auto& question : questions) {
            cout << question << endl;
        }

        // Display answers
        cout << "Answers:" << endl;
        const vector<QuestionAnswer*>& answers = completedAssessments[i].getQuestionAnswer();
        for (const auto& answer : answers) {
            if (typeid(*answer) == typeid(IntQuestion)) {
                IntQuestion* intAnswer = dynamic_cast<IntQuestion*>(answer);
                cout << "Integer Answer: " << intAnswer->answer << endl;
            }
            else if (typeid(*answer) == typeid(StringQuestion)) {
                StringQuestion* stringAnswer = dynamic_cast<StringQuestion*>(answer);
                cout << "String Answer: " << stringAnswer->answer << endl;
            }
            else if (typeid(*answer) == typeid(TrueFalseQuestion)) {
                TrueFalseQuestion* boolAnswer = dynamic_cast<TrueFalseQuestion*>(answer);
                cout << "True/False Answer: " << boolalpha << boolAnswer->answer << endl;
            }
        }
    }


    cout << "---------------------------------- Student Grades ----------------------------------" << endl;
    for (int i = 0; i < completedAssessments.size(); i++) {
        professor1.gradeAndDisplayAssessment(completedAssessments[i]);
    }
    professor1.notifyStudents();

    /*vector<QuestionAnswer*> assessment1_student_answers = student1_Assessment.getQuestionAnswer();
    for (int i = 0; i < assessment1_student_questions.size(); i++) {
        cout << assessment1_student_questions[i] << endl;
        QuestionAnswer* currAnswer = assessment1_student_answers[i];
        if (IntQuestion* x = dynamic_cast<IntQuestion*>(currAnswer)) {
            cout << "Int answer = " << x->answer << endl;
        }
        else if (StringQuestion* x = dynamic_cast<StringQuestion*>(currAnswer)) {
            cout << "String answer = " << x->answer << endl;
        }
        else if (TrueFalseQuestion* x = dynamic_cast<TrueFalseQuestion*>(currAnswer)) {
            cout << "Bool answer = " << x->answer << endl;
        }
        else {
            cout << "End of assessment" << endl;
        }
    }*/


    //professor1.gradeAndDisplayAssessment();
}


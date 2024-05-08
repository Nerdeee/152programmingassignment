#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class for all types of questions
class QuestionAnswer {
public:
    virtual ~QuestionAnswer() {}
};

// Question that expects an integer answer ranging from 1 to 5
class IntQuestion : public QuestionAnswer {
public:
    int answer;
    IntQuestion(int Answer) : answer(Answer) {}
};

// Question that exoects a string
class StringQuestion : public QuestionAnswer {
public:
    string answer;
    StringQuestion(string Answer) : answer(Answer) {}
};

// Question that expects a boolean answer
class TrueFalseQuestion : public QuestionAnswer {
public:
    bool answer;
    TrueFalseQuestion(bool Answer) : answer(Answer) {}
};

// Question set consisting of various questions of the previously defined types 
class QuestionSet {
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

// Professor class
class Professor {
private:
    string name;                       // used for identifying professor
    vector<string> subscribedStudents; // student's object names
    QuestionSet assessment;            // stores the professor's current assessment
    vector<QuestionAnswer*> correct_answers;        // stores the correct answers to the assessment (used for comparing correct answers with student's asnwers)
    bool studentsNotified = 0;
public:
    Professor(string Name) : name(Name) {}           // default constructor that assigns the professor's name as the name member variable        
    string getName() {                  // gets professor's name  
        return name;
    }

    void notifyStudents() {             // notify's students that are subscribed to the professor
        studentsNotified = 1;
        for (int i = 0; i < subscribedStudents.size(); i++) {
            cout << subscribedStudents[i] << " has been notified" << endl;
        }

    }

    void addSubscribedStudent(string studentName) {         // adds students to the professor's subscribed student list
        subscribedStudents.push_back(studentName);
    }

    void gradeAndDisplayAssessment(QuestionSet studentAssessment) {         // grades student's exam and displays it along with the score
        vector<QuestionAnswer*> studentAnswers = studentAssessment.getQuestionAnswer();

        cout << "Grading assessment for student ID: " << studentAssessment.getAssessmentID() << endl;

        int score = 0;
        int total = studentAnswers.size();

        cout << "Question-wise assessment:" << endl;
        for (int i = 0; i < studentAnswers.size(); i++) {
            QuestionAnswer* studentAnswerBase = studentAnswers[i];
            QuestionAnswer* correctAnswerBase = correct_answers[i];

            IntQuestion* studentIntAnswer = dynamic_cast<IntQuestion*>(studentAnswerBase);
            IntQuestion* correctIntAnswer = dynamic_cast<IntQuestion*>(correctAnswerBase);

            StringQuestion* studentStringAnswer = dynamic_cast<StringQuestion*>(studentAnswerBase);
            StringQuestion* correctStringAnswer = dynamic_cast<StringQuestion*>(correctAnswerBase);

            TrueFalseQuestion* studentBoolAnswer = dynamic_cast<TrueFalseQuestion*>(studentAnswerBase);
            TrueFalseQuestion* correctBoolAnswer = dynamic_cast<TrueFalseQuestion*>(correctAnswerBase);

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


    void setCorrectAssessmentAnswers(QuestionAnswer* answer) {              // allows the professor to set the correct answers for the assessment
        correct_answers.push_back(answer);
    }

    vector<QuestionAnswer*> getCorrectAssessmentAnswers() {                 // getter for the correct answers
        vector<QuestionAnswer*> returnedAnswers;
        for (int i = 0; i < correct_answers.size(); i++) {
            returnedAnswers.push_back(correct_answers[i]);
        }
        return returnedAnswers;
    }

    void setProfessorAssessment(QuestionSet Assessment) {                   // adds an assessment to the professor object
        cout << "Assessment created by professor: " << name << endl;
        assessment = Assessment;
        for (int i = 0; i < assessment.getQuestionAnswer().size(); i++) {
            QuestionAnswer* answer = assessment.getQuestionAnswer()[i];
            correct_answers.push_back(answer);
        }
    }

    QuestionSet getProfessorAssessment() {                                   // returns the assessment belonging to the professor object
        return assessment;
    }
        
    bool isNotified() {                                                      // returns either true or false depedning on if the student's have been notified or not
        return studentsNotified;
    }
};

template<typename T>
class System {                      // system class for keeping track of total number of professors and for sending and receiving exams between professor and student
private:
    vector<string> professors;      // stores the names of all of the professors inside the system
    vector<T> assessments;          // stores all of the assessments
    vector<vector<QuestionSet>> completed_assessments;  // stores the completed assessments where the index inside the first vector corresponds to the index of the professor name in the professors vector
public:
    void storeAssessment(T Assessment) {            // stores assessment in the ssessment vector
        assessments.push_back(Assessment);
    }

    void addProfessorToSystem(string profName) {        // adds professor name to the professor name vector
        professors.push_back(profName);
        completed_assessments.push_back(vector<QuestionSet>());
    }

    std::vector<string> getProfessors() {               // returns all of the names of the professors
        return professors;
    }

    vector<T> getAssessmentAnswers(string professor_name) {         // returns all of the assessment answers for an assessment associated with the professor name passed into the function
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

    vector<string> getAssessmentQuestions(string professor_name) {      // returns all of the assessment questions for an assessment associated with the professor name passed into the function
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

    void setCompletedAssessmentFromStudent(QuestionSet studentsTest, string professorName) {        // adds the student's assessment to the correct index associated with their professor
        int pIdx = 0;
        for (int i = 0; i < professors.size(); i++) {
            if (professorName == professors[i]) {
                pIdx = i;
            }
        }

        completed_assessments[pIdx].push_back(studentsTest);
    }

    vector<QuestionSet> getCompletedAssessment(string professorName) {              // returns the completed assessments of the students that are subscribed to that professor
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
class Student {                             // student class
private:
    int ID;                                 // ID for identifying different student objects
    QuestionSet currentAssessment;          // assessment that the student is currently working on
public:
    Student(int id) : ID(id) {}             // default constructor to give a student their ID upon object creation

    void setAssessmentQuestions(vector<string> AssessmentQuestions) {       // sets the questions for the currentAssessment
        for (string x : AssessmentQuestions) {
            currentAssessment.addQuestion(x);
        }
    }

    vector<string> getAssessmentQuestions() {                   // returns the questions for the currentAssessment
        return currentAssessment.getQuestions();
    }

    void questionAnswer(QuestionAnswer* Answer) {               // adds new answer to the currentAssessment
        currentAssessment.addQuestionAnswer(Answer);
    }

    vector<QuestionAnswer*> getQuestionAnswer() {               // returns the answers for the currentAssessment
        return currentAssessment.getQuestionAnswer();
    }

    QuestionSet submitAssessment() {                     // return sthe currentAssessment object
        return this->currentAssessment;
    }
};

int main() {
    System<QuestionSet> system;                         // creating a system
    Professor professor1("professor1");                 // creating a professor
    system.addProfessorToSystem("professor1");
    //system.storeProfessors("professor1");

    Student<QuestionSet> student1(1);                   // adding new stduents and making sure that the currentAssessment is of type QuestionSet
    Student<QuestionSet> student2(2);
    Student<QuestionSet> student3(3);
    Student<QuestionSet> student4(4);
    Student<QuestionSet> student5(5);

    professor1.addSubscribedStudent("student1");        // adding all of the names of the previous student objects to the list of subscribed students for the first professor
    professor1.addSubscribedStudent("student2");
    professor1.addSubscribedStudent("student3");
    professor1.addSubscribedStudent("student4");
    professor1.addSubscribedStudent("student5");

    StringQuestion A1Q1("3");                           // creating answers for the assessment
    IntQuestion A1Q2(4);
    StringQuestion A1Q3("Red");
    TrueFalseQuestion A1Q4(1);

    QuestionAnswer* A1_Q1 = &A1Q1;                      // converting answers to the base class to store later
    QuestionAnswer* A1_Q2 = &A1Q2;
    QuestionAnswer* A1_Q3 = &A1Q3;
    QuestionAnswer* A1_Q4 = &A1Q4;

    QuestionSet assessment1;                                                                        // first assessment
    assessment1.addQuestion("What's a number that is greater than 2 but less than 4?");             // adding questions to the assessment
    assessment1.addQuestion("What's a number that is greater than 3 but less than 5?");
    assessment1.addQuestion("What color comes before orange in ROYGBIV?");
    assessment1.addQuestion("Is the iPhone made by Apple? (Answer True or False)");

    assessment1.addQuestionAnswer(A1_Q1);                       // adds answers to the assessment
    assessment1.addQuestionAnswer(A1_Q2);
    assessment1.addQuestionAnswer(A1_Q3);
    assessment1.addQuestionAnswer(A1_Q4);

    cout << endl;

    professor1.setProfessorAssessment(assessment1);                             // adds assessment to professor / associates it with professor
    professor1.notifyStudents();                                                // once the assessment is created by the professor, the students are notified

    //cout << "-------------- Professor 1's assessment --------------" << endl;         // used for testing purposes
    /*QuestionSet professorTest = professor1.getProfessorAssessment();
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
    }*/

    system.storeAssessment(professor1.getProfessorAssessment());            // stores the professor assessment in the system

    cout << "---------------- professor names ----------------" << endl;                                   // test for retrieving 
    vector<string> test_prof = system.getProfessors();
    for (string x : test_prof) {
        cout << x << endl;
    }

    cout << "---------------- Assessment questions from system ----------------" << endl;                  // questions from system    
    vector<string> testing_questions_vec = system.getAssessmentQuestions("professor1");
    for (string x : testing_questions_vec) {
        cout << x << endl;
    }

    vector<string> student_assessment1_questions = system.getAssessmentQuestions("professor1");         // student 1 getting assessment 1 questions
    student1.setAssessmentQuestions(student_assessment1_questions);                                     // student 1 setting assessment 1 questions for themselves
    student2.setAssessmentQuestions(student_assessment1_questions);

    StringQuestion studentAnswer1("3");                                      // student1's answers
    IntQuestion studentAnswer2(8);
    StringQuestion studentAnswer3("Red");
    TrueFalseQuestion studentAnswer4(1);

    StringQuestion student2Answer1("10");                                      // student2's answers
    IntQuestion student2Answer2(1);
    StringQuestion student2Answer3("Red");
    TrueFalseQuestion student2Answer4(1);

    QuestionAnswer* SA1 = &studentAnswer1;                                   // converting student 1's answers to base class
    QuestionAnswer* SA2 = &studentAnswer2;
    QuestionAnswer* SA3 = &studentAnswer3;
    QuestionAnswer* SA4 = &studentAnswer4;

    QuestionAnswer* S2A1 = &student2Answer1;                                   // converting student 2's answers to base class
    QuestionAnswer* S2A2 = &student2Answer2;
    QuestionAnswer* S2A3 = &student2Answer3;
    QuestionAnswer* S2A4 = &student2Answer4;

    student1.questionAnswer(SA1);                                            // adding student1's answers 
    student1.questionAnswer(SA2);
    student1.questionAnswer(SA3);
    student1.questionAnswer(SA4);

    student2.questionAnswer(S2A1);                                            // adding student2's answers 
    student2.questionAnswer(S2A2);
    student2.questionAnswer(S2A3);
    student2.questionAnswer(S2A4);

    QuestionSet student1_Assessment = student1.submitAssessment();            // gets the student1's assessment object
    student1_Assessment.setAssessmentID(1);                                   // assign it an ID


    QuestionSet student2_Assessment = student2.submitAssessment();            // gets the student2's assessment object
    student2_Assessment.setAssessmentID(2);                                   // assign it an ID
    
    system.setCompletedAssessmentFromStudent(student1_Assessment, "professor1");    // send the completed assessment to the system and put it in the location associated with professor1
    system.setCompletedAssessmentFromStudent(student2_Assessment, "professor1");

    vector<QuestionSet> completedAssessments = system.getCompletedAssessment("professor1");         // professor1 retrieves student 1's assessment

    cout << " ---------------- Completed Assessments and the student's answers from the system ----------------" << endl;
    for (int i = 0; i < completedAssessments.size(); i++) {                                         // loop through completed assessments and display questions and answers
        cout << "Assessment ID: " << completedAssessments[i].getAssessmentID() << endl;

        cout << "Questions:" << endl;                                                               // display student's questions
        const vector<string>& questions = completedAssessments[i].getQuestions();
        for (const auto& question : questions) {
            cout << question << endl;
        }

        cout << "Answers:" << endl;                                                                  // display student's answers
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


    cout << "---------------------------------- Student Grades ----------------------------------" << endl;                    // posted graded assessments
    for (int i = 0; i < completedAssessments.size(); i++) {
        professor1.gradeAndDisplayAssessment(completedAssessments[i]);
    }
    professor1.notifyStudents();                                                                                               // notify students that their grades have been posted
}

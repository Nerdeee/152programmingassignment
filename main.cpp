#include <iostream>
#include <vector>

using namespace std;

//template<typename T>
class System {
private:
	vector<string> professor_names;
	vector<string> assessments_vec;
public:
	void storeAssessment(vector<string> assessments) {
		assessments_vec.push_back(assessments);
	}
	void storeProfessorNames(string name) {
		professor_names.push_back(name);
	}
	vector<string> getProfessorNames() {
		return professor_names;
	}
	vector<string> getAssessments() {
		return assessments_vec;
	}


};

class Assessment {
private:
	T questionTypeOne(T answer);
	bool questionTypeTwo(bool answer);

public:
	vector<T> questionSet;
	void submitAssessment();
};


class Professor {							// needs some way to retrieve the assessments. Possesses the correct answers
private:					
	vector<int> subscribedStudentIDs;		// student's object names		
	void studentPerformance(string assessmentName) {
	
	}
public:
	void notifyStudents(int numberOfStudents) {
	
	}

	void postAssessment(Assessment assessment) {
		
	};
	void gradeAndDisplayAssessment(); // use this to get the questions and question sets, student's answers, and overall score (assuming each question is one point)
};

class Student {
private:
	int ID;
	string subscribedTo;
public:
	void subscribeTo(string professorName) {
		subscribedTo = professorName;
	};
	string getSubscribedTo() {
		return subscribedTo;
	}

	void retrievePostedAssessment(vector<string> professorNames, string professor) {
		for (int i = 0; i < professorNames.size(); i++) {
			if (professor == professorNames[i]) {

			}
			else {

			}
		}
	};
	//void submitAssessment();
};

int main() {
	int numberOfProfessors;
	while (true) {
		bool isProfessor;
		System system;
		cout << "How many professors are there in the department?" << endl;
		cin >> numberOfProfessors;
		cout << "Are you a professor or a student? Enter 1 for \"yes\", 0 for \"no\"" << endl;
		cin >> isProfessor;
		if (!isProfessor) {
			Professor professorObject;
			cout << "" << endl;
		}
	}
}

#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

class Student {
	private:
		std::string studentName;
		std::vector<double> gradeValues;
	public:
		Student(std::string name, std::vector<double> grades)
			: studentName(std::move(name)), gradeValues(std::move(grades)) {}
		~Student() {}

		std::string name() const {
			return studentName;
		}

		double grades() const {
			if (gradeValues.empty())
				return 0.0;
			double sum = std::accumulate(gradeValues.begin(), gradeValues.end(), 0.0);
			return sum / gradeValues.size();
		}
};

class studentReport {
	public:
		void print (const Student& student) const {
			std::cout << "Student Name: " << student.name() << std::endl;
			std::cout << "GPA: " << student.grades() << std::endl;
		}
};

class keepinfile {
	public:
		void saveToFile(const Student& student, const std::string& filename) const {
			std::ofstream file(filename, std::ios::app);
			if (file.is_open()) {
				file << student.name() << "," << student.grades() << "\n";
				file.close();
				std::cout << "Successfully saved to " << filename << "\n";
			}
		}
};

int main () {
	Student student1("Svetlana", {95, 90, 100, 88});
	Student student2("Lusine", {85, 90, 80, 100});

    studentReport printer;
    printer.print(student1);
	printer.print(student2);

    keepinfile repo;
    repo.saveToFile(student1, "student_data.txt");
	repo.saveToFile(student2, "student_data.txt");
    return 0;
}
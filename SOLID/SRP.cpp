#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

class Student {
	public:
		Student(std::string name, std::vector<double> grades)
			: studentName(std::move(name)), gradeValues(std::move(grades)) {}

		const std::string& name() const { return studentName; }
		const std::vector<double>& grades() const { return gradeValues; }

	private:
		std::string studentName;
		std::vector<double> gradeValues;
};

class GpaStrategy {
	public:
		virtual ~GpaStrategy() = default;
		virtual double calculateGPA(const Student& student) const = 0;
};

class StandardGpaStrategy : public GpaStrategy {
	public:
		double calculateGPA(const Student& student) const override {
			const auto& g = student.grades();
			if (g.empty()) return 0.0;
			return std::accumulate(g.begin(), g.end(), 0.0) / static_cast<double>(g.size());
		}
};

class StudentReport {
	public:
		explicit StudentReport(const GpaStrategy& strategy) : strategy(strategy) {}

		void print(const Student& student) const {
			const auto& g = student.grades();
			std::cout << "Student Name: " << student.name() << '\n';
			std::cout << "Grades: ";
			for (std::size_t i = 0; i < g.size(); ++i) {
				if (i > 0) std::cout << ", ";
				std::cout << g[i];
			}
			std::cout << '\n';
			std::cout << "GPA: " << strategy.calculateGPA(student) << '\n';
		}

	private:
		const GpaStrategy& strategy;
};

class StudentFileRepository {
	public:
		explicit StudentFileRepository(std::string filename) : filename(std::move(filename)) {}

		bool save(const Student& student) const {
			std::ofstream file(filename, std::ios::app);
			if (!file) {
				std::cerr << "Failed to open " << filename << '\n';
				return false;
			}
			const auto& g = student.grades();
			file << student.name() << ",";
			for (std::size_t i = 0; i < g.size(); ++i) {
				if (i > 0) file << ", ";
				file << g[i];
			}
			file << '\n';
			return true;
		}

	private:
		std::string filename;
};

int main() {
    Student student1("Svetlana", {95, 90, 100, 88});
    Student student2("Lusine", {85, 90, 80, 100});

    StandardGpaStrategy strategy;
    StudentReport printer(strategy);
    printer.print(student1);
    printer.print(student2);

    StudentFileRepository repo("student_data.txt");
    repo.save(student1);
    repo.save(student2);
    return 0;
}
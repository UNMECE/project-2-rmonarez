nclude <iostream>
#include <vector>
#include <string>
#include <fstream>

// Base class Student
class Student {
protected:
    std::string first_name;
    std::string last_name;
    double gpa;
    int graduation_year;
    std::string graduation_semester;
    int enrolled_year;
    std::string enrolled_semester;
    std::string level; // "Undergrad" or "Grad"

public:
    // Default constructor
    Student() : first_name(""), last_name(""), gpa(0.0), graduation_year(0), enrolled_year(0),
                graduation_semester(""), enrolled_semester(""), level("Undergrad") {}

    // Destructor
    virtual ~Student() = default;

    // Setters
    void setName(const std::string& first, const std::string& last) {
        first_name = first;
        last_name = last;
    }

    void setGPA(double g) { gpa = g; }
    void setGraduationYear(int year) { graduation_year = year; }
    void setGraduationSemester(const std::string& semester) { graduation_semester = semester; }
    void setEnrolledYear(int year) { enrolled_year = year; }
    void setEnrolledSemester(const std::string& semester) { enrolled_semester = semester; }
    void setLevel(const std::string& lvl) { level = lvl; }

    // Getter for displaying student details (virtual to allow overrides)
    virtual void printInfo(std::ostream& out) const {
        out << "Name: " << first_name << " " << last_name << "\n"
            << "GPA: " << gpa << "\n"
            << "Graduation: " << graduation_semester << " " << graduation_year << "\n"
            << "Enrolled: " << enrolled_semester << " " << enrolled_year << "\n"
            << "Level: " << level << "\n";
    }
};

// Derived class Art_Student
class Art_Student : public Student {
private:
    std::string art_emphasis; // Can be "Art Studio", "Art History", or "Art Education"

public:
    // Default constructor
    Art_Student() : art_emphasis("Art Studio") {}

    // Setter for art emphasis
    void setArtEmphasis(const std::string& emphasis) {
        if (emphasis == "Art Studio" || emphasis == "Art History" || emphasis == "Art Education") {
            art_emphasis = emphasis;
        }
    }

    // Override printInfo to include art emphasis
    void printInfo(std::ostream& out) const override {
        Student::printInfo(out);
        out << "Art Emphasis: " << art_emphasis << "\n";
    }
};

// Derived class Physics_Student
class Physics_Student : public Student {
private:
    std::string concentration; // Can be "Biophysics" or "Earth and Planetary Sciences"

public:
    // Default constructor
    Physics_Student() : concentration("Biophysics") {}

    // Setter for concentration
    void setConcentration(const std::string& conc) {
        if (conc == "Biophysics" || conc == "Earth and Planetary Sciences") {
            concentration = conc;
        }
    }

    // Override printInfo to include concentration
    void printInfo(std::ostream& out) const override {
        Student::printInfo(out);
        out << "Concentration: " << concentration << "\n";
    }
};

int main() {
    // Create vectors to store pointers to Art_Student and Physics_Student objects
    std::vector<Art_Student*> art_students;
    std::vector<Physics_Student*> physics_students;

    // Create and add Art_Student objects to the vector
    for (int i = 0; i < 5; ++i) {
        Art_Student* art_student = new Art_Student;
        art_student->setName("ArtFirst" + std::to_string(i + 1), "ArtLast" + std::to_string(i + 1));
        art_student->setGPA(3.5 + i * 0.1);
        art_student->setGraduationYear(2025);
        art_student->setGraduationSemester("Spring");
        art_student->setEnrolledYear(2021);
        art_student->setEnrolledSemester("Fall");
        art_student->setLevel("Undergrad");
        art_student->setArtEmphasis(i % 2 == 0 ? "Art Studio" : "Art History");
        art_students.push_back(art_student);
    }

    // Create and add Physics_Student objects to the vector
    for (int i = 0; i < 5; ++i) {
        Physics_Student* physics_student = new Physics_Student;
        physics_student->setName("PhysFirst" + std::to_string(i + 1), "PhysLast" + std::to_string(i + 1));
        physics_student->setGPA(3.7 + i * 0.1);
        physics_student->setGraduationYear(2026);
        physics_student->setGraduationSemester("Winter");
        physics_student->setEnrolledYear(2022);
        physics_student->setEnrolledSemester("Spring");
        physics_student->setLevel("Grad");
        physics_student->setConcentration(i % 2 == 0 ? "Biophysics" : "Earth and Planetary Sciences");
        physics_students.push_back(physics_student);
    }

    // Write student information to a file
    std::ofstream outfile("student_info.dat");
    if (outfile.is_open()) {
        for (const auto& student : art_students) {
            student->printInfo(outfile);
            outfile << "\n";
        }
        for (const auto& student : physics_students) {
            student->printInfo(outfile);
            outfile << "\n";
        }
        outfile.close();
    } else {
        std::cerr << "Error opening file for writing.\n";
    }

    // Clean up dynamically allocated memory
    for (auto* student : art_students) {
        delete student;
    }
    for (auto* student : physics_students) {
        delete student;
    }

    return 0;
}


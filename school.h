#include<string>
#include<vector>
#include<unordered_set>
#include<iostream>
#include<fstream>

class Student{
private:
    std::string ID;
    std::string firstName;
    std::string lastName;

public:
//constructor

    Student(const std::string& ID, const std::string& firstName, const std::string& lastName)
    : ID(ID), firstName(firstName), lastName(lastName){}

//accessor methods

    std::string getFirstName() const{
        return firstName;
    }

    std::string getLastName() const{
        return lastName;
    }

    std::string getID() const{
        return ID;
    }
};

class Subject{
private:
    std::string subjectName;
    float LT1;//grade at lab test 1
    float LT2;//grade at lab test 2
    float MTE;//grade at course midterm
    float FE;//grade at final exam
    int labAttendace;
    int courseAttendace;

public:

//constructor

    Subject(const std::string& subjectName, float LT1 = -1, float LT2 = -1, float MTE = -1, float FE = -1, int labAttendance = 0, int courseAttendance = 0)
    : subjectName(subjectName), LT1(LT1), LT2(LT2), MTE(MTE), FE(FE), labAttendace(labAttendace), courseAttendace(courseAttendace){}

//accessor methods



//other methods

    float getLabGrade() const{
        return (LT1+LT2)/2;
    }

    float getFinalGrade() const{
        return (this->getLabGrade()*0.3 + MTE*0.2 + FE*0.5);
    }
};

class Program{
private:
    std::string name;
    int numberOfStudents;
    std::unordered_set<Student> students;
    std::unordered_set<Subject> subjectsForSem1;
    std::unordered_set<Subject> subjectsForSem2;
    std::unordered_set<Subject> subjectsForSem3;
    std::unordered_set<Subject> subjectsForSem4;
    std::unordered_set<Subject> subjectsForSem5;
    std::unordered_set<Subject> subjectsForSem6;

public:

//constructor

    Program(
        const std::string& name, int numberOfStudents, std::unordered_set<Student> students,
        std::unordered_set<Subject> subjectsForSem1, std::unordered_set<Subject> subjectsForSem2,
        std::unordered_set<Subject> subjectsForSem3, std::unordered_set<Subject> subjectsForSem4,
        std::unordered_set<Subject> subjectsForSem5, std::unordered_set<Subject> subjectsForSem6
    )
    : name(name), numberOfStudents(numberOfStudents), students(students), subjectsForSem1(subjectsForSem1), subjectsForSem2(subjectsForSem2),
    subjectsForSem3(subjectsForSem3), subjectsForSem4(subjectsForSem4), subjectsForSem5(subjectsForSem5), subjectsForSem6(subjectsForSem6){}

//accessor methods



//other methods

    std::string getNameOfProgram() const{
        return name;
    }

    int getNumberOfStudents() const{
        return numberOfStudents; 
    }

    std::unordered_set<Subject> getSubjectsForASemester(int s){
        switch (s){
            case 1:
                return subjectsForSem1;
                break;
            case 2:
                return subjectsForSem2;
                break;
            case 3:
                return subjectsForSem3;
                break;
            case 4:
                return subjectsForSem4;
                break;
            case 5:
                return subjectsForSem5;
                break;
            case 6:
                return subjectsForSem6;
                break;
        }
        std::unordered_set<Subject> empty;
        return empty;
    }

};

class Faculty{
private:
    std::string name;
    std::unordered_set<Program> programs;

public:

//constructor

    Faculty(const std::string& name, std::unordered_set<Program> programs)
    : name(name), programs(programs){}

//accessor methods

    std::string getNameOfFaculty() const{
        return name;
    }

//other methods

    std::string getAbbreviatedNameOfFaculty(){
        std::string abbreviation;
        bool prevIsSpace = true; // Flag to track if the previous character was a space
        for(char c : name){
            if(std::isalpha(c)){
                if(prevIsSpace){
                    abbreviation += c;
                }
                prevIsSpace = false;
            }
            else{
                prevIsSpace = true;
            }
        }
        return abbreviation;
    }

    int getNumberofStudents() const{
        int numberofstudents=0;
        for (const auto& element : programs) {
            // Access each element using the 'element' variable
            numberofstudents+=element.getNumberOfStudents();
       }
       return numberofstudents;
    }

};

class University{
private:
    std::string name;
    std::unordered_set<Faculty> faculties;

public:

//constructor

    University(const std::string& name, std::unordered_set<Faculty> faculties )
        : name(name), faculties(faculties){}


//accessor methods
    std::string getNameOfUniversity() const{
            return name;
    }

//acceseaza o anumita facultate, acceseaza numele

//other methods



};

//bagi o metoda care iti numara cati studenti sunt la facultatea x, metoda sa o bagi in clasa faculty

//cauta cum se lucreaza cu sfml
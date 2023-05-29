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

    std::string getID() const{
        return ID;
    }

    std::string getFirstName() const{
        return firstName;
    }

    std::string getLastName() const{
        return lastName;
    }
//other methods

    friend std::string getAbbreviatedNameOfFaculty();//make the abreviate function friend;

};

class Subject{
private:
    std::string name;
    float LT1;//grade at lab test 1
    float LT2;//grade at lab test 2
    float MTE;//grade at course midterm
    float FE;//grade at final exam
    int labAttendance;
    int courseAttendance;

public:

//constructor

    Subject(const std::string& name, float LT1 = -1, float LT2 = -1, float MTE = -1, float FE = -1, int labAttendance = 0, int courseAttendance = 0)
    : name(name), LT1(LT1), LT2(LT2), MTE(MTE), FE(FE), labAttendance(labAttendance), courseAttendance(courseAttendance){}

//accessor methods

    std::string getSubjectName() const{
        return name;
    }

    float getLT1() const{
        return LT1;
    }

    float getLT2() const{
        return LT2;
    }

    float getMTE() const{
        return MTE;
    }

    float getFE(){
        return FE;
    }
    
    int getLabAttendance() const{
        return labAttendance;
    }

    int getCourseAttendance() const{
        return courseAttendance
    }

//update methods

    void updateSubjectName(const std::string& name){
        this->name=name;
    }

    void updateLT1(float LT1){
        this->LT1=LT1;
    }

    void updateLT2()onst{
        this->LT2=LT2;
    }

    void updateMTE(){
        this->MTE=MTE;
    }

    void updateFE(){
        this->FE=FE;
    }
    
    void updateLabAttendance(int labAttendance){
        this->labAttendance=labAttendance;
    }

    void updateCourseAttendance(int courseAttendance){
        this->courseAttendance=courseAttendance;
    }

//other methods

    float getLabGrade() const{
        return (LT1+LT2)/2;
    }

    float getFinalGrade() const{
        if(FE==-1){
            return -1;//will print N/A
        }
        else
            return (this->getLabGrade()*0.3 + MTE*0.2 + FE*0.5);
    }

    bool examEntrance(){
        if(labAttendance>=10 && courseAttendance>=5 && getLabGrade() >=5)
            return true;//will be able to enter exam
    }

    bool passStatus(){
        if(getFinalGrade>=5){
            return true;
        }
        else{
            return false;
        }
    }

    friend std::string getAbbreviatedNameOfFaculty();//make the abreviate function friend

};

class Program{
private:
    std::string name;
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
        const std::string& name, std::unordered_set<Student> students,
        std::unordered_set<Subject> subjectsForSem1, std::unordered_set<Subject> subjectsForSem2,
        std::unordered_set<Subject> subjectsForSem3, std::unordered_set<Subject> subjectsForSem4,
        std::unordered_set<Subject> subjectsForSem5, std::unordered_set<Subject> subjectsForSem6
    )
    : name(name), students(students), subjectsForSem1(subjectsForSem1), subjectsForSem2(subjectsForSem2),
    subjectsForSem3(subjectsForSem3), subjectsForSem4(subjectsForSem4), subjectsForSem5(subjectsForSem5), subjectsForSem6(subjectsForSem6){}

//accessor methods

    std::string getNameOfProgram() const{
        return name;
    }

    std::unordered_set<Subject> getSubjectsForASemester(int s) const{
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
    }//when printed, the subjects should be numbered 1. 2. 3. each on a new line

//update methods

    void changeProgramName(const std::string& newname){
        name=newname;
    }

    void addStudent(Student h){
        student.append(h);
    }

//other methods

    int getNumberOfStudentsInProgram() const{
        return students.size(); 
    }

    friend std::string getAbbreviatedNameOfFaculty();//make the abreviate function friend

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

    int getNumberOfPrograms(){
        return programs.size;
    }

//update methods

    void changeFacultyName(const std::string& newname){
        name=newname;
    }

    void addProgram(Faculty h){
        faculties.append(h);
    }

//other methods

    int getNumberOfStudentsInFaculty() const{
        int numberofstudents=0;
        for (const auto& element : programs) {
            // Access each element using the 'element' variable
            numberofstudents+=element.getNumberOfStudentsInProgram();
        }
        return numberofstudents;
    }

    friend std::string getAbbreviatedNameOfFaculty();//make the abreviate function friend

};

class University{
private:
    std::string name;
    std::string country;
    std::string city;

    std::unordered_set<Faculty> faculties;

public:

//constructor

    University(const std::string& name, const std::string& country, const std::string& city, std::unordered_set<Faculty> faculties )
        : name(name), faculties(faculties){}


//accessor methods

    std::string getNameOfUniversity() const{
            return name;
    }

    

//acceseaza o anumita facultate, acceseaza numele

//update methods

    void changeUniversityName(std::string newname){
        name=newname;
    }

    void addFaculty(Faculty h){
        faculties.append(h);
    }

//other methods

    int getNumberOfFaculties(){
        return faculties.size;
    }
    friend std::string getAbbreviatedNameOfFaculty();//make the abreviate function friend

};

//bagi o metoda care iti numara cati studenti sunt la facultatea x, metoda sa o bagi in clasa faculty

//cauta cum se lucreaza cu sfml

std::string getAbbreviatedName(){
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
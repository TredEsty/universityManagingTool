#include<string>
#include<vector>
#include<unordered_set>
#include<iostream>
#include<fstream>
#include<sstream>
#include<filesystem>

class Student {
private:
    std::string ID;
    std::string firstName;
    std::string lastName;

    int semester;
    std::unordered_set<Subject> subjects; // Store subjects for each semester
    Program *program;
    
    bool finishedUniversity;
public:
    // Constructor
    Student(Program *program, const std::string& ID, const std::string& firstName, const std::string& lastName, int semester=1)
        : ID(ID), firstName(firstName), lastName(lastName), semester(semester), finishedUniversity(0) {}

    // Accessor methods
    std::string getID() const {
        return ID;
    }

    std::string getFirstName() const {
        return firstName;
    }

    std::string getLastName() const {
        return lastName;
    }

    int getSemester() const {
        return semester;
    }

    std::unordered_set<Subject> getSubjects() const {
        return subjects;
    }

    // Update methods

    void addSubject(const Subject& subject) {
        subjects.insert(subject);
    }

    // Other methods

//will update semester if he has enough credits, otherwise he will redo the semester,
//if he didn't pass certain subjects but has enough credits he will do the subjects again next semester
    void updateSemester() {
        std::unordered_set<Subject> nextSemesterSubjects;
        std::unordered_set<Subject> notPassedSubjects;

        int totalCredits=0;
        bool passedAll=1;

        for (const auto& subject : subjects) {
            if (!subject.passStatus()) {
                notPassedSubjects.insert(subject.resetSubject());
            }
            else {
                totalCredits+=subject.getCredits();
            }
        }
        if (totalCredits >= 120){
            semester++;
            switch (semester) {
            case 2:
                nextSemesterSubjects = program->getSubjectsForASemester(2);
                break;
            case 3:
                nextSemesterSubjects = program->getSubjectsForASemester(3);
                break;
            case 4:
                nextSemesterSubjects = program->getSubjectsForASemester(4);
                break;
            case 5:
                nextSemesterSubjects = program->getSubjectsForASemester(5);
                break;
            case 6:
                nextSemesterSubjects = program->getSubjectsForASemester(6);
                break;
            case 7:
                finishedUniversity=1;//yay
                break;
            default:
                std::cout << "Invalid semester for student: " << ID << std::endl;
                return;
            }

            if (!nextSemesterSubjects.empty()) {
                ++semester;
                subjects = nextSemesterSubjects;
                subjects.insert(notPassedSubjects.begin(), notPassedSubjects.end());
            } else {
                // Reset subjects if no subjects are available for the next semester
                subjects.clear();
            }
        }
        else {
            for (auto& subject : subjects) {
                subject.resetSubject();
            }
        }
        
    }
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
    int credits;

public:

//constructor

    Subject(const std::string& name, float LT1 = -1, float LT2 = -1, float MTE = -1, float FE = -1, int labAttendance = 0, int courseAttendance = 0, int credits=0)
    : name(name), LT1(LT1), LT2(LT2), MTE(MTE), FE(FE), labAttendance(labAttendance), courseAttendance(courseAttendance), credits(credits){}

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

    int getCredits() const {
        return credits;
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

    void resetSubject() {
        name = "";
        LT1 = -1;
        LT2 = -1;
        MTE = -1;
        FE = -1;
        labAttendance = 0;
        courseAttendance = 0;
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
        return false;//will not be able to enter exam
    }

    bool passStatus(){
        if(getFinalGrade()>=5){
            credits=5*getFinalGrade();
            return true;
        }
        else{
            return false;
        }
    }

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

};


void readData(Program& obj) {
    // Get the name of the parent folder
    std::string folderName;
    std::filesystem::path programPath = std::filesystem::path(argv[0]);
    if (std::filesystem::is_directory(programPath)) {
        // Use the name of the parent folder as the program name
        folderName = programPath.filename().string();
    }
    else {
        // Use the name of the grandparent folder as the program name
        folderName = programPath.parent_path().parent_path().filename().string();
    }
    obj.changeProgramName(folderName);

    // Read student data
    for (int i = 1; i <= 100; i++) {
        std::string filename = folderName + "/student" + std::to_string(i) + ".txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string studentID, firstName, lastName;
            // Read student data from the file
            std::getline(file, studentID);
            std::getline(file, firstName);
            std::getline(file, lastName);
            // Create a Student object and add it to the program
            Student student(studentID, firstName, lastName);
            obj.addStudent(student);
            file.close();
        }
    }

    // Read subjects data for each semester
    for (int sem = 1; sem <= 6; sem++) {
        std::string filename = folderName + "/sem" + std::to_string(sem) + ".txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            std::unordered_set<Subject>& subjects = obj.getSubjectsForASemester(sem);
            std::string subjectName;
            while (std::getline(file, subjectName)) {
                // Create a Subject object and add it to the semester's subjects
                Subject subject(subjectName);
                subjects.insert(subject);
            }
            file.close();
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------


void readData() {
    // Get the current directory path
    std::filesystem::path currentPath = std::filesystem::current_path();

    // Find the Informatica folder
    std::filesystem::path informaticaPath;
    for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
        if (entry.is_directory() && entry.path().filename() != "Informatica") {
            informaticaPath = entry.path();
            break;
        }
    }

    // Check if Informatica folder exists
    if (informaticaPath.empty()) {
        std::cout << "Informatica folder not found." << std::endl;
        return;
    }

    // Create a program with the name of the Informatica folder
    std::string programName = informaticaPath.filename().string();
    Program program(programName);

    // Read subjects for each semester
    for (int semester = 1; semester <= 6; ++semester) {
        std::filesystem::path subjectsPath = informaticaPath / ("sem" + std::to_string(semester) + ".txt");

        std::ifstream subjectsFile(subjectsPath);
        if (!subjectsFile) {
            std::cout << "Failed to open subjects file for semester " << semester << "." << std::endl;
            continue;
        }

        std::string subjectName;
        int subjectCredits;

        while (subjectsFile >> subjectName >> subjectCredits) {
            Subject subject(subjectName, subjectCredits);
            program.addSubjectForSemester(semester, subject);
        }

        subjectsFile.close();
    }

    // Read student data
    std::filesystem::path studentsPath = informaticaPath / "students";

    for (const auto& entry : std::filesystem::directory_iterator(studentsPath)) {
        if (!entry.is_regular_file())
            continue;

        std::ifstream studentFile(entry.path());
        if (!studentFile) {
            std::cout << "Failed to open student file: " << entry.path() << std::endl;
            continue;
        }

        std::string studentID;
        std::string firstName;
        std::string lastName;
        int semester;

        if (!(studentFile >> studentID >> firstName >> lastName >> semester)) {
            std::cout << "Failed to read student data from file: " << entry.path() << std::endl;
            continue;
        }

        Student student(&program, studentID, firstName, lastName, semester);

        std::string subjectName;
        int subjectCredits;

        while (studentFile >> subjectName >> subjectCredits) {
            Subject subject(subjectName, subjectCredits);
            student.addSubject(subject);
        }

        studentFile.close();

        // Update the semester
        student.updateSemester();

        // Print student information
        std::cout << "Student ID: " << student.getID() << std::endl;
        std::cout << "Name: " << student.getFirstName() << " " << student.getLastName() << std::endl;
    }
}

void readData(Program& obj) {
    // Get the name of the parent folder
    std::string folderName;
    std::filesystem::path programPath = std::filesystem::path(argv[0]);

    if (std::filesystem::is_directory(programPath)) {
        // Use the name of the parent folder as the program name
        folderName = programPath.filename().string();
    }
    else {
        // Use the name of the grandparent folder as the program name
        folderName = programPath.parent_path().parent_path().filename().string();
    }
    obj.changeProgramName(folderName);

    // Read student data
    for (int i = 1; i <= 100; i++) {
        std::string filename = folderName + "/student" + std::to_string(i) + ".txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string studentID, firstName, lastName;
            // Read student data from the file
            std::getline(file, studentID);
            std::getline(file, firstName);
            std::getline(file, lastName);
            // Create a Student object and add it to the program
            Student student(obj, studentID, firstName, lastName);
            obj.addStudent(student);
            file.close();
        }
    }

    // Read subjects data for each semester
    for (int sem = 1; sem <= 6; sem++) {
        std::string filename = folderName + "/sem" + std::to_string(sem) + ".txt";
        std::ifstream file(filename);
        if (file.is_open()) {
            std::unordered_set<Subject>& subjects = obj.getSubjectsForASemester(sem);
            std::string subjectName;
            while (std::getline(file, subjectName)) {
                // Create a Subject object and add it to the semester's subjects
                Subject subject(subjectName);
                subjects.insert(subject);
            }
            file.close();
        }
    }
}


    for (const auto& entry : std::filesystem::directory_iterator(parentPath)) {
        if (entry.is_directory()) {
            std::string folderName = entry.path().filename().string();
            std::cout << "Folder Name: " << folderName << std::endl;
        }
    }



//In this updated version, the program checks if the path of the executable is a directory.
//If it is, it uses the name of the "Informatica" folder as the program name.
//Otherwise, it uses the name of the parent folder.
//The student data is read from the "Informatica" folder using the path "Informatica/studentX.txt",
//and the subject data is read from the "Informatica" folder using the path "Informatica/semX.txt".

//Please ensure that the "Informatica" folder is located in the same directory as the executable file when running the program.


/*

project folder:
    Program
        detalii:
        adica orice nume de program, nu citim dupa un anumit nume,
        daca e Informatica programul citeste din folderul informatica,
        daca e Pshio, citeste din pshio, se face automat selectarea
        numelui, numele folderului defineste numele obiectului de clasa Program)
    program.exe


Program(poate avea orice nume)
    students(folder)
        1(folder)(numele folderului reprezinta id-ul obiectului de clasa Student)
        2(folder)
        ...
        X(folder)
            studentdata.csv
                firstname lastname semester
            subjects
                sem1.csv (aici gasim datele studentului din semestrul 1)
                sem2.csv (aici gasim datele studentului din semestrul 2)
                ...
                sem6.csv
    curiculum.csv (tabel cu materile semestrelor, pe fiecare linie avem materile semestrului de pe linia x)

*/
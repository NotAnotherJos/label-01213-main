// Student.h - Student class declaration
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

class Student {
private:
    string studentId;    // 10-digit student ID
    string name;         // student name (max 8 chars)
    int age;             // student age
    char gender;         // 'M' or 'F'
    int courseCount;     // number of courses (3 or 5)
    double* scores;      // dynamic array for course scores
    double avgScore;     // average score

public:
    // Default constructor
    Student();
    
    // Parameterized constructor
    Student(string id, string n, int a, char g, int cc);
    
    // Copy constructor
    Student(const Student& other);
    
    // Assignment operator
    Student& operator=(const Student& other);
    
    // Destructor
    ~Student();
    
    // Setter functions with validation
    bool setStudentId(string id);
    bool setName(string n);
    bool setAge(int a);
    bool setGender(char g);
    bool setScore(int index, double score);
    bool setCourseCount(int cc);
    
    // Getter functions
    string getStudentId() const;
    string getName() const;
    int getAge() const;
    char getGender() const;
    int getCourseCount() const;
    double getScore(int index) const;
    double getAvgScore() const;
    
    // Calculate average score - overloaded functions
    double calcAverage();                      // all courses
    double calcAverage(int start, int end);   // range of courses
    
    // Check if student has failed courses
    bool hasFailedCourse() const;
    
    // Display functions
    void display() const;       // full information
    void displayBrief() const;  // brief information
    
    // Input student information
    void inputInfo();
    
    // Modify student information
    void modifyInfo();
};

// Validation helper functions
bool isValidId(const string& id);
bool isValidName(const string& n);
bool isValidGender(char g);
bool isValidScore(double score);

#endif // STUDENT_H

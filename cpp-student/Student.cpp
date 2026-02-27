// Student.cpp - Student class member function implementation
#include "Student.h"

// Validation helper functions
bool isValidId(const string& id) {
    if (id.length() != 10) {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (id[i] < '0' || id[i] > '9') {
            return false;
        }
    }
    return true;
}

bool isValidName(const string& n) {
    if (n.length() == 0 || n.length() > 8) {
        return false;
    }
    return true;
}

bool isValidGender(char g) {
    return (g == 'M' || g == 'F' || g == 'm' || g == 'f');
}

bool isValidScore(double score) {
    return (score >= 0 && score <= 100);
}

// Default constructor
Student::Student() {
    studentId = "0000000000";
    name = "Unknown";
    age = 0;
    gender = 'M';
    courseCount = 0;
    scores = nullptr;
    avgScore = 0.0;
}

// Parameterized constructor
Student::Student(string id, string n, int a, char g, int cc) {
    studentId = id;
    name = n;
    age = a;
    gender = g;
    courseCount = cc;
    avgScore = 0.0;
    
    if (courseCount > 0) {
        scores = new double[courseCount];
        for (int i = 0; i < courseCount; i++) {
            scores[i] = 0.0;
        }
    } else {
        scores = nullptr;
    }
}

// Copy constructor
Student::Student(const Student& other) {
    studentId = other.studentId;
    name = other.name;
    age = other.age;
    gender = other.gender;
    courseCount = other.courseCount;
    avgScore = other.avgScore;
    
    if (courseCount > 0) {
        scores = new double[courseCount];
        for (int i = 0; i < courseCount; i++) {
            scores[i] = other.scores[i];
        }
    } else {
        scores = nullptr;
    }
}

// Assignment operator
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        delete[] scores;
        
        studentId = other.studentId;
        name = other.name;
        age = other.age;
        gender = other.gender;
        courseCount = other.courseCount;
        avgScore = other.avgScore;
        
        if (courseCount > 0) {
            scores = new double[courseCount];
            for (int i = 0; i < courseCount; i++) {
                scores[i] = other.scores[i];
            }
        } else {
            scores = nullptr;
        }
    }
    return *this;
}

// Destructor
Student::~Student() {
    delete[] scores;
    scores = nullptr;
    // Note: Author message is printed only in main() to avoid repeated output during sorting
}

// Setter functions
bool Student::setStudentId(string id) {
    if (!isValidId(id)) {
        cout << "Error: Student ID must be exactly 10 digits!" << endl;
        return false;
    }
    studentId = id;
    return true;
}

bool Student::setName(string n) {
    if (!isValidName(n)) {
        cout << "Error: Name cannot be empty and must not exceed 8 characters!" << endl;
        return false;
    }
    name = n;
    return true;
}

bool Student::setAge(int a) {
    if (a <= 0 || a > 150) {
        cout << "Error: Age must be a positive number!" << endl;
        return false;
    }
    age = a;
    return true;
}

bool Student::setGender(char g) {
    if (!isValidGender(g)) {
        cout << "Error: Gender must be M(Male) or F(Female)!" << endl;
        return false;
    }
    gender = (g == 'm') ? 'M' : ((g == 'f') ? 'F' : g);
    return true;
}

bool Student::setScore(int index, double score) {
    if (index < 0 || index >= courseCount) {
        cout << "Error: Course index out of range!" << endl;
        return false;
    }
    if (!isValidScore(score)) {
        cout << "Error: Score must be between 0 and 100!" << endl;
        return false;
    }
    scores[index] = score;
    return true;
}

bool Student::setCourseCount(int cc) {
    if (cc != 3 && cc != 5) {
        cout << "Error: Course count must be 3 or 5!" << endl;
        return false;
    }
    
    // Delete old scores array
    delete[] scores;
    
    courseCount = cc;
    scores = new double[courseCount];
    for (int i = 0; i < courseCount; i++) {
        scores[i] = 0.0;
    }
    avgScore = 0.0;
    return true;
}

// Getter functions
string Student::getStudentId() const {
    return studentId;
}

string Student::getName() const {
    return name;
}

int Student::getAge() const {
    return age;
}

char Student::getGender() const {
    return gender;
}

int Student::getCourseCount() const {
    return courseCount;
}

double Student::getScore(int index) const {
    if (index < 0 || index >= courseCount) {
        return -1;
    }
    return scores[index];
}

double Student::getAvgScore() const {
    return avgScore;
}

// Calculate average - all courses (overload 1)
double Student::calcAverage() {
    if (courseCount == 0) {
        avgScore = 0.0;
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 0; i < courseCount; i++) {
        sum += scores[i];
    }
    avgScore = sum / courseCount;
    return avgScore;
}

// Calculate average - range of courses (overload 2)
double Student::calcAverage(int start, int end) {
    if (start < 0 || end >= courseCount || start > end) {
        return -1;
    }
    
    double sum = 0.0;
    int count = end - start + 1;
    for (int i = start; i <= end; i++) {
        sum += scores[i];
    }
    return sum / count;
}

// Check if student has failed courses
bool Student::hasFailedCourse() const {
    for (int i = 0; i < courseCount; i++) {
        if (scores[i] < 60) {
            return true;
        }
    }
    return false;
}

// Display full information
void Student::display() const {
    cout << "========================================" << endl;
    cout << "Student ID    : " << studentId << endl;
    cout << "Name          : " << name << endl;
    cout << "Age           : " << age << endl;
    cout << "Gender        : " << (gender == 'M' ? "Male" : "Female") << endl;
    cout << "Course Count  : " << courseCount << endl;
    cout << "Scores        : ";
    for (int i = 0; i < courseCount; i++) {
        cout << "Course" << (i + 1) << ":" << scores[i];
        if (i < courseCount - 1) cout << ", ";
    }
    cout << endl;
    cout << "Average Score : " << avgScore << endl;
    cout << "Failed Course : " << (hasFailedCourse() ? "Yes" : "No") << endl;
    cout << "========================================" << endl;
}

// Display brief information
void Student::displayBrief() const {
    cout << studentId << "\t" << name << "\t" << gender << "\t" << avgScore << endl;
}

// Helper function to clear cin error state
static void clearCinError() {
    cin.clear();
    // Avoid infinite loop on EOF
    while (cin.peek() != '\n' && cin.peek() != EOF) {
        cin.get();
    }
    if (cin.peek() == '\n') {
        cin.get();
    }
}

// Input student information
void Student::inputInfo() {
    string tempId;
    string tempName;
    int tempAge;
    char tempGender;
    int tempCourseCount;
    
    // Input student ID
    while (true) {
        cout << "Please enter student ID (10 digits): " << flush;
        cin >> tempId;
        // Clear remaining input in buffer
        clearCinError();
        if (setStudentId(tempId)) break;
    }
    
    // Input name
    while (true) {
        cout << "Please enter name (max 8 characters): " << flush;
        cin >> tempName;
        // Clear remaining input in buffer
        clearCinError();
        if (setName(tempName)) break;
    }
    
    // Input age
    while (true) {
        cout << "Please enter age: " << flush;
        cin >> tempAge;
        if (cin.fail()) {
            clearCinError();
            cout << "Error: Please enter a valid number!" << endl;
            continue;
        }
        if (setAge(tempAge)) break;
    }
    
    // Input gender
    while (true) {
        cout << "Please enter gender (M/F): " << flush;
        cin >> tempGender;
        // Clear remaining input in buffer
        clearCinError();
        if (setGender(tempGender)) break;
    }
    
    // Input course count
    while (true) {
        cout << "Please enter student type (1 for 5 courses, 2 for 3 courses): " << flush;
        int type;
        cin >> type;
        if (cin.fail()) {
            clearCinError();
            cout << "Error: Please enter a valid number!" << endl;
            continue;
        }
        if (type == 1) {
            tempCourseCount = 5;
        } else if (type == 2) {
            tempCourseCount = 3;
        } else {
            cout << "Error: Please enter 1 or 2!" << endl;
            continue;
        }
        if (setCourseCount(tempCourseCount)) break;
    }
    
    // Input scores
    cout << "Please enter " << courseCount << " course scores:" << endl;
    for (int i = 0; i < courseCount; i++) {
        double tempScore;
        while (true) {
            cout << "Course " << (i + 1) << " score (0-100): " << flush;
            cin >> tempScore;
            if (cin.fail()) {
                clearCinError();
                cout << "Error: Please enter a valid number!" << endl;
                continue;
            }
            if (setScore(i, tempScore)) break;
        }
    }
    
    // Calculate average
    calcAverage();
    
    cout << "Student information entered successfully!" << endl;
}

// Modify student information
void Student::modifyInfo() {
    int choice;
    cout << "\n--- Modify Student Information ---" << endl;
    cout << "1. Modify Student ID" << endl;
    cout << "2. Modify Name" << endl;
    cout << "3. Modify Age" << endl;
    cout << "4. Modify Gender" << endl;
    cout << "5. Modify All Scores" << endl;
    cout << "0. Cancel" << endl;
    cout << "Please enter your choice: " << flush;
    cin >> choice;
    
    if (cin.fail()) {
        clearCinError();
        cout << "Error: Please enter a valid number!" << endl;
        return;
    }
    
    switch (choice) {
        case 1: {
            string newId;
            cout << "Enter new student ID (10 digits): " << flush;
            cin >> newId;
            // Clear remaining input in buffer
            clearCinError();
            if (setStudentId(newId)) {
                cout << "Student ID modified successfully!" << endl;
            }
            break;
        }
        case 2: {
            string newName;
            cout << "Enter new name (max 8 characters): " << flush;
            cin >> newName;
            // Clear remaining input in buffer
            clearCinError();
            if (setName(newName)) {
                cout << "Name modified successfully!" << endl;
            }
            break;
        }
        case 3: {
            int newAge;
            cout << "Enter new age: " << flush;
            cin >> newAge;
            if (cin.fail()) {
                clearCinError();
                cout << "Error: Please enter a valid number!" << endl;
                break;
            }
            if (setAge(newAge)) {
                cout << "Age modified successfully!" << endl;
            }
            break;
        }
        case 4: {
            char newGender;
            cout << "Enter new gender (M/F): " << flush;
            cin >> newGender;
            // Clear remaining input in buffer
            clearCinError();
            if (setGender(newGender)) {
                cout << "Gender modified successfully!" << endl;
            }
            break;
        }
        case 5: {
            cout << "Enter " << courseCount << " new scores:" << endl;
            for (int i = 0; i < courseCount; i++) {
                double newScore;
                while (true) {
                    cout << "Course " << (i + 1) << " score (0-100): " << flush;
                    cin >> newScore;
                    if (cin.fail()) {
                        clearCinError();
                        cout << "Error: Please enter a valid number!" << endl;
                        continue;
                    }
                    if (setScore(i, newScore)) break;
                }
            }
            calcAverage();
            cout << "All scores modified successfully!" << endl;
            break;
        }
        case 0:
            cout << "Modification cancelled." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}

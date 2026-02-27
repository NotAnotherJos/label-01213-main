// main.cpp - Main function with menu system
#include "Student.h"

// Global variables
Student* students = nullptr;
int studentCount = 0;

// Helper function to clear cin error state
void clearInput() {
    cin.clear();
    // Avoid infinite loop on EOF
    while (cin.peek() != '\n' && cin.peek() != EOF) {
        cin.get();
    }
    if (cin.peek() == '\n') {
        cin.get();
    }
}

// Function declarations
void showMainMenu();
void inputStudents();
void showAllStudents();
void queryStudent();
void modifyStudent();
void modifySingleScore();
void showCourseStats();
void sortAndDisplay();

// Check if student ID already exists
bool isIdDuplicate(const string& id, int currentIndex) {
    for (int i = 0; i < currentIndex; i++) {
        if (students[i].getStudentId() == id) {
            return true;
        }
    }
    return false;
}

// Main function
int main() {
    int choice;
    
    cout << "============================================" << endl;
    cout << "    Welcome to Student Management System    " << endl;
    cout << "============================================" << endl;
    
    // Input number of students
    while (true) {
        cout << "\nPlease enter the number of students (1-100): " << flush;
        cin >> studentCount;
        if (cin.fail()) {
            clearInput();
            cout << "Error: Please enter a valid number!" << endl;
            continue;
        }
        if (studentCount <= 0) {
            cout << "Error: Number must be positive!" << endl;
            continue;
        }
        if (studentCount > 100) {
            cout << "Error: Maximum 100 students allowed!" << endl;
            continue;
        }
        break;
    }
    
    // Dynamically allocate memory for students
    students = new Student[studentCount];
    
    // Input all students information
    cout << "\n--- Please enter information for " << studentCount << " students ---" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << "\n>>> Entering information for Student " << (i + 1) << " <<<" << endl;
        while (true) {
            students[i].inputInfo();
            // Check for duplicate student ID
            if (isIdDuplicate(students[i].getStudentId(), i)) {
                cout << "Error: Student ID already exists! Please enter again." << endl;
                continue;
            }
            break;
        }
    }
    
    // Main menu loop
    while (true) {
        showMainMenu();
        cout << "Please enter your choice: " << flush;
        cin >> choice;
        
        if (cin.fail()) {
            clearInput();
            cout << "Error: Please enter a valid number!" << endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                showAllStudents();
                break;
            case 2:
                queryStudent();
                break;
            case 3:
                modifyStudent();
                break;
            case 4:
                modifySingleScore();
                break;
            case 5:
                showCourseStats();
                break;
            case 6:
                sortAndDisplay();
                break;
            case 0:
                cout << "\nExiting program..." << endl;
                // Release memory - destructor will be called
                delete[] students;
                students = nullptr;
                cout << "Thank you for using Student Management System!" << endl;
                cout << "This program is written by Zhang San" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}

// Show main menu
void showMainMenu() {
    cout << "\n============================================" << endl;
    cout << "           Student Management Menu          " << endl;
    cout << "============================================" << endl;
    cout << "  1. Display All Students" << endl;
    cout << "  2. Query Student (by ID or Name)" << endl;
    cout << "  3. Modify Student Information" << endl;
    cout << "  4. Modify Single Course Score" << endl;
    cout << "  5. Show Course Statistics" << endl;
    cout << "  6. Sort and Display Students" << endl;
    cout << "  0. Exit Program" << endl;
    cout << "============================================" << endl;
}

// Display all students
void showAllStudents() {
    cout << "\n============================================" << endl;
    cout << "           All Students Information         " << endl;
    cout << "============================================" << endl;
    
    for (int i = 0; i < studentCount; i++) {
        cout << "\n--- Student " << (i + 1) << " ---" << endl;
        students[i].display();
    }
}

// Query student by ID or name
void queryStudent() {
    cout << "\n--- Query Student ---" << endl;
    cout << "1. Query by Student ID" << endl;
    cout << "2. Query by Name" << endl;
    cout << "Please enter your choice: " << flush;
    
    int choice;
    cin >> choice;
    
    if (cin.fail()) {
        clearInput();
        cout << "Error: Please enter a valid number!" << endl;
        return;
    }
    
    bool found = false;
    
    if (choice == 1) {
        string searchId;
        cout << "Enter student ID to search: " << flush;
        cin >> searchId;
        clearInput();
        
        for (int i = 0; i < studentCount; i++) {
            if (students[i].getStudentId() == searchId) {
                cout << "\nStudent found!" << endl;
                students[i].display();
                found = true;
                break;
            }
        }
    } else if (choice == 2) {
        string searchName;
        cout << "Enter name to search: " << flush;
        cin >> searchName;
        clearInput();
        
        for (int i = 0; i < studentCount; i++) {
            if (students[i].getName() == searchName) {
                cout << "\nStudent found!" << endl;
                students[i].display();
                found = true;
            }
        }
    } else {
        cout << "Invalid choice!" << endl;
        return;
    }
    
    if (!found) {
        cout << "No student found with the given information!" << endl;
    }
}

// Modify student information
void modifyStudent() {
    cout << "\n--- Modify Student Information ---" << endl;
    
    string searchId;
    cout << "Enter student ID to modify: " << flush;
    cin >> searchId;
    clearInput();
    
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].getStudentId() == searchId) {
            cout << "\nCurrent student information:" << endl;
            students[i].display();
            
            // Save old ID before modification
            string oldId = students[i].getStudentId();
            students[i].modifyInfo();
            
            // Check if ID was changed and is now duplicate
            string newId = students[i].getStudentId();
            if (newId != oldId) {
                // Check if new ID duplicates another student
                for (int j = 0; j < studentCount; j++) {
                    if (j != i && students[j].getStudentId() == newId) {
                        cout << "Error: This student ID already exists! Reverting to original ID." << endl;
                        students[i].setStudentId(oldId);
                        break;
                    }
                }
            }
            
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "No student found with ID: " << searchId << endl;
    }
}

// Modify single course score
void modifySingleScore() {
    cout << "\n--- Modify Single Course Score ---" << endl;
    
    string searchId;
    cout << "Enter student ID: " << flush;
    cin >> searchId;
    clearInput();
    
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].getStudentId() == searchId) {
            found = true;
            cout << "\nStudent found: " << students[i].getName() << endl;
            cout << "This student has " << students[i].getCourseCount() << " courses." << endl;
            cout << "Current scores: ";
            for (int j = 0; j < students[i].getCourseCount(); j++) {
                cout << "Course" << (j + 1) << ":" << students[i].getScore(j);
                if (j < students[i].getCourseCount() - 1) cout << ", ";
            }
            cout << endl;
            
            int courseIndex;
            double newScore;
            
            while (true) {
                cout << "Enter course number to modify (1-" << students[i].getCourseCount() << "): " << flush;
                cin >> courseIndex;
                if (cin.fail()) {
                    clearInput();
                    cout << "Error: Please enter a valid number!" << endl;
                    continue;
                }
                if (courseIndex >= 1 && courseIndex <= students[i].getCourseCount()) {
                    break;
                }
                cout << "Error: Invalid course number!" << endl;
            }
            
            while (true) {
                cout << "Enter new score (0-100): " << flush;
                cin >> newScore;
                if (cin.fail()) {
                    clearInput();
                    cout << "Error: Please enter a valid number!" << endl;
                    continue;
                }
                if (students[i].setScore(courseIndex - 1, newScore)) {
                    students[i].calcAverage();
                    cout << "Score modified successfully!" << endl;
                    cout << "New average score: " << students[i].getAvgScore() << endl;
                    break;
                }
            }
            break;
        }
    }
    
    if (!found) {
        cout << "No student found with ID: " << searchId << endl;
    }
}

// Show course statistics
void showCourseStats() {
    cout << "\n============================================" << endl;
    cout << "           Course Statistics                " << endl;
    cout << "============================================" << endl;
    
    // Find max course count
    int maxCourses = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].getCourseCount() > maxCourses) {
            maxCourses = students[i].getCourseCount();
        }
    }
    
    // Calculate statistics for each course
    for (int c = 0; c < maxCourses; c++) {
        double sum = 0;
        double maxScore = -1;
        double minScore = 101;
        int count = 0;
        
        for (int i = 0; i < studentCount; i++) {
            if (c < students[i].getCourseCount()) {
                double score = students[i].getScore(c);
                sum += score;
                count++;
                if (score > maxScore) maxScore = score;
                if (score < minScore) minScore = score;
            }
        }
        
        if (count > 0) {
            cout << "\nCourse " << (c + 1) << ":" << endl;
            cout << "  Average Score : " << (sum / count) << endl;
            cout << "  Highest Score : " << maxScore << endl;
            cout << "  Lowest Score  : " << minScore << endl;
            cout << "  Student Count : " << count << endl;
        }
    }
    
    // Show students with failed courses
    cout << "\n--- Students with Failed Courses ---" << endl;
    bool hasFailedStudents = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].hasFailedCourse()) {
            cout << "ID: " << students[i].getStudentId() 
                 << ", Name: " << students[i].getName() << endl;
            hasFailedStudents = true;
        }
    }
    if (!hasFailedStudents) {
        cout << "No student has failed courses." << endl;
    }
}

// Sort and display
void sortAndDisplay() {
    cout << "\n--- Sort and Display Students ---" << endl;
    cout << "1. Sort by Student ID (Ascending)" << endl;
    cout << "2. Sort by Student ID (Descending)" << endl;
    cout << "3. Sort by Average Score (Ascending)" << endl;
    cout << "4. Sort by Average Score (Descending)" << endl;
    cout << "Please enter your choice: " << flush;
    
    int choice;
    cin >> choice;
    
    if (cin.fail()) {
        clearInput();
        cout << "Error: Please enter a valid number!" << endl;
        return;
    }
    
    // Create index array for sorting (avoid copying Student objects)
    int* indices = new int[studentCount];
    for (int i = 0; i < studentCount; i++) {
        indices[i] = i;
    }
    
    switch (choice) {
        case 1:
            // Sort by ID ascending
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = 0; j < studentCount - 1 - i; j++) {
                    if (students[indices[j]].getStudentId() > students[indices[j + 1]].getStudentId()) {
                        int temp = indices[j];
                        indices[j] = indices[j + 1];
                        indices[j + 1] = temp;
                    }
                }
            }
            cout << "\n--- Sorted by Student ID (Ascending) ---" << endl;
            break;
        case 2:
            // Sort by ID descending
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = 0; j < studentCount - 1 - i; j++) {
                    if (students[indices[j]].getStudentId() < students[indices[j + 1]].getStudentId()) {
                        int temp = indices[j];
                        indices[j] = indices[j + 1];
                        indices[j + 1] = temp;
                    }
                }
            }
            cout << "\n--- Sorted by Student ID (Descending) ---" << endl;
            break;
        case 3:
            // Sort by average ascending
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = 0; j < studentCount - 1 - i; j++) {
                    if (students[indices[j]].getAvgScore() > students[indices[j + 1]].getAvgScore()) {
                        int temp = indices[j];
                        indices[j] = indices[j + 1];
                        indices[j + 1] = temp;
                    }
                }
            }
            cout << "\n--- Sorted by Average Score (Ascending) ---" << endl;
            break;
        case 4:
            // Sort by average descending
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = 0; j < studentCount - 1 - i; j++) {
                    if (students[indices[j]].getAvgScore() < students[indices[j + 1]].getAvgScore()) {
                        int temp = indices[j];
                        indices[j] = indices[j + 1];
                        indices[j + 1] = temp;
                    }
                }
            }
            cout << "\n--- Sorted by Average Score (Descending) ---" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            delete[] indices;
            return;
    }
    
    // Display sorted list using indices
    cout << "\nRank\tStudent ID\tName\t\tGender\tAverage" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << (i + 1) << "\t" 
             << students[indices[i]].getStudentId() << "\t" 
             << students[indices[i]].getName() << "\t\t" 
             << students[indices[i]].getGender() << "\t" 
             << students[indices[i]].getAvgScore() << endl;
    }
    cout << "------------------------------------------------------------" << endl;
    
    delete[] indices;
}


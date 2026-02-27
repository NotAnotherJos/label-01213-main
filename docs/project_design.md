# Student Management System - Project Design

## System Architecture

```mermaid
flowchart TD
    A[main.cpp] --> B[Student Class]
    B --> C[Student.h - Declaration]
    B --> D[Student.cpp - Implementation]
    
    subgraph Core Functions
        E[Add Student]
        F[Modify Student Info]
        G[Calculate Average Score]
        H[Course Statistics]
        I[Query Student]
        J[Sort and Display]
    end
    
    A --> E
    A --> F
    A --> G
    A --> H
    A --> I
    A --> J
```

## Class Diagram

```mermaid
classDiagram
    class Student {
        -string studentId
        -string name
        -int age
        -char gender
        -int courseCount
        -double* scores
        -double avgScore
        +Student()
        +Student(string id, string n, int a, char g, int cc)
        +~Student()
        +setStudentId(string id) bool
        +setName(string n) bool
        +setAge(int a) bool
        +setGender(char g) bool
        +setScore(int index, double score) bool
        +getStudentId() string
        +getName() string
        +getAge() int
        +getGender() char
        +getCourseCount() int
        +getScore(int index) double
        +getAvgScore() double
        +calcAverage() double
        +calcAverage(int start, int end) double
        +hasFailedCourse() bool
        +display() void
        +displayBrief() void
    }
```

## File Structure

```
cpp-student/
├── Student.h      # Student class declaration
├── Student.cpp    # Student class member function implementation
└── main.cpp       # Main function with menu system
```

## API/Function List

### Student Class (Student.h / Student.cpp)

| Function | Description |
|----------|-------------|
| `Student()` | Default constructor |
| `Student(id, name, age, gender, courseCount)` | Parameterized constructor |
| `~Student()` | Destructor - releases memory and prints author info |
| `setStudentId(id)` | Set student ID with validation (10 digits) |
| `setName(name)` | Set name with validation (max 8 chars) |
| `setAge(age)` | Set age with validation |
| `setGender(gender)` | Set gender (M/F only) |
| `setScore(index, score)` | Set single course score (0-100) |
| `calcAverage()` | Calculate average of all courses (overload 1) |
| `calcAverage(start, end)` | Calculate average of courses in range (overload 2) |
| `hasFailedCourse()` | Check if any course score < 60 |
| `display()` | Display full student information |
| `displayBrief()` | Display brief info (ID, name, gender, average) |

### Main Function Features (main.cpp)

| Function | Description |
|----------|-------------|
| `inputStudents()` | Input n students from keyboard |
| `modifyStudent()` | Modify student information |
| `modifySingleScore()` | Modify single course score |
| `showAllStudents()` | Display all students |
| `queryByIdOrName()` | Query student by ID or name |
| `showCourseStats()` | Show course statistics (avg, max, min) |
| `sortByIdAsc()` | Sort by student ID ascending |
| `sortByIdDesc()` | Sort by student ID descending |
| `sortByAvgAsc()` | Sort by average score ascending |
| `sortByAvgDesc()` | Sort by average score descending |

## Data Validation Rules

1. **Student ID**: Must be exactly 10 digits (0-9)
2. **Name**: Maximum 8 characters (English only in code)
3. **Gender**: Only 'M' (Male) or 'F' (Female)
4. **Score**: Must be between 0 and 100 (inclusive)
5. **Age**: Must be positive integer

## Student Types

- **Type A**: 5 courses
- **Type B**: 3 courses

## UI/UX Design

- Console-based menu system
- Clear prompts for all inputs
- Formatted table output for student lists
- Error messages for invalid inputs
- Confirmation messages for successful operations

// A simple C++17 program that calculates the cgpa of level 100 students from UG and GCTU
#include <iostream>
#include <vector>  // vector — to hold "list of courses selected" dynamically (student can pick different numbers of courses)
#include <string>  // to store names, student ids, name of school, course codes/names
#include <iomanip> //formatting final cgpa output
#include <cctype>  //id validation function
using namespace std;

struct Course
{
    string code;
    string name;
    int creditHours;
    string letterGrade;
    double gradePoint;
};

// function prototypes
int selectUniversity();
string inputName();
string inputStudentID(int uniChoice);
bool validateStudentID(int uniChoice, string id);
vector<Course> getCourseList(int uniChoice);
vector<Course> selectCourses(vector<Course> allCourses);
void scoreToGrade(double score, string &letterGrade, double &gradePoint);
vector<Course> assignGrades(vector<Course> gradedCourses);
double calculateCGPA(vector<Course> selectedCourses);
string classifyDegree(double cgpa);
void displaySummary(string name, string studentID, int uniChoice, vector<Course> gradedCourses, double cgpa);

int selectUniversity()
{
    int choice;
    bool valid = false;

    while (!valid)
    {
        cout << "Select University:\n";
        cout << "1. UG\n";
        cout << "2. GCTU\n";
        cin >> choice;

        if (choice == 1 || choice == 2)
            valid = true;
        else
            cout << "Invalid choice. Please enter 1 or 2.\n";
    }

    return choice;
}

string inputName()
{
    string name;
    cout << "Enter your name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, name);
    return name;
}

string inputStudentID(int uniChoice)
{
    string id;
    bool valid = false;

    while (!valid)
    {
        cout << "Enter your student ID: ";
        cin >> id;

        valid = validateStudentID(uniChoice, id);

        if (!valid)
        {
            cout << "Invalid student ID format for your selected University. Please try again.\n";
        }
    }
    return id;
}

bool validateStudentID(int uniChoice, string id)
{
    if (uniChoice == 1)
    {
        if (id.length() != 10)
            return false;
        if (id.substr(0, 6) != "UG2026")
            return false;

        // remaining 4 characters should be digits
        for (int i = 6; i < 10; ++i)
        {
            if (!isdigit(id[i]))
                return false;
        }

        return true;
    }

    else if (uniChoice == 2)
    {
        if (id.length() != 10)
            return false;
        if (id.substr(0, 6) != "252640")
            return false;

        // all 10 characters should be digits
        for (int i = 0; i < 10; i++)
        {
            if (!isdigit(id[i]))
                return false;
        }

        return true;
    }

    return false; // Invalid university choice
}

vector<Course> getCourseList(int uniChoice)
{
    vector<Course> courses;

    if (uniChoice == 1)
    {
        courses = {
            {"CS101", "Introduction to Computer Science", 3},
            {"CS102", "Computer Systems Fundamentals", 3},
            {"MATH101", "Applied Mathematics", 3},
            {"ENG101", "Communicative English", 2},
            {"CS103", "Digital Logic Design", 3}};
    }

    else if (uniChoice == 2)
    {
        courses = {
            {"CSSD111", "Introduction to Computer Science", 3},
            {"CSSD101", "Programming and Problem Solving", 3},
            {"MATH103", "Discrete Mathematics", 3},
            {"MATH105", "Linear Algebra", 3},
            {"ENGL171", "Communication Skills I", 2},
            {"FREN171", "Basic French I", 3},
            {"CSNS141", "Digital Electronics", 3},
        };
    }

    return courses;
}

vector<Course> selectCourses(vector<Course> allCourses)
{
    vector<Course> selected;
    vector<int> chosenIndices; // tracks which courses have already been picked

    cout << "\nAvailable Courses:\n";
    for (int i = 0; i < allCourses.size(); i++)
    {
        cout << i + 1 << ". " << allCourses[i].code << " - " << allCourses[i].name
             << " (" << allCourses[i].creditHours << " credit hours)\n";
    }

    cout << "\nHow many courses did you take this semester? ";
    int numCourses;
    bool validCount = false;

    while (!validCount)
    {
        cin >> numCourses;

        if (numCourses >= 1 && numCourses <= allCourses.size())
            validCount = true;
        else
            cout << "Please enter a number between 1 and " << allCourses.size() << ": ";
    }

    for (int i = 0; i < numCourses; i++)
    {
        int courseChoice;
        bool valid = false;

        while (!valid)
        {
            cout << "Enter course number " << (i + 1) << ": ";
            cin >> courseChoice;

            if (courseChoice < 1 || courseChoice > allCourses.size())
            {
                cout << "Invalid course number. Please choose between 1 and " << allCourses.size() << ".\n";
                continue;
            }

            // check for duplicates
            bool alreadyChosen = false;
            for (int j = 0; j < chosenIndices.size(); j++)
            {
                if (chosenIndices[j] == courseChoice)
                {
                    alreadyChosen = true;
                    break;
                }
            }

            if (alreadyChosen)
                cout << "You've already selected that course. Choose a different one.\n";
            else
                valid = true;
        }

        chosenIndices.push_back(courseChoice);
        selected.push_back(allCourses[courseChoice - 1]);
    }

    return selected;
}

void scoreToGrade(double score, string &letterGrade, double &gradePoint)
{
    if (score >= 80 && score <= 100)
    {
        letterGrade = "A";
        gradePoint = 4.00;
    }
    else if (score >= 75)
    {
        letterGrade = "A-";
        gradePoint = 3.75;
    }
    else if (score >= 70)
    {
        letterGrade = "B+";
        gradePoint = 3.50;
    }
    else if (score >= 65)
    {
        letterGrade = "B";
        gradePoint = 3.25;
    }
    else if (score >= 60)
    {
        letterGrade = "B-";
        gradePoint = 3.00;
    }
    else if (score >= 55)
    {
        letterGrade = "C+";
        gradePoint = 2.75;
    }
    else if (score >= 50)
    {
        letterGrade = "C";
        gradePoint = 2.50;
    }
    else if (score >= 45)
    {
        letterGrade = "C-";
        gradePoint = 2.00;
    }
    else if (score >= 40)
    {
        letterGrade = "D";
        gradePoint = 1.50;
    }
    else
    {
        letterGrade = "F";
        gradePoint = 0.00;
    }
}

vector<Course> assignGrades(vector<Course> selectedCourses)
{
    for (int i = 0; i < selectedCourses.size(); i++)
    {
        cout << "\nCourse: " << selectedCourses[i].code << " - " << selectedCourses[i].name << "\n";

        double score;
        bool valid = false;

        while (!valid)
        {
            cout << "Enter your score (0-100): ";
            cin >> score;

            if (score >= 0 && score <= 100)
                valid = true;
            else
                cout << "Invalid score. Please enter a value between 0 and 100.\n";
        }

        string letterGrade;
        double gradePoint;
        scoreToGrade(score, letterGrade, gradePoint);

        selectedCourses[i].gradePoint = gradePoint;
        selectedCourses[i].letterGrade = letterGrade;
    }

    return selectedCourses;
}

double calculateCGPA(vector<Course> selectedCourses)
{
    double totalQualityPoints = 0.0;
    int totalCreditHours = 0;

    for (int i = 0; i < selectedCourses.size(); i++)
    {
        totalQualityPoints += selectedCourses[i].creditHours * selectedCourses[i].gradePoint;
        totalCreditHours += selectedCourses[i].creditHours;
    }

    if (totalCreditHours == 0)
        return 0.0; // avoid dividing by zero if somehow no courses were selected

    return totalQualityPoints / totalCreditHours;
}

string classifyDegree(double cgpa)
{
    if (cgpa >= 3.60)
        return "First Class Honours";
    else if (cgpa >= 3.00)
        return "Second Class Honours (Upper Division)";
    else if (cgpa >= 2.50)
        return "Second Class Honours (Lower Division)";
    else if (cgpa >= 2.00)
        return "Third Class Honours";
    else if (cgpa >= 1.50)
        return "Pass";
    else
        return "Fail (No Award)";
}

void displaySummary(string name, string studentID, int uniChoice, vector<Course> gradedCourses, double cgpa)
{
    string universityName = (uniChoice == 1) ? "University of Ghana (Legon)" : "GCTU";
    string degreeClassification = classifyDegree(cgpa);

    cout << "\n===================================\n";
    cout << "         CGPA SUMMARY REPORT\n";
    cout << "===================================\n";
    cout << "Name: " << name << "\n";
    cout << "Student ID: " << studentID << "\n";
    cout << "University: " << universityName << "\n";
    cout << "-----------------------------------\n";
    cout << "Courses Taken:\n";

    for (int i = 0; i < gradedCourses.size(); i++)
    {
        cout << gradedCourses[i].code << " - " << gradedCourses[i].name
             << " | Credit Hours: " << gradedCourses[i].creditHours
             << " | Grade: " << gradedCourses[i].letterGrade
             << " (" << fixed << setprecision(2) << gradedCourses[i].gradePoint << ")\n";
    }

    cout << "-----------------------------------\n";
    cout << "Final CGPA: " << fixed << setprecision(2) << cgpa << "\n";
    cout << "===================================\n";
}

int main()
{
    int uniChoice = selectUniversity();
    string name = inputName();
    string studentID = inputStudentID(uniChoice);

    vector<Course> allCourses = getCourseList(uniChoice);
    vector<Course> selected = selectCourses(allCourses);
    vector<Course> graded = assignGrades(selected);

    double cgpa = calculateCGPA(graded);

    displaySummary(name, studentID, uniChoice, graded, cgpa);

    return 0;
}
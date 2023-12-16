#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

struct Employee {
    int age;
    string gender;
    string educationLevel;
    string jobTitle;
    int yearsOfExperience;
    double salary;
};

struct CompareSalary {
    bool operator()(const Employee& emp1, const Employee& emp2) const {
        return emp1.salary < emp2.salary;
    }
};

int main() {
    const int MAX_EMPLOYEES = 500;
    Employee employees[MAX_EMPLOYEES];

    // Read employee data from CSV file
    ifstream file("employee.csv");
    if (!file) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    string line;
    int index = 0;
    while (getline(file, line) && index < MAX_EMPLOYEES) {
        stringstream ss(line);
        string cell;

        // Read each column of the CSV line into employee struct
        getline(ss, cell, ',');
        stringstream(cell) >> employees[index].age;

        getline(ss, cell, ',');
        employees[index].gender = cell;

        getline(ss, cell, ',');
        employees[index].educationLevel = cell;

        getline(ss, cell, ',');
        employees[index].jobTitle = cell;

        getline(ss, cell, ',');
        stringstream(cell) >> employees[index].yearsOfExperience;

        getline(ss, cell, ',');
        stringstream(cell) >> employees[index].salary;

        index++;
    }
    file.close();

    // Create and populate the priority queue based on salary
    priority_queue<Employee, vector<Employee>, CompareSalary> priorityQueue;
    for (int i = 0; i < index; i++) {
        priorityQueue.push(employees[i]);
    }

    // Perform dequeue operations (display all employee data)
    while (!priorityQueue.empty()) {
        Employee emp = priorityQueue.top();
        cout << "Employee details:" << endl;
        cout << "Age: " << emp.age << endl;
        cout << "Gender: " << emp.gender << endl;
        cout << "Education Level: " << emp.educationLevel << endl;
        cout << "Job Title: " << emp.jobTitle << endl;
        cout << "Years of Experience: " << emp.yearsOfExperience << endl;
        cout << "Salary: " << emp.salary << endl;
        cout << endl;
        priorityQueue.pop();
    }

    return 0;
}


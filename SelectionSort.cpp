#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Employee {
    int age;
    string gender;
    string educationLevel;
    string jobTitle;
    int yearsOfExperience;
    double salary;
};

void selectionSort(Employee* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].age < arr[minIndex].age) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

double calculateAverageSalary(Employee* employees, int numEmployees) {
    double totalSalary = 0.0;

    for (int i = 0; i < numEmployees; i++) {
        totalSalary += employees[i].salary;
    }

    return totalSalary / numEmployees;
}

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

    // Sort employees based on age using selection sort
    selectionSort(employees, index);

    // Display employees in ascending order based on age
    cout << "Employees sorted by age:" << endl;
    for (int i = 0; i < index; i++) {
        cout << "Employee " << i + 1 << ":" << endl;
        cout << "Age: " << employees[i].age << endl;
        cout << "Gender: " << employees[i].gender << endl;
        cout << "Education Level: " << employees[i].educationLevel << endl;
        cout << "Job Title: " << employees[i].jobTitle << endl;
        cout << "Years of Experience: " << employees[i].yearsOfExperience << endl;
        cout << "Salary: " << employees[i].salary << endl;
        cout << endl;
    }

    return 0;
}

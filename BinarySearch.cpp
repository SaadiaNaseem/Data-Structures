#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Employee {
    int age;
    std::string gender;
    std::string educationLevel;
    std::string jobTitle;
    int yearsOfExperience;
    double salary;
};

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
    std::ifstream file("employee.csv");
    if (!file) {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    std::string line;
    int index = 0;
    while (std::getline(file, line) && index < MAX_EMPLOYEES) {
        std::stringstream ss(line);
        std::string cell;

        // Read each column of the CSV line into employee struct
        std::getline(ss, cell, ',');
        std::stringstream(cell) >> employees[index].age;

        std::getline(ss, cell, ',');
        employees[index].gender = cell;

        std::getline(ss, cell, ',');
        employees[index].educationLevel = cell;

        std::getline(ss, cell, ',');
        employees[index].jobTitle = cell;

        std::getline(ss, cell, ',');
        std::stringstream(cell) >> employees[index].yearsOfExperience;

        std::getline(ss, cell, ',');
        std::stringstream(cell) >> employees[index].salary;

        index++;
    }
    file.close();

    // Search employees based on target salary
    double targetSalary;
    std::cout << "Enter target salary: ";
    std::cin >> targetSalary;

    bool found = false;
    for (int i = 0; i < MAX_EMPLOYEES; i++) {
        if (employees[i].salary >= targetSalary) {
            std::cout << "Employee " << i + 1 << ":" << std::endl;
            std::cout << "Age: " << employees[i].age << std::endl;
            std::cout << "Gender: " << employees[i].gender << std::endl;
            std::cout << "Education Level: " << employees[i].educationLevel << std::endl;
            std::cout << "Job Title: " << employees[i].jobTitle << std::endl;
            std::cout << "Years of Experience: " << employees[i].yearsOfExperience << std::endl;
            std::cout << "Salary: " << employees[i].salary << std::endl;
            std::cout << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No employees found with a salary greater than or equal to the target." << std::endl;
    }

    return 0;
}

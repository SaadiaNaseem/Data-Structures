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

void merge(Employee* arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Employee* L = new Employee[n1];
    Employee* R = new Employee[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i].age <= R[j].age) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Employee* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
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

    // Sort employees based on age using merge sort
    mergeSort(employees, 0, index - 1);

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

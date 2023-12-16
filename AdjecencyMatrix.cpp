#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct Employee {
    int age;
    string gender;
    string educationLevel;
    string jobTitle;
    int yearsOfExperience;
    double salary;
};

const int MAX_EMPLOYEES = 500;

// Function to populate the adjacency matrix
void populateAdjacencyMatrix(bool adjacencyMatrix[][MAX_EMPLOYEES], const Employee employees[], int numEmployees) {
    // Your logic to populate the adjacency matrix goes here
    // Example: Assuming you want to create a matrix based on the age of employees
    for (int i = 0; i < numEmployees; i++) {
        for (int j = 0; j < numEmployees; j++) {
            if (employees[i].age == employees[j].age && i != j) {
                adjacencyMatrix[i][j] = true;
                adjacencyMatrix[j][i] = true;  // Assuming an undirected graph
            }
        }
    }
}


int main() {
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

    // Create adjacency matrix
    const int numEmployees = index;  // Actual number of employees read
    bool adjacencyMatrix[MAX_EMPLOYEES][MAX_EMPLOYEES] = {false};

    // Populate the adjacency matrix
    populateAdjacencyMatrix(adjacencyMatrix, employees, numEmployees);

    // Print adjacency matrix
    for (int i = 0; i < numEmployees; i++) {
    	cout<<"adgecency matrix of emeloyee "<< i+1 <<"is : "<<endl;
        for (int j = 0; j < numEmployees; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

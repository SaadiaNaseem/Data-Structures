#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath> // Include <cmath> for the abs function

struct Employee {
    int age;
    std::string gender;
    std::string educationLevel;
    std::string jobTitle;
    int yearsOfExperience;
    double salary;
};

void createGraph(int**& graph, Employee* employees, int numEmployees) {
    // Allocate memory for the graph
    graph = new int*[numEmployees];
    for (int i = 0; i < numEmployees; i++) {
        graph[i] = new int[numEmployees];
        for (int j = 0; j < numEmployees; j++) {
            graph[i][j] = 0; // Initialize all elements to 0
        }
    }

    for (int i = 0; i < numEmployees; i++) {
        for (int j = 0; j < numEmployees; j++) {
            if (i != j) {
                if (std::abs(employees[i].age - employees[j].age) <= 5) {
                    // Establish a connection between employees i and j
                    graph[i][j] = 1;
                    graph[j][i] = 1;
                }
            }
        }
    }
}

void printGraph(int** graph, int numEmployees) {
    for (int i = 0; i < numEmployees; i++) {
    	std::cout<<"<=============================================================================================================================>";
        std::cout<<std::endl;
		std::cout << "Connections for Employee " << i + 1 << ": ";
        for (int j = 0; j < numEmployees; j++) {
            if (graph[i][j] == 1) {
                std::cout << j + 1 << " ->";
            }
        }
        std::cout << std::endl;
    }
}

void deleteGraph(int**& graph, int numEmployees) {
    for (int i = 0; i < numEmployees; i++) {
        delete[] graph[i];
    }
    delete[] graph;
    graph = NULL;
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

    // Create the graph
    int** graph = NULL;
    createGraph(graph, employees, index);

    // Display the graph
    printGraph(graph, index);

    // Clean up memory
    deleteGraph(graph, index);

    return 0;
}


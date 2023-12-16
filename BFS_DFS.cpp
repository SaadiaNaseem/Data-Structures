#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <deque>

struct Employee {
    int age;
    std::string gender;
    std::string educationLevel;
    std::string jobTitle;
    int yearsOfExperience;
    double salary;
};

class BFSDFS {
    static const int MAX_SIZE = 500;
    int adjacencyMatrix[MAX_SIZE][MAX_SIZE];

public:
    BFSDFS() {
        for (int i = 0; i < MAX_SIZE; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int source, int destination, int salary) {
        adjacencyMatrix[source][destination] = salary;
        adjacencyMatrix[destination][source] = salary;
    }

    void printGraph() {
        for (int i = 0; i < MAX_SIZE; i++) {
            std::cout << "Vertex " << i << " connections: "<<std::endl;
            for (int j = 0; j < MAX_SIZE; j++) {
                if (adjacencyMatrix[i][j] != 0) {
                    std::cout << j << "     (" << adjacencyMatrix[i][j] << ")     ";
                }
            }
            std::cout << std::endl;
        }
    }

    void printMatrix() {
        for (int i = 0; i < MAX_SIZE; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void bfsTraversal(int startVertex) {
        bool visited[MAX_SIZE] = {false};
        std::deque<int> q;

        visited[startVertex] = true;
        q.push_back(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop_front();

            std::cout << currentVertex << "-> ";

            for (int i = 0; i < MAX_SIZE; i++) {
                if (adjacencyMatrix[currentVertex][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    q.push_back(i);
                }
            }
        }
        std::cout << std::endl;
    }

    void dfsTraversal(int startVertex) {
        bool visited[MAX_SIZE] = {false};
        std::deque<int> stack;

        stack.push_back(startVertex);

        while (!stack.empty()) {
            int currentVertex = stack.back();
            stack.pop_back();

            if (!visited[currentVertex]) {
                std::cout << currentVertex << "-> ";
                visited[currentVertex] = true;
            }
            for (int i = MAX_SIZE - 1; i >= 0; i--) {
                if (adjacencyMatrix[currentVertex][i] != 0 && !visited[i]) {
                    stack.push_back(i);
                }
            }
        }
        std::cout << std::endl;
    }
};

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

    BFSDFS graph;
    // Adding edges based on employee salaries (example)
    for (int i = 0; i < index - 1; i++) {
        for (int j = i + 1; j < index; j++) {
            if (employees[i].salary > employees[j].salary) {
                graph.addEdge(i, j, employees[i].salary);
            } else {
                graph.addEdge(j, i, employees[j].salary);
            }
        }
    }
    std::cout << std::endl;
	std::cout<<"<======================================BFS TRIVERSAL===========================================>"<<std::endl;
    graph.bfsTraversal(0);
    std::cout<<std::endl;
	std::cout<<"<=========================================DFS TRIVERSALS========================================>"<<std::endl; // Perform BFS traversal starting from vertex 0
    std::cout  <<std::endl;
    graph.dfsTraversal(0); // Perform DFS traversal starting from vertex 0

    return 0;
}


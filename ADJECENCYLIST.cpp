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

struct Node {
    int data;
    Node* next;
};

const int MAX_EMPLOYEES = 500;

// Function to populate the adjacency list
void populateAdjacencyList(Node* adjacencyList[], const Employee employees[], int numEmployees) {
    // Initialize the adjacency list
    for (int i = 0; i < numEmployees; i++) {
        adjacencyList[i] = NULL;
    }

    // Your logic to populate the adjacency list goes here
    // Example: Assuming you want to create a list based on the age of employees
    for (int i = 0; i < numEmployees; i++) {
        for (int j = 0; j < numEmployees; j++) {
            if (employees[i].age == employees[j].age && i != j) {
                // Create a new node
                Node* newNode = new Node;
                newNode->data = j;
                newNode->next = NULL;

                // Insert the new node at the beginning of the list
                if (adjacencyList[i] == NULL) {
                    adjacencyList[i] = newNode;
                } else {
                    newNode->next = adjacencyList[i];
                    adjacencyList[i] = newNode;
                }
            }
        }
    }
}

// Function to print the adjacency list
void printAdjacencyList(Node* adjacencyList[], int numEmployees) {
    for (int i = 0; i < numEmployees; i++) {
        cout << "Adjacency List for Employee " << i << ": "<<endl;
        Node* current = adjacencyList[i];
        while (current != NULL) {
            cout << current->data << "-> ";
            current = current->next;
        }
        cout << endl;
        cout<<endl;
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

    // Create adjacency list
    const int numEmployees = index;  // Actual number of employees read
    Node* adjacencyList[MAX_EMPLOYEES] = {NULL};
    cout<<endl;

    // Populate the adjacency list
    populateAdjacencyList(adjacencyList, employees, numEmployees);

    // Print adjacency list
    cout<<"linking the employ with same age to each other :"<<endl;
    printAdjacencyList(adjacencyList, numEmployees);

    return 0;
}

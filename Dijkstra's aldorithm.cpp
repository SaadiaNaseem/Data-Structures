#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <limits>
#include <vector>
#include <queue>

struct Employee {
    int age;
    std::string gender;
    std::string educationLevel;
    std::string jobTitle;
    int yearsOfExperience;
    double salary;
};

struct Edge {
    int destination;
    double weight;
};

void createGraph(std::vector<std::vector<Edge>>& graph, Employee employees[], int numEmployees) {
    graph.resize(numEmployees);
    for (int i = 0; i < numEmployees; i++) {
        for (int j = 0; j < numEmployees; j++) {
            if (i != j && std::abs(employees[i].age - employees[j].age) <= 5) {
                // Assign weight based on some criteria (e.g., years of experience)
                double weight = std::abs(employees[i].yearsOfExperience - employees[j].yearsOfExperience);
                graph[i].push_back({j, weight});
            }
        }
    }
}

void printGraph(const std::vector<std::vector<Edge>>& graph, int numEmployees) {
    for (int i = 0; i < numEmployees; i++) {
        std::cout << "Connections for Employee " << i + 1 << ": ";
        for (const Edge& edge : graph[i]) {
            std::cout << edge.destination + 1 << " (Weight: " << edge.weight << "), ";
        }
        std::cout << std::endl;
    }
}

void dijkstra(const std::vector<std::vector<Edge>>& graph, int numEmployees, int source) {
    std::vector<double> dist(numEmployees, std::numeric_limits<double>::infinity());
    std::vector<int> prev(numEmployees, -1);

    dist[source] = 0;

    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        double d = pq.top().first;
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            double weight = edge.weight;

            double newDist = dist[u] + weight;
            if (newDist < dist[v]) {
                dist[v] = newDist;
                prev[v] = u;
                pq.push({newDist, v});
            }
        }
    }

    std::cout << "Shortest paths from Employee " << source + 1 << ":\n";
    for (int i = 0; i < numEmployees; i++) {
        std::cout << "To Employee " << i + 1 << ": ";
        if (dist[i] == std::numeric_limits<double>::infinity()) {
            std::cout << "Not reachable\n";
        } else {
            std::cout << "Distance: " << dist[i] << ", Path: ";
            std::vector<int> path;
            int current = i;
            while (current != -1) {
                path.insert(path.begin(), current + 1);
                current = prev[current];
            }
            for (int j = 0; j < path.size(); j++) {
                std::cout << path[j];
                if (j < path.size() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << "\n";
        }
    }
}

int main() {
    const int MAX_EMPLOYEES = 500;
    Employee employees[MAX_EMPLOYEES];

    // Read employee data from CSV file
    std::ifstream file("employees.csv");
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

    std::vector<std::vector<Edge>> graph;
    createGraph(graph, employees, index);
    printGraph(graph, index);

    // Apply Dijkstra's algorithm
    int source = 0; // Choose the source employee
    dijkstra(graph, index, source);

    return 0;
}

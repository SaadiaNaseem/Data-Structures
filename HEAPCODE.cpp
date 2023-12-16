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

struct MinHeap {
    Employee* data;
    int capacity;
    int size;

    // Constructor
    MinHeap(int maxCapacity) {
        data = new Employee[maxCapacity];
        capacity = maxCapacity;
        size = 0;
    }

    // Destructor
    ~MinHeap() {
        delete[] data;
    }

    // Get parent index
    int parent(int i) {
        return (i - 1) / 2;
    }

    // Get left child index
    int leftChild(int i) {
        return 2 * i + 1;
    }

    // Get right child index
    int rightChild(int i) {
        return 2 * i + 2;
    }

    // Swap two employees
    void swap(Employee& emp1, Employee& emp2) {
        Employee temp = emp1;
        emp1 = emp2;
        emp2 = temp;
    }

    // Heapify the heap downward from a given index
    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < size && data[left].age < data[smallest].age)
            smallest = left;

        if (right < size && data[right].age < data[smallest].age)
            smallest = right;

        if (smallest != i) {
            swap(data[i], data[smallest]);
            heapifyDown(smallest);
        }
    }

    // Insert an employee into the heap
    void insert(const Employee& emp) {
        if (size == capacity) {
            cout << "Heap is full. Cannot insert more elements." << endl;
            return;
        }

        int i = size;
        data[i] = emp;
        size++;

        while (i != 0 && data[parent(i)].age > data[i].age) {
            swap(data[parent(i)], data[i]);
            i = parent(i);
        }
    }

    // Extract the minimum employee from the heap
    Employee extractMin() {
        if (size <= 0) {
            cout << "Heap is empty. No element to extract." << endl;
            Employee emptyEmp;
            return emptyEmp;
        }

        if (size == 1) {
            size--;
            return data[0];
        }

        Employee minEmp = data[0];
        data[0] = data[size - 1];
        size--;
        heapifyDown(0);

        return minEmp;
    }

    // Sort the data in the heap
    void sort() {
        int initialSize = size;

        for (int i = initialSize / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }

        for (int i = initialSize - 1; i > 0; i--) {
            swap(data[0], data[i]);
            size--;
            heapifyDown(0);
        }

        size = initialSize;
    }

};

void buildHeap(Employee employees[], int numEmployees) {
    // Create a min heap using the provided employees array
    MinHeap minHeap(numEmployees);
    for (int i = 0; i < numEmployees; i++) {
        minHeap.insert(employees[i]);
    }

    // Copy the sorted data back to the employees array
    for (int i = 0; i < numEmployees; i++) {
        employees[i] = minHeap.extractMin();
    }
}

void printHeap(Employee employees[], int numEmployees) {
    for (int i = 0; i < numEmployees; i++) {
        cout << "Employee " << i + 1 << ":" << endl;
        cout << "Age: " << employees[i].age << endl;
        cout << "Gender: " << employees[i].gender << endl;
        cout << "Education Level: " << employees[i].educationLevel << endl;
        cout << "Job Title: " << employees[i].jobTitle << endl;
        cout << "Years of Experience: " << employees[i].yearsOfExperience << endl;
        cout << "Salary: " << employees[i].salary << endl;
        cout << endl;
    }
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

        // Read each column of the CSV line into the employee struct
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

    // Create a min heap and insert the employee data
    MinHeap minHeap(index);
    for (int i = 0; i < index; i++) {
        minHeap.insert(employees[i]);
    }

    // Sort the data in the heap
    minHeap.sort();

    // Print the sorted heap
    cout << "Heap of Employees sorted by Age:" << endl;
    printHeap(minHeap.data, minHeap.size);

    return 0;
}

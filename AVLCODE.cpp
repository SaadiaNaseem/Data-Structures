#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

// Employee structure to store employee data
struct Employee {
    int age;
    string gender;
    string educationLevel;
    string jobTitle;
    int yearsOfExperience;
    double salary;
    Employee* next;
};

// Node structure to create a linked list of employees
struct Node {
	Employee employee;
    Node* next;
};

// Graph structure using adjacency lists
struct Graph {
    int numVertices;
    int** adjLists;
};

// Function to create the adjacency list
void createAdjacencyList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        cout << "Age: " << temp->employee.age << ", Gender: " << temp->employee.gender << ", Education Level: " << temp->employee.educationLevel << endl;
        // Display other employee information if needed
        temp = temp->next;
    }
}

// Function to convert linked list to graph representation
Graph convertToGraph(Node* head) {
    Graph graph;
    graph.numVertices = 0;

    Node* temp = head;
    while (temp != NULL) {
        graph.numVertices++;
        temp = temp->next;
    }

    // Dynamically allocate memory for the adjacency lists
    graph.adjLists = new int*[graph.numVertices];
    for (int i = 0; i < graph.numVertices; i++) {
        graph.adjLists[i] = new int[1]; // Assuming only one column (age) is used for the adjacency list
    }

    temp = head;
    int vertexIndex = 0;
    while (temp != NULL) {
        graph.adjLists[vertexIndex][0] = temp->employee.age;
        // Add other employee information to the adjacency list if needed
        temp = temp->next;
        vertexIndex++;
    }

    return graph;
}

// Function to free memory allocated for the graph
void destroyGraph(Graph& graph) {
    for (int i = 0; i < graph.numVertices; i++) {
        delete[] graph.adjLists[i];
    }
    delete[] graph.adjLists;
}


// AVL Tree implementation (insert, search, delete not included)

struct AVLNode {
    Employee* data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(Employee* data)
        : data(data), height(1), left(NULL), right(NULL) {}
};

int getHeight(AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* rotateRight(AVLNode* node) {
    AVLNode* newRoot = node->left;
    AVLNode* subtree = newRoot->right;

    newRoot->right = node;
    node->left = subtree;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* newRoot = node->right;
    AVLNode* subtree = newRoot->left;

    newRoot->left = node;
    node->right = subtree;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

AVLNode* insertAVL(AVLNode* root, Employee* data) {
    if (root == NULL)
        return new AVLNode(data);

    if (data->salary < root->data->salary)
        root->left = insertAVL(root->left, data);
    else if (data->salary > root->data->salary)
        root->right = insertAVL(root->right, data);
    else
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && data->salary < root->left->data->salary)
        return rotateRight(root);

    if (balance < -1 && data->salary > root->right->data->salary)
        return rotateLeft(root);

    if (balance > 1 && data->salary > root->left->data->salary) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && data->salary < root->right->data->salary) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inOrderTraversal(AVLNode* node) {
    if (node == NULL)
        return;

    inOrderTraversal(node->left);
    cout<<endl;
    cout << "Age: " << node->data->age << "/n Gender: " << node->data->gender
         << "/n Education Level: " << node->data->educationLevel
         << "/n Job Title: " << node->data->jobTitle
         << "/n Years of Experience: " << node->data->yearsOfExperience
         << "/n Salary: " << node->data->salary << endl;
    inOrderTraversal(node->right);
    cout << "Age: " << node->data->age << "/n Gender: " << node->data->gender
         << "/n Education Level: " << node->data->educationLevel
         << "/n Job Title: " << node->data->jobTitle
         << "/n Years of Experience: " << node->data->yearsOfExperience
         << "/n Salary: " << node->data->salary << endl;
    
}

int main() {
    // Read data from the Excel file
    ifstream file("employee.csv");
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    // Skip the header row
    getline(file, line);

    // Create a linked list of employees
    Node* head = NULL;
    Node* current = NULL;

    // Read data from the file line by line
    while (getline(file, line)) {
        istringstream iss(line);
        string token;

        // Read each column value directly into the Employee structure
        Employee employee;
        getline(iss, token, ',');
        stringstream(token) >> employee.age;
        getline(iss, employee.gender, ',');
        getline(iss, employee.educationLevel, ',');
        getline(iss, employee.jobTitle, ',');
        getline(iss, token, ',');
        stringstream(token) >> employee.yearsOfExperience;
        getline(iss, token, ',');
        stringstream(token) >> employee.salary;

        // Create a new node for the employee
        Node* newNode = new Node();
        newNode->employee = employee;
        newNode->next = NULL;

        // Add the node to the linked list
        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    // Call the adjacency list function
   Graph graph = convertToGraph(head);
   
    // Perform AVL Tree operations
    AVLNode* root = NULL;

    // Insert employees into AVL Tree
    Node* temp = head;
    while (temp != NULL) {
        root = insertAVL(root, &(temp->employee));
        temp = temp->next;
    }

     cout << "Adjacency List:" << endl;
    createAdjacencyList(head);
    cout << endl;


    // Clean up the linked list memory and graph memory
    temp = head;
    while (temp != NULL) {
        Node* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    

    destroyGraph(graph);

    file.close();
    return 0;
}


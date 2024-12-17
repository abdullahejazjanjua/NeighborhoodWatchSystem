#ifndef GRAPH_H
#define GRAPH_H
#include "Queue.h"
#include <iostream>
#include <cstring>
using namespace std;

struct Node_graph {
    int val;
    Node_graph* next;
    Node_graph(int value) : val(value), next(nullptr) {}
};

class Graph {

public:
    Node_graph** adjacencyList;
    int size;
    Graph(int vertices) {
        size = vertices;
        adjacencyList = new Node_graph*[size];
        for (int i = 0; i < size; ++i) {
            adjacencyList[i] = nullptr;
        }
    }

    void addEdge(int u, int v) {
        Node_graph* newNode = new Node_graph(v);
        newNode->next = adjacencyList[u];
        adjacencyList[u] = newNode;

        newNode = new Node_graph(u);
        newNode->next = adjacencyList[v];
        adjacencyList[v] = newNode;
    }

    void printGraph() const {
        for (int i = 0; i < size; ++i) {
            cout << "Vertex " << i << ": ";
            Node_graph* temp = adjacencyList[i];
            while (temp) {
                cout << temp->val << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    }

    int * BFS(int start) 
    {
        bool* visited = new bool[size]();
        Queue<int> q;
        int *houses = new int[size];

        visited[start] = true;
        q.enqueue(start);

        int i = 0;
        while (!q.isEmpty()) 
        {
            int vertex = q.dequeue();
            houses[i] = vertex;
            

            Node_graph* temp = adjacencyList[vertex];
            while (temp) {
                int adjVertex = temp->val;
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    q.enqueue(adjVertex);
                }
                temp = temp->next;
            }
            i++;
        }
        delete[] visited;
        return houses;
    }

    int* DFS(int start) 
    {
    int* movements = new int[size];  
    memset(movements, -1, sizeof(int) * size); 

    bool* visited = new bool[size]();  
    int i = 0;  
    DFSHelper(start, visited, movements, i); 
    delete[] visited;
    return movements;
}

void DFSHelper(int vertex, bool* visited, int* movements, int& i) 
{
    visited[vertex] = true;
    movements[i++] = vertex;  

    Node_graph* temp = adjacencyList[vertex];
    while (temp) {
        int adjVertex = temp->val;
        if (!visited[adjVertex]) {
            DFSHelper(adjVertex, visited, movements, i);  // Pass i by reference
        }
        temp = temp->next;
    }
}

    ~Graph() {

        for (int i = 0; i < size; ++i) {
            Node_graph* temp = adjacencyList[i];
            while (temp) {
                Node_graph* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] adjacencyList;
    }
};

#endif
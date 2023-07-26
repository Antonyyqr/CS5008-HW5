#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Node** adjList, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = adjList[src];
    adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = adjList[dest];
    adjList[dest] = newNode;
}

void BFS(struct Node** adjList, int numVertices) {
    int* visited = (int*)calloc(numVertices, sizeof(int));
    int* queue = (int*)malloc(numVertices * sizeof(int));
    int front = 0, rear = 0;

    int startVertex = 0;
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct Node* temp = adjList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(queue);
}

int main() {
    int numVertices = 9;
    struct Node** adjList = (struct Node**)malloc(numVertices * sizeof(struct Node*));

    for (int i = 0; i < numVertices; i++) {
        adjList[i] = NULL;
    }

    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 1, 3);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 2, 4);
    addEdge(adjList, 3, 4);
    addEdge(adjList, 3, 5);
    addEdge(adjList, 4, 5);
    addEdge(adjList, 6, 7);
    addEdge(adjList, 7, 8);
    addEdge(adjList, 0, 6);
    addEdge(adjList, 2, 3);
    addEdge(adjList, 4, 6);
    addEdge(adjList, 5, 7);
    addEdge(adjList, 1, 8);

    printf("BFS Traversal: ");
    BFS(adjList, numVertices);

    for (int i = 0; i < numVertices; i++) {
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            struct Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(adjList);

    return 0;
}


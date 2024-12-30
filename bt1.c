#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

typedef struct Queue {
    int items[MAX];
    int front;
    int rear;
} Queue;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    Node* current = graph->adjLists[src];
    if (!current || current->vertex > dest) {
        newNode->next = current;
        graph->adjLists[src] = newNode;
    } else {
        while (current->next && current->next->vertex < dest) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    newNode = createNode(src);
    current = graph->adjLists[dest];
    if (!current || current->vertex > src) {
        newNode->next = current;
        graph->adjLists[dest] = newNode;
    } else {
        while (current->next && current->next->vertex < src) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1)
        return;
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
        return item;
    }
}

void bfs(Graph* graph, int startVertex) {
    Queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices, edges;
    printf("nhap so dinh: ");
    scanf("%d", &vertices);
    printf("nhap so canh: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("nhap danh sach cac canh\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int startVertex;
    printf("nhap dinh bat dau ");
    scanf("%d", &startVertex);

    printf("thu tu duyet  ");
    bfs(graph, startVertex);
}

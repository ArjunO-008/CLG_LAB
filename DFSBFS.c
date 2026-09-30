#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Node for adjacency list
struct Node {
    int vertex;
    struct Node *next;
};

// Add edge to adjacency list
void addEdge(struct Node *adj[], int u, int v) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

// BFS - Non-recursive
int BFS(struct Node *adj[], int n) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front, rear;
    int components = 0;

    printf("\nBFS Traversal: ");

    for (int start = 0; start < n; start++) {

        if (visited[start] == 0) {

            components++;

            front = 0;
            rear = 0;

            queue[rear++] = start;
            visited[start] = 1;

            while (front < rear) {

                int current = queue[front++];

                printf("%d ", current);

                struct Node *temp = adj[current];

                while (temp != NULL) {

                    int nextVertex = temp->vertex;

                    if (visited[nextVertex] == 0) {
                        visited[nextVertex] = 1;
                        queue[rear++] = nextVertex;
                    }

                    temp = temp->next;
                }
            }

            printf("| ");
        }
    }

    printf("\n");

    return components;
}

// DFS - Non-recursive
int DFS(struct Node *adj[], int n) {
    int visited[MAX] = {0};
    int stack[MAX];
    int top;
    int components = 0;

    printf("DFS Traversal: ");

    for (int start = 0; start < n; start++) {

        if (visited[start] == 0) {

            components++;

            top = -1;

            stack[++top] = start;

            while (top != -1) {

                int current = stack[top--];

                if (visited[current] == 1)
                    continue;

                visited[current] = 1;

                printf("%d ", current);

                struct Node *temp = adj[current];

                while (temp != NULL) {

                    int nextVertex = temp->vertex;

                    if (visited[nextVertex] == 0) {
                        stack[++top] = nextVertex;
                    }

                    temp = temp->next;
                }
            }

            printf("| ");
        }
    }

    printf("\n");

    return components;
}

int main() {

    struct Node *adj[MAX] = {NULL};

    int n, edges;
    int u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (u v):\n");

    for (int i = 0; i < edges; i++) {

        scanf("%d %d", &u, &v);

        // Undirected graph
        addEdge(adj, u, v);
        addEdge(adj, v, u);
    }

    int bfsComponents = BFS(adj, n);

    int dfsComponents = DFS(adj, n);

    printf("\nConnected Components using BFS: %d\n",
           bfsComponents);

    printf("Connected Components using DFS: %d\n",
           dfsComponents);

    return 0;
}

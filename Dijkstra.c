#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Structure for an edge
struct Edge
{
    int destination;
    int weight;
    struct Edge *next;
};

// Adjacency list
struct Edge *graph[MAX];

// Add a directed edge
void addEdge(int source, int destination, int weight)
{
    struct Edge *newEdge =
        (struct Edge *)malloc(sizeof(struct Edge));

    newEdge->destination = destination;
    newEdge->weight = weight;
    newEdge->next = graph[source];

    graph[source] = newEdge;
}

// Find vertex with minimum distance
int minDistance(int dist[], int visited[], int n)
{
    int min = INT_MAX;
    int minVertex = -1;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            minVertex = i;
        }
    }

    return minVertex;
}

// Dijkstra's algorithm
void dijkstra(int n, int source)
{
    int dist[MAX];
    int visited[MAX];

    // Initialization
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (int count = 0; count < n; count++)
    {
        int u = minDistance(dist, visited, n);

        if (u == -1)
            break;

        visited[u] = 1;

        // Traverse adjacency list of u
        struct Edge *temp = graph[u];

        while (temp != NULL)
        {
            int v = temp->destination;
            int weight = temp->weight;

            if (!visited[v] &&
                dist[u] != INT_MAX &&
                dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
            }

            temp = temp->next;
        }
    }

    // Print shortest distances
    printf("\nShortest distances from city %d:\n", source);

    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INT_MAX)
            printf("City %d -> Not reachable\n", i);
        else
            printf("City %d -> %d\n", i, dist[i]);
    }
}

int main()
{
    int n, edges;
    int source, destination, weight;

    // Initialize graph
    for (int i = 0; i < MAX; i++)
        graph[i] = NULL;

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter number of routes: ");
    scanf("%d", &edges);

    printf("\nEnter routes as:\n");
    printf("Source Destination Weight\n");

    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d %d",
              &source,
              &destination,
              &weight);

        addEdge(source, destination, weight);
    }

    printf("\nEnter source city: ");
    scanf("%d", &source);

    dijkstra(n, source);

    return 0;
}

Write C like pseudocode

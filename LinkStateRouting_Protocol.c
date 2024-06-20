#include <stdio.h>
#include <stdlib.h>
//#include <limits.h>

#define INF INT_MAX

void dijkstra(int graph[n][n], int n, int source) {
    int distance[n]; 
    int previous[n]; 
    int visited[n];

    for (int i = 0; i < n; i++) {
        distance[i] = INF;
    }

    distance[source] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        int min_distance = INF;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && distance[j] < min_distance) {
                u = j;
                min_distance = distance[j];
            }
        }

        if (u == -1) break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != INF && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                previous[v] = u;
            }
        }
    }

    printf("Final routing table of router %c:\n", 'A' + source);
    printf("Destination\tDistance\tNext_hop\n");
    for (int i = 0; i < n; i++) {
        int next_hop = i;
        while (previous[next_hop] != source && i != source) {
            next_hop = previous[next_hop];
        }
        printf("%c\t\t%d\t\t%c\n", 'A' + i, distance[i], 'A' + next_hop);
    }

}

int main() {
    int n;
    printf("Enter the number of nodes or routers in the network: ");
    scanf("%d", &n);

    int graph[n][n];

    printf("Enter the weight or cost matrix (use -1 for absence of connection):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == -1) {
                graph[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("\n");
        dijkstra(graph[n][n], n, i);
    }

   

    return 0;
}
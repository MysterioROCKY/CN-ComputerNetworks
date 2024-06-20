#include <stdio.h>
#include <limits.h>

#define MAX_NODES 100
#define INF 1000

int main() {
    int n; // Number of nodes
    int cost[MAX_NODES][MAX_NODES]; // Cost matrix

    printf("Enter the number of nodes or routers in the network: ");
    scanf("%d", &n);

    printf("Enter the weight or cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == -1) {
                cost[i][j] = INF;
            }
        }
    }

    int dist[MAX_NODES][MAX_NODES]; // Distance matrix
    int next_hop[MAX_NODES][MAX_NODES]; // Next hop matrix

    // Initialize distance and next hop matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = cost[i][j];
            if (cost[i][j] != INF) {
                next_hop[i][j] = j;
            } else {
                next_hop[i][j] = -1;
            }
        }
    }

    // link state Routing algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next_hop[i][j] = next_hop[i][k];
                }
            }
        }
    }

    // Print the routing tables
    for (int i = 0; i < n; i++) {
        printf("Final routing table of router %c:\n", 'A' + i);
        printf("Destination  Distance  Next_hop\n");
        for (int j = 0; j < n; j++) {
            if (i == j) {
                printf("\t %c \t 0 \t %c\n", 'A' + j, 'A' + j);
            } else if (dist[i][j] != INF) {
                printf("\t %c \t %d \t %c\n", 'A' + j, dist[i][j], 'A' + next_hop[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
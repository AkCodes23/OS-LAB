#include <stdio.h>
#include <stdbool.h>

bool isSafe(int processes, int resources, int need[][resources], int available[resources], int allocation[][resources]) {
    int work[resources];
    bool finish[processes];
    int safeSeq[processes];
    int count = 0;

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < processes; i++) {
        finish[i] = false;
    }

    while (count < processes) {
        bool found = false;
        for (int p = 0; p < processes; p++) {
            if (finish[p] == false) {
                int j;
                for (j = 0; j < resources; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == resources) {
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (found == false) {
            return false;
        }
    }

    printf("Safe Sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return true;
}

bool resourceRequest(int processes, int resources, int need[][resources], int available[resources], int allocation[][resources], int processId, int request[resources]) {
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[processId][i]) {
            printf("Error: Request exceeds need.\n");
            return false;
        }
    }

    for (int i = 0; i < resources; i++) {
        if (request[i] > available[i]) {
            printf("Error: Resources not available.\n");
            return false;
        }
    }

    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[processId][i] += request[i];
        need[processId][i] -= request[i];
    }

    if (isSafe(processes, resources, need, available, allocation)) {
        return true;
    } else {
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[processId][i] -= request[i];
            need[processId][i] += request[i];
        }
        printf("Error: Request leads to an unsafe state.\n");
        return false;
    }
}

int main() {
    int processes, resources;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int max[processes][resources], allocation[processes][resources], available[resources];
    int need[processes][resources];

    printf("Enter the Max matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Available vector:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    if (isSafe(processes, resources, need, available, allocation)) {
        int processId;
        int request[resources];

        printf("Enter the process ID for resource request: ");
        scanf("%d", &processId);

        printf("Enter the resource request vector:\n");
        for (int i = 0; i < resources; i++) {
            scanf("%d", &request[i]);
        }

        resourceRequest(processes, resources, need, available, allocation, processId, request);
    } else {
        printf("System is in an unsafe state.\n");
    }

    return 0;
}

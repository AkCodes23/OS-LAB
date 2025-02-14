#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resources

bool is_safe(int processes[], int avail[], int max[][R], int alloc[][R]) {
    int work[R];
    bool finish[P] = {0};
    int safe_seq[P];
    int count = 0;

    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool can_allocate = true;
                for (int r = 0; r < R; r++) {
                    if (max[p][r] - alloc[p][r] > work[r]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int r = 0; r < R; r++) {
                        work[r] += alloc[p][r];
                    }
                    safe_seq[count++] = processes[p];
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safe_seq[i]);
    }
    printf("\n");

    return true;
}

bool request_resources(int processes[], int avail[], int max[][R], int alloc[][R], int request[], int p) {
    for (int r = 0; r < R; r++) {
        if (request[r] > max[p][r] - alloc[p][r]) {
            return false;
        }
    }

    for (int r = 0; r < R; r++) {
        if (request[r] > avail[r]) {
            return false;
        }
    }

    for (int r = 0; r < R; r++) {
        avail[r] -= request[r];
        alloc[p][r] += request[r];
    }

    if (is_safe(processes, avail, max, alloc)) {
        return true;
    } else {
        for (int r = 0; r < R; r++) {
            avail[r] += request[r];
            alloc[p][r] -= request[r];
        }
        return false;
    }
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};
    int avail[] = {3, 3, 2};
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int request[] = {1, 0, 2};
    int p = 1;

    if (request_resources(processes, avail, max, alloc, request, p)) {
        printf("Request can be granted.\n");
    } else {
        printf("Request cannot be granted. System would be unsafe.\n");
    }

    return 0;
}


//gcc -o Q1 Q1.c
//./Q1

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sstf(int arr[], int head, int n) {
    int seek_count = 0;
    int visited[n], distance, min, index;
    for (int i = 0; i < n; i++) visited[i] = 0;
    printf("SSTF Sequence: ");
    for (int i = 0; i < n; i++) {
        min = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (visited[j] == 0) {
                distance = abs(arr[j] - head);
                if (distance < min) {
                    min = distance;
                    index = j;
                }
            }
        }
        seek_count += min;
        head = arr[index];
        visited[index] = 1;
        printf("%d -> ", head);
    }
    printf("\nTotal seek time = %d\n", seek_count);
}

void scan(int arr[], int head, int n, int direction, int disk_size) {
    int seek_count = 0, i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("SCAN Sequence: ");
    if (direction == 1) { // Right
        int head_index = 0;
        for (i = 0; i < n; i++) {
            if (arr[i] >= head) {
                head_index = i;
                break;
            }
        }
        for (j = head_index; j < n; j++) {
            seek_count += abs(arr[j] - head);
            head = arr[j];
            printf("%d -> ", head);
        }
        seek_count += abs(head - disk_size - 1);
        head = disk_size - 1;
        printf("%d -> ", head);
        for (j = head_index - 1; j >= 0; j--) {
            seek_count += abs(arr[j] - head);
            head = arr[j];
            printf("%d -> ", head);
        }
    } else { // Left
        int head_index = 0;
        for (i = n - 1; i >= 0; i--) {
            if (arr[i] <= head) {
                head_index = i;
                break;
            }
        }
        for (j = head_index; j >= 0; j--) {
            seek_count += abs(arr[j] - head);
            head = arr[j];
            printf("%d -> ", head);
        }
        seek_count += abs(head - 0);
        head = 0;
        printf("%d -> ", head);
        for (j = head_index + 1; j < n; j++) {
            seek_count += abs(arr[j] - head);
            head = arr[j];
            printf("%d -> ", head);
        }
    }
    printf("\nTotal seek time = %d\n", seek_count);
}

void cscan(int arr[], int head, int n, int direction, int disk_size) {
    int seek_count = 0, i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("C-SCAN Sequence: ");
    if (direction == 1) { // Right
        int head_index = 0;
        for (i = 0; i < n; i++) {
            if (arr[i] >= head) {
                head_index = i;
                break;
            }
        }
        for (j = head_index; j < n; j++) {
            seek_count += abs(arr[j] - head);
            head = arr[j];
            printf("%d -> ", head);
        }
        seek_count += abs(head - disk_size - 1);
        head = 0;
        printf("%d -> ", head);
        for (j = 0; j < head_index; j++) {
            seek_count += abs(arr[j] - head);
            head = arr[j];
            printf("%d -> ", head);
        }
    } else { // Left
        int head_index = 0;
        for (i = n - 1; i >= 0; i--) {
            if (arr[i] <= head) {
                head_index = i;
                break;
            }
        }
        for (j = head_index; j >= 0; j--) {
            seek_count += abs(arr[j] - head);
            head = arr[j];
            printf("%d -> ", head);
        }
        seek_count += abs(head - 0);
        head = disk_size - 1;
        printf("%d -> ", head);
        for (j = n - 1; j > head_index; j--) {
            seek_count += abs(arr[j] - head);
            head = arr[j];
            printf("%d -> ", head);
        }
    }
    printf("\nTotal seek time = %d\n", seek_count);
}

void clook(int arr[], int head, int n) {
    int seek_count = 0, i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("C-LOOK Sequence: ");
    int head_index = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] >= head) {
            head_index = i;
            break;
        }
    }
    for (j = head_index; j < n; j++) {
        seek_count += abs(arr[j] - head);
        head = arr[j];
        printf("%d -> ", head);
    }
    if (head_index > 0) {
        seek_count += abs(head - arr[0]);
        head = arr[0];
        printf("%d -> ", head);
        for (j = 0; j < head_index; j++) {
            seek_count += abs(arr[j] - head);
            head = arr[j];
            printf("%d -> ", head);
        }
    }
    printf("\nTotal seek time = %d\n", seek_count);
}

int main() {
    int n, head, disk_size, choice, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    while (1) {
        printf("\nDisk Scheduling Algorithms\n");
        printf("1. SSTF\n2. SCAN\n3. C-SCAN\n4. C-LOOK\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sstf(arr, head, n);
                break;
            case 2:
                printf("Enter direction (1 for right, 0 for left): ");
                scanf("%d", &direction);
                scan(arr, head, n, direction, disk_size);
                break;
            case 3:
                printf("Enter direction (1 for right, 0 for left): ");
                scanf("%d", &direction);
                cscan(arr, head, n, direction, disk_size);
                break;
            case 4:
                clook(arr, head, n);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

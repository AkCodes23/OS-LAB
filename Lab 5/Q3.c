#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(char *arr[], int n) {
    char *temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(char *arr[], int n) {
    int minIdx;
    char *temp;
    for (int i = 0; i < n - 1; i++) {
        minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[minIdx]) < 0) {
                minIdx = j;
            }
        }
        temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int n;
    printf("Enter number of strings: ");
    scanf("%d", &n);

    char *arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = (char *)malloc(100 * sizeof(char));
        printf("Enter string %d: ", i + 1);
        scanf("%s", arr[i]);
    }

    pid_t pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid1 == 0) {
        
        bubbleSort(arr, n);
        printf("Sorted strings by bubble sort:\n");
        for (int i = 0; i < n; i++) {
            printf("%s\n", arr[i]);
        }
        exit(0);
    } else {
        pid_t pid2 = fork();
        if (pid2 < 0) {
            fprintf(stderr, "Fork Failed");
            return 1;
        } else if (pid2 == 0) {
            
            selectionSort(arr, n);
            printf("Sorted strings by selection sort:\n");
            for (int i = 0; i < n; i++) {
                printf("%s\n", arr[i]);
            }
            exit(0);
        } else {
            
            int status1, status2;
            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);
            printf("Parent process waiting for both children to complete.\n");
        }
    }

    
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }

    return 0;
}

// gcc -o Q3 Q3.c
// ./Q3

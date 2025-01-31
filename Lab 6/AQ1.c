#include <stdio.h>

#define MAX 10

struct process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void fcfs(struct process p[], int n);
void display(struct process p[], int n);

int main() {
    int n;
    struct process p[MAX];
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
    }
    
    fcfs(p, n);
    display(p, n);
    
    return 0;
}

void fcfs(struct process p[], int n) {
    p[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
    }
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

void display(struct process p[], int n) {
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }
}

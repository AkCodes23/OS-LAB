#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct process {
    int id;
    int burst_time;
    int arrival_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completed;
};

void preemptive_sjf(struct process p[], int n);
void round_robin(struct process p[], int n, int quantum);
void non_preemptive_priority(struct process p[], int n);
void display(struct process p[], int n);

int main() {
    int choice, n, quantum;
    struct process p[MAX];
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        printf("Process %d\n", i+1);
        p[i].id = i+1;
        printf("Enter burst time: ");
        scanf("%d", &p[i].burst_time);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Enter priority: ");
        scanf("%d", &p[i].priority);
        p[i].remaining_time = p[i].burst_time;
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
        p[i].completed = 0;
    }
    
    while(1) {
        printf("\n--- Menu ---\n");
        printf("1. Preemptive SJF\n");
        printf("2. Round Robin\n");
        printf("3. Non-preemptive Priority\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                preemptive_sjf(p, n);
                break;
            case 2:
                printf("Enter time quantum: ");
                scanf("%d", &quantum);
                round_robin(p, n, quantum);
                break;
            case 3:
                non_preemptive_priority(p, n);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    
    return 0;
}

void preemptive_sjf(struct process p[], int n) {
    int time = 0, completed = 0, min_index;
    while (completed != n) {
        min_index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                if (min_index == -1 || p[i].remaining_time < p[min_index].remaining_time) {
                    min_index = i;
                }
            }
        }

        if (min_index != -1) {
            p[min_index].remaining_time--;
            if (p[min_index].remaining_time == 0) {
                p[min_index].completed = 1;
                completed++;
                p[min_index].turnaround_time = time - p[min_index].arrival_time + 1;
                p[min_index].waiting_time = p[min_index].turnaround_time - p[min_index].burst_time;
            }
            time++;
        } else {
            time++;
        }
    }
    display(p, n);
}

void round_robin(struct process p[], int n, int quantum) {
    int time = 0, completed = 0;
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                if (p[i].remaining_time <= quantum) {
                    time += p[i].remaining_time;
                    p[i].remaining_time = 0;
                    p[i].completed = 1;
                    completed++;
                    p[i].turnaround_time = time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                } else {
                    time += quantum;
                    p[i].remaining_time -= quantum;
                }
            }
        }
    }
    display(p, n);
}

void non_preemptive_priority(struct process p[], int n) {
    int time = 0, completed = 0, max_priority, max_index;
    while (completed != n) {
        max_index = -1;
        max_priority = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                if (p[i].priority > max_priority) {
                    max_priority = p[i].priority;
                    max_index = i;
                }
            }
        }

        if (max_index != -1) {
            time += p[max_index].burst_time;
            p[max_index].completed = 1;
            completed++;
            p[max_index].turnaround_time = time - p[max_index].arrival_time;
            p[max_index].waiting_time = p[max_index].turnaround_time - p[max_index].burst_time;
        } else {
            time++;
        }
    }
    display(p, n);
}

void display(struct process p[], int n) {
    printf("\nProcess ID\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].burst_time, p[i].arrival_time, p[i].priority, p[i].waiting_time, p[i].turnaround_time);
    }
}

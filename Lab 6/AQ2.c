#include <stdio.h>

#define MAX 10

struct process {
    int id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completed;
};

void non_preemptive_sjf(struct process p[], int n);
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
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        p[i].completed = 0;
    }
    
    non_preemptive_sjf(p, n);
    display(p, n);
    
    return 0;
}

void non_preemptive_sjf(struct process p[], int n) {
    int time = 0, completed = 0, min_index;
    
    while (completed != n) {
        min_index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !p[i].completed) {
                if (min_index == -1 || p[i].burst_time < p[min_index].burst_time) {
                    min_index = i;
                }
            }
        }
        
        if (min_index != -1) {
            p[min_index].waiting_time = time - p[min_index].arrival_time;
            time += p[min_index].burst_time;
            p[min_index].turnaround_time = time - p[min_index].arrival_time;
            p[min_index].completed = 1;
            completed++;
        } else {
            time++;
        }
    }
}

void display(struct process p[], int n) {
    printf("\nProcess ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].burst_time, p[i].arrival_time, p[i].waiting_time, p[i].turnaround_time);
    }
}

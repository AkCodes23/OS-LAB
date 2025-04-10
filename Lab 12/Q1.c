#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int execution_time;
    int remaining_time;
    int period;
    int deadline;
    int next_arrival;
    int next_deadline;
} Task;

void sort_by_period(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (tasks[j].period > tasks[j + 1].period) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
}

void sort_by_deadline(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (tasks[j].next_deadline > tasks[j + 1].next_deadline) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
}

void simulate_rms(Task tasks[], int n, int simulation_time) {
    sort_by_period(tasks, n);
    for (int i = 0; i < n; i++) {
        tasks[i].next_arrival = 0;
        tasks[i].remaining_time = 0;
    }

    printf("\n[Rate Monotonic Scheduling Simulation]\n");
    for (int time = 0; time < simulation_time; time++) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_arrival += tasks[i].period;
            }
        }

        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                selected = i;
                break;
            }
        }

        if (selected != -1) {
            printf("Time %2d: Task %d is running\n", time, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("Time %2d: Idle\n", time);
        }
    }
}

void simulate_edf(Task tasks[], int n, int simulation_time) {
    for (int i = 0; i < n; i++) {
        tasks[i].next_arrival = 0;
        tasks[i].next_deadline = tasks[i].deadline;
        tasks[i].remaining_time = 0;
    }

    printf("\n[Earliest Deadline First Scheduling Simulation]\n");
    for (int time = 0; time < simulation_time; time++) {
        for (int i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].execution_time;
                tasks[i].next_arrival += tasks[i].period;
                tasks[i].next_deadline = time + tasks[i].deadline;
            }
        }

        sort_by_deadline(tasks, n);

        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                selected = i;
                break;
            }
        }

        if (selected != -1) {
            printf("Time %2d: Task %d is running\n", time, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("Time %2d: Idle\n", time);
        }
    }
}

int main() {
    int n, simulation_time;
    Task tasks[MAX_TASKS];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask %d:\n", i + 1);
        printf("  Execution Time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("  Period: ");
        scanf("%d", &tasks[i].period);
        printf("  Deadline (for EDF): ");
        scanf("%d", &tasks[i].deadline);
    }

    printf("\nEnter total simulation time: ");
    scanf("%d", &simulation_time);

    simulate_rms(tasks, n, simulation_time);
    simulate_edf(tasks, n, simulation_time);

    return 0;
}

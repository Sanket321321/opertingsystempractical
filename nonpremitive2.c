Write the program to simulate Non-preemptive Priority scheduling. The arrival time and first CPU burst and priority for different n number of processes should be input to the algorithm. Assume the fixed IO waiting time (2 units). The next CPU-burst should be generated randomly. The output should give Gantt chart, turnaround time and waiting time for each process. Also find the average waiting time and turnaround time
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Process {
    int id;
    int arrival_time;
    int first_burst;
    int priority;
    int remaining_burst;
    int turnaround_time;
    int waiting_time;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void sort_by_priority(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

int main() {
    int n, i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter first CPU burst for process P%d: ", i + 1);
        scanf("%d", &processes[i].first_burst);
        processes[i].remaining_burst = processes[i].first_burst;
        printf("Enter priority for process P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Simulate IO waiting time and sort by priority
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        int io_waiting = 2 + (rand() % 5); // Random IO waiting time between 2 to 6 units
        processes[i].arrival_time += io_waiting;
    }

    sort_by_priority(processes, n);

    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("\nGantt Chart:\n");
    printf("0");

    for (i = 0; i < n; i++) {
        int execution_time = processes[i].first_burst;
        processes[i].turnaround_time = execution_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].first_burst;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        
        printf(" -> P%d -> %d", processes[i].id, execution_time);

        // Update waiting times for the next processes
        for (j = i + 1; j < n; j++) {
            if (processes[j].arrival_time <= execution_time) {
                processes[j].waiting_time += execution_time - processes[j].arrival_time;
            }
        }
    }

    printf("\n\nProcess\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].id, processes[i].turnaround_time, processes[i].waiting_time);
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}


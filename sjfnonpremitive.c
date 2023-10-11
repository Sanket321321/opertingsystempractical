Write the simulation program using SJF(non-preemptive). The arrival time and first CPU bursts of different jobs should be input to the system. The Assume the fixed I/O waiting time (2 units). Thenext CPU burst should be generated using random function. The output should give the Gantt chart, Turnaround Time and Waiting time for each process and average times.
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
};

// Function to calculate waiting time and turnaround time for each process
void calculateWaitingTurnaroundTime(struct Process processes[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        // Calculate waiting time
        if (processes[i].arrival_time > currentTime) {
            currentTime = processes[i].arrival_time;
        }
        processes[i].waiting_time = currentTime - processes[i].arrival_time;
        
        // Calculate turnaround time
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        
        currentTime += processes[i].burst_time + 2;  // Add 2 for fixed I/O waiting time
    }
}

// Function to perform SJF scheduling
void sjfScheduling(struct Process processes[], int n) {
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    calculateWaitingTurnaroundTime(processes, n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Perform SJF scheduling
    sjfScheduling(processes, n);

    // Display Gantt chart and results
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", processes[i].id);
    }

    printf("\n\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Calculate and display average waiting time and turnaround time
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}

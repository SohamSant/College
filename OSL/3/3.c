#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
};

// Function to perform Shortest Job First scheduling
void sjf(struct Process processes[], int n) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    char gantt_chart[1000] = "|";

    while (completed < n) {
        int shortest = -1; // Index of the shortest remaining time process

        // Find the process with the shortest remaining time at the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                if (shortest == -1 || processes[i].remaining_time < processes[shortest].remaining_time) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            // No process is ready to execute, move to the next arrival time
            time++;
            gantt_chart[time] = '-';
        } else {
            // Execute the shortest remaining time process
            processes[shortest].remaining_time--;
            time++;
            gantt_chart[time] = processes[shortest].id + '0';

            // If the process is completed
            if (processes[shortest].remaining_time == 0) {
                completed++;
                processes[shortest].turnaround_time = time - processes[shortest].arrival_time;
                processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            }
        }
    }

    // Print Gantt Chart
    printf("Gantt Chart: %s|\n", gantt_chart);

    // Calculate and print average turnaround time and average waiting time
    double avg_turnaround_time = 0.0, avg_waiting_time = 0.0;
    for (int i = 0; i < n; i++) {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;
    printf("Average Turnaround Time: %.2lf\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2lf\n", avg_waiting_time);
}

// Function to perform Round Robin scheduling
void roundRobin(struct Process processes[], int n, int time_quantum) {
    int time = 0; // Current time
    int completed = 0; // Number of completed processes
    char gantt_chart[1000] = "|";

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                int execution_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;
                processes[i].remaining_time -= execution_time;
                time += execution_time;

                for (int j = 0; j < execution_time; j++) {
                    gantt_chart[time - execution_time + j] = processes[i].id + '0';
                }

                // If the process is completed
                if (processes[i].remaining_time == 0) {
                    completed++;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                }
            }
        }
    }

    // Print Gantt Chart
    printf("Gantt Chart: %s|\n", gantt_chart);

    // Calculate and print average turnaround time and average waiting time
    double avg_turnaround_time = 0.0, avg_waiting_time = 0.0;
    for (int i = 0; i < n; i++) {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;
    printf("Average Turnaround Time: %.2lf\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2lf\n", avg_waiting_time);
}

int main() {
    int choice, n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("Choose scheduling algorithm:\n");
    printf("1. Shortest Job First (Preemptive)\n");
    printf("2. Round Robin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sjf(processes, n);
            break;
        case 2:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &time_quantum);
            roundRobin(processes, n, time_quantum);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
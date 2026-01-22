#include <stdio.h>

// Structure to hold process information
struct Process {
    int id;          // Process ID
    int burst_time;  // Burst time (total CPU time needed)
    int remaining_time; // Remaining time to complete
    int arrival_time; // Arrival time
};

int main() {
    int n, quantum;
    
    // Get number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    // Input process details
    for(int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].arrival_time = 0; // All arrive at time 0 for simplicity
    }
    
    // Get time quantum
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
    printf("\n=== Round Robin Scheduling ===\n");
    printf("Time Quantum: %d\n\n", quantum);
    
    int time = 0;
    int completed = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    
    // Store waiting times and turnaround times
    int waiting_times[n];
    int turnaround_times[n];
    
    // Initialize waiting times
    for(int i = 0; i < n; i++) {
        waiting_times[i] = 0;
    }
    
    printf("Gantt Chart:\n");
    printf("Time\tProcess\n");
    printf("----\t-------\n");
    
    // Round Robin Scheduling
    while(completed < n) {
        int all_done = 1;
        
        for(int i = 0; i < n; i++) {
            if(processes[i].remaining_time > 0) {
                all_done = 0;
                
                printf("%d\tP%d starts\n", time, processes[i].id);
                
                if(processes[i].remaining_time <= quantum) {
                    // Process will finish in this quantum
                    time += processes[i].remaining_time;
                    waiting_times[i] = time - processes[i].burst_time - processes[i].arrival_time;
                    turnaround_times[i] = time - processes[i].arrival_time;
                    processes[i].remaining_time = 0;
                    completed++;
                    
                    printf("%d\tP%d finishes\n", time, processes[i].id);
                } else {
                    // Process will not finish, continue with next quantum
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                    
                    printf("%d\tP%d preempted\n", time, processes[i].id);
                }
            }
        }
        
        if(all_done) {
            break;
        }
    }
    
    // Calculate totals
    for(int i = 0; i < n; i++) {
        total_waiting_time += waiting_times[i];
        total_turnaround_time += turnaround_times[i];
    }
    
    // Display results
    printf("\n=== Results ===\n");
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("-------\t----------\t------------\t---------------\n");
    
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", 
               processes[i].id, 
               processes[i].burst_time,
               waiting_times[i],
               turnaround_times[i]);
    }
    
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    
    return 0;
}
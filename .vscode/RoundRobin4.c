#include <stdio.h>

int main() {
    int processes[3] = {5, 3, 4};  // Fixed burst times
    int remaining[3] = {5, 3, 4};
    int quantum = 2;
    int time = 0;
    
    // 2D array: 3 processes x 20 time units
    char gantt[3][20];
    
    // Initialize Gantt chart with spaces
    for(int i = 0; i < 3; i++) {
        for(int t = 0; t < 20; t++) {
            gantt[i][t] = ' ';
        }
    }
    
    // Round Robin logic
    while(1) {
        int done = 1;
        
        for(int i = 0; i < 3; i++) {
            if(remaining[i] > 0) {
                done = 0;
                
                if(remaining[i] >= quantum) {
                    // Mark execution in Gantt chart
                    for(int j = 0; j < quantum; j++) {
                        gantt[i][time + j] = 'X';
                    }
                    remaining[i] -= quantum;
                    time += quantum;
                } else {
                    for(int j = 0; j < remaining[i]; j++) {
                        gantt[i][time + j] = 'X';
                    }
                    time += remaining[i];
                    remaining[i] = 0;
                }
            }
        }
        
        if(done) break;
    }
    
    // Display Gantt chart
    printf("Simple Round Robin Gantt Chart:\n");
    printf("Time: ");
    for(int t = 0; t < time; t++) {
        printf("%d ", t);
    }
    printf("\n");
    
    for(int i = 0; i < 3; i++) {
        printf("P%d:  ", i+1);
        for(int t = 0; t < time; t++) {
            printf("%c ", gantt[i][t]);
        }
        printf("\n");
    }
    
    return 0;
}
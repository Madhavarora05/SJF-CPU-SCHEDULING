#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};
// Function to sort processes by burst time
void sort_processes_by_burst_time(struct Process processes[], int num_processes) {
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
// Function to generate random processes
void generate_processes(struct Process processes[], int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        processes[i].id = i + 1;
        processes[i].arrival_time = rand() % 10; // Random arrival time
        processes[i].burst_time = 1 + rand() % 10; // Random burst time
    }
}

void sjf_scheduling(struct Process processes[], int num_processes) {
    int current_time = 0;
    for (int k = 0; k < num_processes - 1; k++) {
        for (int j = 0; j < num_processes - k - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time ||
                (processes[j].arrival_time == processes[j + 1].arrival_time &&
                 processes[j].burst_time > processes[j + 1].burst_time)) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    int a;
    for (int i = 0; i < num_processes; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].completion_time = current_time + processes[i].burst_time;
        a = processes[i].completion_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        if (processes[i].id == processes[0].id) {
            processes[i].waiting_time = processes[i].arrival_time;
        } else if (processes[i].arrival_time > processes[i - 1].completion_time) {
            processes[i].waiting_time = processes[i].arrival_time - processes[i - 1].completion_time;
        } else {
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        }
        current_time = processes[i].completion_time;
        
        int max = 0;
        for(int x = i + 1; x < num_processes ; x++){
            if(processes[x].arrival_time <= processes[i].completion_time){
                max = x;
            }
        }
        //Sorting that processes whose arrival time is less than the previous completion_time on basis of burst time
        if (max > i + 2) {
            sort_processes_by_burst_time(&processes[1], max);
        }
    }
}

// Function to calculate and print performance metrics
void calculate_and_print_metrics(struct Process processes[], int num_processes) {
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].completion_time);

        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time / num_processes);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time / num_processes);
}

int main() {
    srand(time(NULL)); // Initialize the random number generator with the current time

    int num_processes = 5; // Number of processes

    struct Process processes[num_processes]; // Create an array of processes

    generate_processes(processes, num_processes); // Generate random processes

    sjf_scheduling(processes, num_processes); // Run SJF scheduling

    calculate_and_print_metrics(processes, num_processes); // Calculate and print performance metrics

    return 0;
}

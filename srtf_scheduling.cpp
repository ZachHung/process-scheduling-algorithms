#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct process {
	int pid;
	int arrival_time;
	int burst_time;
	int start_time;
	int completion_time;
	int turnaround_time;
	int waiting_time;
	int response_time;
};
bool compareProc(process p, process n) {
	return p.start_time < n.start_time;
}

int main() {

	int n;
	struct process p[100];
	float avg_turnaround_time;
	float avg_waiting_time;
	int total_turnaround_time = 0;
	int total_waiting_time = 0;

	int current_time = 0;
	int completed = 0;
	int is_completed[100] = { 0 };
    int burst_remaining[100];

	cout << setprecision(2) << fixed;

	cout << "Enter the number of processes: ";
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << "Enter process name, arrival time and burst time: ";
		cin >> p[i].pid >> p[i].arrival_time >> p[i].burst_time;
        burst_remaining[i] = p[i].burst_time;
	}

    while(completed != n) {
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(burst_remaining[i] < mn) {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if(burst_remaining[i] == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if(idx != -1) {
            if(burst_remaining[idx] == p[idx].burst_time)
                p[idx].start_time = current_time;
            burst_remaining[idx] -= 1;
            current_time++;
            if(burst_remaining[idx] == 0) {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else {
        current_time++;
        }  
    }
sort(p, p + n, compareProc);
	cout << "\n\nName\t" << "Arrive\t" << "Burst\t" << "Start\t" << "Complete " << "  TurnAround\t" << "Wait\t"<<"Response\n";
	for (int i = 0; i < n; i++) {
		total_turnaround_time += p[i].turnaround_time;
		total_waiting_time += p[i].waiting_time;
		cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << endl;
	}
	avg_turnaround_time = (float)total_turnaround_time / n;
	avg_waiting_time = (float)total_waiting_time / n;
	cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
	cout << "Average Waiting Time = " << avg_waiting_time << endl;
	return 0;
}
#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <queue> 
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

bool compare1(process p1, process p2) 
{ 
    return p1.arrival_time < p2.arrival_time;
}

bool compare2(process p1, process p2) 
{  
    return p1.pid < p2.pid;
}

int main() {
    int n;
    int qt;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int burst_remaining[100];
    int idx;

    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"Enter quantum time: ";
    cin>>qt;

    for (int i = 0; i < n; i++) {
		cout << "Enter process name, arrival time and burst time: ";
		cin >> p[i].pid >> p[i].arrival_time >> p[i].burst_time;
        burst_remaining[i] = p[i].burst_time;
	}

    sort(p,p+n,compare1);

    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int mark[100]={0};
    mark[0] = 1;
    cout<<"\n-------GANTT CHART--------\n";
    while(completed != n) {
        idx = q.front();
        cout<<'['<<current_time<<']'<<"__"<<p[idx].pid<<"__";
        q.pop();
        if(burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = max(current_time,p[idx].arrival_time);
            current_time = p[idx].start_time;
        }
        if(burst_remaining[idx]-qt > 0) {
            burst_remaining[idx] -= qt;
            current_time += qt;
        }
        else {
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++;

            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

        }

        for(int i = 1; i < n; i++) {
            if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }
        if(burst_remaining[idx] > 0) {  
            q.push(idx);
        }

        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }
    cout<<'['<<current_time<<']';
    sort(p, p + n, compare2);
	cout << "\n\nName\t" << "Arrive\t" << "Burst\t" << "Start\t" << "Complete " << "  TurnAround\t" << "Wait\t"<<"Reponse\n";

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
#include <bits/stdc++.h>
using namespace std;

struct process {
    int pid; // process id
    int at; // arrival time
    int bt; // burst time
    int ct, wt, tat, rt, start_time; // completion time, wait time, turn around time, response time
}ps[100]; // array of struct process for 'n' processes

int main()
{
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    bool is_completed[100], first_process = true;
    int curr_time = 0, completed = 0;
    float bt_remaining[100]; // this will contain the values when the process will preempt
    
    int sum_tat=0, sum_wt=0, sum_rt=0, idle_time=0, prev=0, cycle_length;
    float cpu_utilization;
    
    cout<<fixed<<setprecision(2);
    
    // Taking the arrival time input
    for(int i=0;i<n;i++) {
        cout<<"Enter process "<<i<<" arrival time: ";
        cin>>ps[i].at;
        ps[i].pid = i;
    }
    
    // Taking the burst time input
    for(int i=0;i<n;i++) {
        cout<<"Enter process "<<i<<" burst time: ";
        cin>>ps[i].bt;
        bt_remaining[i] = ps[i].bt;
    }
    
    while(completed < n) {
        //find the process with min. burst time in ready queue at current time (at <= curr_time)
        int min_ind = -1;
        int mini = INT_MAX;
        
        for(int i=0;i<n;i++) {
            if(ps[i].at <= curr_time && !is_completed[i]) {
                if(bt_remaining[i] < mini) {
                    mini = bt_remaining[i];
                    min_ind = i;
                }
                if(bt_remaining[i] == mini) {
                    if(ps[i].at < ps[min_ind].at) {
                        mini = bt_remaining[i];
                        min_ind = i;
                    }
                }
            }
        }
        
        if(min_ind == -1) curr_time++;
        else {
            if(bt_remaining[min_ind] == ps[min_ind].bt) {
                ps[min_ind].start_time = curr_time;
                if(!first_process) {
                    idle_time += ps[min_ind].start_time - prev;
                }
                first_process = false;
            }
            
            bt_remaining[min_ind] -= 1; // as we are checking every one second, we will perform this operation
            // by 1 second and then again go into the while loop and check for the min burst time 
            curr_time++;
            prev = curr_time;
            
            if(bt_remaining[min_ind] == 0) {
                ps[min_ind].ct = curr_time;
                ps[min_ind].tat = ps[min_ind].ct - ps[min_ind].at;
                ps[min_ind].wt= ps[min_ind].tat - ps[min_ind].bt;
                ps[min_ind].rt = ps[min_ind].start_time - ps[min_ind].at;
            
            
                sum_tat += ps[min_ind].tat;
                sum_wt += ps[min_ind].wt;
                sum_rt += ps[min_ind].rt;
                completed++;
                is_completed[min_ind] = true;
            }
        }
    }
    
    int max_completion_time = INT_MIN;
    int min_arrival_time = INT_MAX;
    for(int i=0;i<n;i++) {
        max_completion_time = max(max_completion_time, ps[i].ct); // when last process ended
        min_arrival_time = min(min_arrival_time, ps[i].at); // when first process started
    }
    cycle_length = max_completion_time - min_arrival_time;
    
    cout<<endl;
    cout<<"Process No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT"<<endl;
    for(int i=0;i<n;i++) {
     cout<<i<<"\t\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<endl;
     cout<<endl;  
    }
    
    cpu_utilization = (float)(cycle_length - idle_time)/cycle_length;

    cout<<"Average Turn Around time= "<< (float)sum_tat/n<<endl;
    cout<<"Average Waiting Time= "<<(float)sum_wt/n<<endl;
    cout<<"Average Response Time= "<<(float)sum_rt/n<<endl;    
    cout<<"Throughput= "<<n/(float)cycle_length<<endl;
    cout<<"CPU Utilization(Percentage)= "<<cpu_utilization*100;

    return 0;
}
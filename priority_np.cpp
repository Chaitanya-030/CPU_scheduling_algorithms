#include <bits/stdc++.h>
using namespace std;

struct process {
    int pid; // process id
    int at; // arrival time
    int bt; // burst time
    int priority; // priority
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
    }
    
    // Taking the priority input
    for(int i=0;i<n;i++) {
        cout<<"Enter process "<<i<<" priority: ";
        cin>>ps[i].priority;
    }
    
    while(completed < n) {
        //find the process with max. priority in ready queue at current time (at <= curr_time)
        int max_ind = -1;
        int maxi = INT_MIN;
        
        for(int i=0;i<n;i++) {
            if(ps[i].at <= curr_time && !is_completed[i]) {
                if(ps[i].priority > maxi) {
                    maxi = ps[i].priority;
                    max_ind = i;
                }
                if(ps[i].priority == maxi) {
                    if(ps[i].at < ps[max_ind].at) {
                        maxi = ps[i].priority;
                        max_ind = i;
                    }
                }
            }
        }
        
        if(max_ind == -1) curr_time++;
        else {
            ps[max_ind].start_time = curr_time;
            ps[max_ind].ct = ps[max_ind].start_time + ps[max_ind].bt;
            ps[max_ind].tat = ps[max_ind].ct - ps[max_ind].at;
            ps[max_ind].wt= ps[max_ind].tat - ps[max_ind].bt;
            ps[max_ind].rt = ps[max_ind].start_time - ps[max_ind].at;
            idle_time += (first_process == true) ? 0 : (ps[max_ind].start_time - prev);
         
            sum_tat += ps[max_ind].tat;
            sum_wt += ps[max_ind].wt;
            sum_rt += ps[max_ind].rt;
            completed++;
            is_completed[max_ind] = true;
            curr_time = ps[max_ind].ct;
            prev = curr_time;
            first_process = false; 
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
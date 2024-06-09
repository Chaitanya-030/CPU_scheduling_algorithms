#include <bits/stdc++.h>
using namespace std;

struct process {
    int pid; // process id
    int at; // arrival time
    int bt; // burst time
    int ct, wt, tat, rt, start_time; // completion time, wait time, turn around time, response time
}ps[100]; // array of struct process for 'n' processes

bool cmp_at(struct process a, struct process b) {
    int x = a.at;
    int y = b.at;
    return x < y;
}

bool cmp_pid(struct process a, struct process b) {
    int x = a.pid;
    int y = b.pid;
    return x < y;
}

int main()
{
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    float sum_tat, sum_wt, sum_rt;
    int cycle_length, idle_time = 0;
    float cpu_utilization;
    
    cout<<fixed<<setprecision(2);
    
    // Taking the input of arrival time
    for(int i=0;i<n;i++) {
        cout<<"Enter process "<<i<<" arrival time: ";
        cin>>ps[i].at;
        ps[i].pid = i;
    }
    
    // Taking the input of burst time
    for(int i=0;i<n;i++) {
        cout<<"Enter process "<<i<<" burst time: ";
        cin>>ps[i].bt;
    }
    
    // Sort on arrival time (FCFS)
    sort(ps, ps+n, cmp_at);
    
    for(int i=0;i<n;i++) {
        if(i == 0) {
            ps[i].start_time = ps[i].at;
        }
        else {
            ps[i].start_time = max(ps[i].at, ps[i-1].ct);
        }
        
        ps[i].ct = ps[i].start_time + ps[i].bt;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;
        ps[i].rt = ps[i].wt;
        
        sum_tat += ps[i].tat;
        sum_wt += ps[i].wt;
        sum_rt += ps[i].rt;
        
        if(i != 0) {
            idle_time += (ps[i].start_time -ps[i-1].ct);
        }
    }
    
    cycle_length = ps[n-1].ct - ps[0].start_time; // total time
    
    sort(ps, ps+n, cmp_pid); // just for the display
    
    cout<<endl;
    cout<<"Process No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT"<<endl;
    
    for(int i=0;i<n;i++) {
     cout<<i<<"\t\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<endl;
     cout<<endl;
    }
    
    cpu_utilization = (float)(cycle_length - idle_time)/ cycle_length;
    
    cout<<"Average Turn Around time= "<<sum_tat/n<<endl;
    cout<<"Average Waiting Time= "<<sum_wt/n<<endl;
    cout<<"Average Response Time= "<<sum_rt/n<<endl;    
    cout<<"Throughput= "<<n/(float)cycle_length<<endl;
    cout<<"CPU Utilization(Percentage)= " << cpu_utilization*100;
    

    return 0;
}
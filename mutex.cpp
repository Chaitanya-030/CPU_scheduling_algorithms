#include <bits/stdc++.h>
#include<thread>
#include <mutex>
using namespace std;

int cnt = 0;
mutex mtx; 

void task() {
    mtx.lock(); // we are locking this process hence no other process will execute (mutual exclusion)
    for(int i=0;i<100000;i++) {
        cnt++;
    }
    mtx.unlock();
}

int main()
{
    // P --> t1 and t2
    thread t1(task);
    thread t2(task);
    
    t1.join(); // this prevents from termaination of the parent process P
    t2.join();
    
    cout<<cnt<<endl;

    return 0;
}
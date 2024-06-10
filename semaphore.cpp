#include <bits/stdc++.h>
#include<thread>
#include <mutex>
#include <semaphore>
using namespace std;

counting_semaphore<10> sem(3); 
// by using semaphore we can provide resourses to multiple threads (upto the limit of number of resources)
// and hence can run multiple threads instead of one (as in locks)

void task() {
    sem.acquire(); 
    for(int i=0;i<5;i++) {
        cout<<"Hello"<<endl;
        sleep(1);
    }
    sem.release();
}

int main()
{
    // P --> t1, t2, t3, t4, t5
    thread t1(task);
    thread t2(task);
    thread t3(task);
    thread t4(task);
    thread t5(task);
    
    // this prevents from termination of the parent process P
    t1.join(); 
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
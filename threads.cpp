#include <bits/stdc++.h>
#include<thread>
using namespace std;

void taskA() {
    for(int i=0;i<10;i++) {
        sleep(1);
        cout<<"TaskA "<<i<<endl;
        fflush(stdout);
    }
}

void taskB() {
    for(int i=0;i<10;i++) {
        sleep(1);
        cout<<"TaskB "<<i<<endl;
        fflush(stdout);
    }
}


int main()
{
    // P --> t1 and t2
    thread t1(taskA);
    thread t2(taskB);
    
    t1.join(); // this prevents from termaination of the parent process P
    t2.join();

    return 0;
}
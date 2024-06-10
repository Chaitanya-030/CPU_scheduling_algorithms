#include <thread>
#include <bits/stdc++.h>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable cond;
queue<int> q;
int maxSize = 50;

void producer(int val) {
    while(val) {
        unique_lock<mutex> lock(mtx);
        while(q.size() > 50) {
            cond.wait(lock);
        }
        q.push(val);
        cout<<"Produced: "<<val<<endl;
        val--;
        lock.unlock();
        cond.notify_all();
    }
}

void consumer() {
    while(1) {
        unique_lock<mutex> lock(mtx);
        while(q.size() == 0) {
            cond.wait(lock);
        }
        int val = q.front();
        q.pop();
        cout<<"Consumed: "<<val<<endl;
        lock.unlock();
        cond.notify_all();
    }
}

int main()
{
    thread t1(producer, 100);
    thread t2(consumer);
    
    t1.join();
    t2.join();

    return 0;
}
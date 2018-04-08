#include <mutex> 
#include <deque>
#include <thread>
#include <iostream>


using namespace std;

std::mutex mu;
std::deque<int> q;
std::condition_variable cond;

void f1() {
    int cnt = 10;
    while (cnt > 0) {
        std::unique_lock<mutex> locker(mu);
        q.push_front(cnt--);
        locker.unlock();
        cond.notify_one();
        //cond.notify_all();
        std::this_thread::sleep_for(chrono::seconds(1));
    }
}

void f2() {
    int data = 0;
    while (data != 1) {
        std::unique_lock<mutex> locker(mu);
        //if (!q.empty()) {
        //cond.wait(locker});  // will unlock mu
        cond.wait(locker, [](){ return !q.empty();});  // suprious wake
            data = q.back();
            q.pop_back();
            locker.unlock();
            cout << "t2 got a value from t1: " << data << endl;
        //} else {
            //locker.unlock();
            //std::this_thread::sleep_for(chrono::milliseconds(10));  // inefficient
        //}

    }
}

int main() {
    std::thread t1(f1);
    std::thread t2(f2);
    while (1) {;}
}   

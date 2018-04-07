#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

class LogFile {
    std::mutex _mu;
    std::mutex _mu2;
    //ofstream _f;
public:
    LogFile() {
        //_f.open("log.txt");
    }  // Need destructor to close file
    
    void shared_print(string id, int value) {
        std::lock(_mu, _mu2);
        std::lock_guard<std::mutex> locker(_mu, std::adopt_lock);
        std::lock_guard<std::mutex> locker2(_mu2, std::adopt_lock);
        //_f << "From " << id << ": " << value << endl;
        cout << "From " << id << ": " << value << endl;
    }   
    void shared_print2(string id, int value) {
        //std::lock_guard<std::mutex> locker2(_mu2);  // deadlock
        std::lock(_mu, _mu2);
        std::lock_guard<std::mutex> locker2(_mu2, std::adopt_lock);
        std::lock_guard<std::mutex> locker(_mu, std::adopt_lock);
        //_f << "From " << id << ": " << value << endl;
        cout << "From " << id << ": " << value << endl;
    }   
};

/* Avoid deadlock
  1. Prefer locking single mutex
  2. Avoid locking a mutex and then calling a user provided function
  3. Use std::lock() and adopt_lock to lock more than one mutex 
  4. Lock the mutex in same order
*/

void f1(LogFile& log) {
    for (int i=0;i>-100;--i) {
        log.shared_print("t1", i);
    }
}

int main() {
    LogFile log;
    std::thread t1(f1, std::ref(log));

    for (int i=0;i<100;++i)
        log.shared_print2(string("main: "), i);
    t1.join();
}

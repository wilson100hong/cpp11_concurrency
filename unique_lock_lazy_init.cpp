#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

class LogFile {
    std::mutex _mu;
    std::mutex _mu_open;
    std::once_flag _flag;
    ofstream _f;
public:
    LogFile() {
        //_f.open("log.txt");
    }  // Need destructor to close file
    
    void shared_print(string id, int value) {
        //{
            //std::unique_lock<mutex> locker2(_mu_open);
            //if (!_f.is_open()) {
                //_f.open("log.txt");
            //}
        //}
        
        std::call_once(_flag, [&](){ _f.open("log.txt"); })

        std::unique_lock<std::mutex> locker(_mu, std::defer_lock);
        //std::unique_lock<std::mutex> locker2 = std::move(locker);
        
        //locker.lock();
        cout << "From " << id << ": " << value << endl;
        //locker.unlock();
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
        log.shared_print(string("main: "), i);
    t1.join();
}

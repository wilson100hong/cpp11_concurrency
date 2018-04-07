#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

class LogFile {
    std::mutex mu;
    ofstream f;
public:
    LogFile() {
        f.open("log.txt");
    }  // Need destructor to close file
    
    void shared_print(string id, int value) {
        std::lock_guard<std::mutex> guard(mu);  // RAII
        //mu.lock();
        f << "From " << id << ": " << value << endl;
        //mu.unlock();
    }   

    // Never return f to the outside world
    //ofstream& getStream() {return f;}

    // Never pass f as an argument to user provided function
    //void processf(void fun(ofstream&)) {
        //fun(f);
    //}
};


void f1() {
    for (int i=0;i<100;++i) {
        shared_print(string("From t1: "), i);
    }
}

int main() {
    std::thread t1(f1);

    for (int i=0;i<100;++i) {
        shared_print(string("From main: "), i);
    }

    t1.join();

}

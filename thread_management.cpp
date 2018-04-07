#include <iostream>
#include <thread>

using namespace std;

void f1() {
    std::cout << "f1" << std::endl;
}

//class Fctor {
//public:
    //void operator()() {
        //for (int i=0; i>-100; --i) {
            //cout << "from t1: " << i << endl;
        //}
    //}
//};

//class Fctor {
//public:
    //void operator()(string msg) {
        //cout << "t1 says: " << msg << endl;
    //}
//};

class Fctor {
public:
    void operator()(string& msg) {
        cout << "t1 says: " << msg << endl;
        msg = "maga!";
    }
};

int main() {
    // 1. construct thread with function 
    //std::thread t1(f1);  // t1 starts running   
   
    // 2. construct thread with functor
    //Fctor fctor;
    //std::thread t1(fctor);
    
    //std::thread t1((Fctor()));
    
    string s = "in god we trust";
    cout << std::this_thread::get_id() << endl;
    cout << std::thread::hardware_concurrency() << endl;

    std::thread t1((Fctor()), std::ref(s));  // t1 starts running
    
    t1.join();

    cout << "from main: " << s << endl;

    // mimic RAII
    // wrapper w(t1)
    //
    //try {
        //cout << "from main: " << s << endl;
    //} catch (...) {
        //t1.join();
        //throw;
    //}

    //t1.join();
    return 0;
}

#include <iostream>
#include <thread>
using namespace std;

void function_1() {
    cout << "function1" << endl;
}   

int main() {
    std::thread t1(function_1); 
    //t1.join();  // main thread wait t1 to finsih  
    t1.detach();  // t1 becomes a daemon


    if (t1.joinable()) {
        t1.join();
    }
    //t1.join();  // will crash
    return 0;
}

#include <iostream>
#include <thread>


int factorial(int n) {
    int res = 1;
    for (int i=n; i>1;i--) {
        res *= i;
    }
    cout << "result is: " << res << endl;
    return res;
}

int main() {
    /* thread */
    std::thread t1(factorial); 
    std::this_thread::sleep_for(chron::milliseconds(3));
    chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::microseconds(4);
    std::this_thread::sleep_until(tp);

    /* Mutex */
    std::mutex mu;
    std::lock_guard<mutex> locker(mu);
    std::unique_lock<mutex> ulocker(mu);
    ulocker.try_lock();
    ulocker.try_lock_for(chrono::nanoseconds(500));
    ulocker.try_lock_until(fp);

    /* condition varialbe */
    std::condition_variable cond;
    cond.wait_for(ulocker, chrono::microseconds(2));
    cond.wait_until(ulocker, tp);


    /* Future and promise */
    std::promise<int> p;
    std::future<int> f = p.get_future();
    f.get();
    f.wait();
    f.wait_for(chrono::milliseconds(2));
    f.wait_until(tp);

    /* async() */
    std::future<int> fu = std::async(factorial, 6);

    /* Packaged Task */
    std::packaged_task<int(int)> t(factorial);
    std::future<int> fu2 = t.get_future();
    t(6);

    
}


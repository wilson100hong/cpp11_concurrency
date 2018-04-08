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

std::deque<std::packaged_task<int()> > task_q;
std::mutex mu;
std::conditional_variable cond;

void thread1() {
    std::packaged_task<int()> t;
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){return !task_q.empty();});

        t = std::move(task_q.front());
        task_q.pop_front();
    }
    t();
}



int main() {
    std::thread t1(factorial, 6);
    std::packaged_task<int(int)> t(std::bind(factorial, 6));
    std::future<int> fu = t.get_future();
    {
        std::lock_guard<std::mutex> locker(mu);
        task_q.push_back(std::move(t));
    }
    cond.notify_one();
    cout << fu.get() << endl;

    t1.join();

    //t(6);
    //int x = t.get_future().get();

    return 0;
}

/*
 * Summary
 * 3 ways to get a future
 * - promise: get_future()
 * - packaged_task::get_future()
 * - async() returns a future
 *
 */

#include <future>
#include <iostream>
using namespace std;

//int factorial(int n) {
    //int res = 1;
    //for (int i=n;i>1;--i)
        //res *= i;

    //cout << "Result is: " << res << endl;
    //return res;
//}

int factorial(std::shared_future<int> f) {
    int res = 1;
    int n = f.get();
    for (int i=n;i>1;--i)
        res *= i;

    cout << "Result is: " << res << endl;
    return res;
}

int main() {
    int x;

    //std::future<int> fu = std::async(factorial, 4);
    //std::future<int> fu = std::async(std::launch::async, factorial, 4);
    //std::future<int> fu = std::async(std::launch::async | std::launch::defered, factorial, 4);
    
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::shared_future<int> sf = f.share();


    std::future<int> fu = std::async(std::launch::async, factorial, sf);
    std::future<int> fu2 = std::async(std::launch::async, factorial, sf);
    std::future<int> fu3 = std::async(std::launch::async, factorial, sf);

    std::this_thread::sleep_for(chrono::milliseconds(20));
    p.set_value(4);
    //p.set_exception(std::make_exception_ptr(std::runtime_error("human error")));

    x = fu.get();
    cout << "Get from child: " << x << endl;
}

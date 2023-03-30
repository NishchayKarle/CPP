#include <iostream>
#include <thread>
#include <future>

using namespace std;

int func1(int a, int b, int c)
{
    return a + b + c;
}

int func2(int a, int b)
{
    return a + b;
}

template <typename Func, typename... Args>
auto my_async(Func &f, Args... args)
{
    packaged_task<Func> pt{f};
    future<decltype(f(args...))> fi = pt.get_future();
    jthread t(move(pt), args...);
    t.detach();

    return fi;
}

int main()
{
    future<int> fi = my_async(func1, 1, 2, 3);
    future<int> fi2 = my_async(func2, 1, 2);
    cout << fi.get() << endl;
    cout << fi2.get() << endl;
}

// We don't join the thread coz we want the main thread to continue its own execution and not wait
// for the other thread to complete its execution.
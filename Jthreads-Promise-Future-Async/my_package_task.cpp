#include <iostream>
#include <future>

using namespace std;

int func1(int a, int b, int c)
{
    return a + b + c;
}

template <typename T>
struct my_package_task;

template <typename _Ret, typename... _Args>
struct my_package_task<_Ret(_Args...)>
{

    function<_Ret(_Args...)> func;
    promise<_Ret> p;

    my_package_task(function<_Ret(_Args...)> func) : func(func){};

    void operator()(_Args... args)
    {
        try
        {
            _Ret val = func(args...);
            p.set_value(val);
        }

        catch (...)
        {
            p.set_exception(current_exception());
        }
    }

    future<_Ret> get_future()
    {
        return p.get_future();
    }
};

int main()
{
    my_package_task<int(int, int, int)> pt(func1);
    pt(1, 2, 3);
    future<int> fi = pt.get_future();
    cout << fi.get() << endl;
}
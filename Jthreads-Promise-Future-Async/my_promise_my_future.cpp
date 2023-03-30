#include <iostream>
#include <thread>
#include <mutex>
#include <memory>

using namespace std;

mutex mtx;
condition_variable cv;

int func1(int a, int b, int c)
{
    return a + b + c;
}

template <typename _Ret>
struct _State
{
    _State() : done(false), exp(nullptr){};

    bool done;
    _Ret val;
    exception_ptr exp;
};

template <typename _Ret>
class my_promise;

template <typename _Ret>
class my_future
{
private:
    friend class my_promise<_Ret>;

    _State<_Ret> *val = new _State<_Ret>();

public:
    _Ret get()
    {
        if (val->exp)
        {
            rethrow_exception(val->exp);
        }

        else
        {
            std::unique_lock<mutex> l(mtx);
            cv.wait(l, [this]()
                    { return val->done == true; });
            l.unlock();
            return val->val;
        }
    }

    my_future() = default;
    my_future(const my_future &) = delete;
    my_future &operator=(const my_future &) = delete;
    my_future(my_future &&) = default;
};

template <typename _Ret>
class my_promise
{
private:
    unique_ptr<my_future<_Ret>> fi = make_unique<my_future<_Ret>>();

public:
    my_promise() = default;
    my_promise(const my_promise &) = delete;
    my_promise &operator=(const my_promise &) = delete;
    my_promise(my_promise &&) = default;

    void set_value(_Ret new_val)
    {
        try
        {
            std::unique_lock<mutex> l(mtx);
            cv.wait(l, [this]()
                    { return fi->val->done == false; });

            fi->val->done = true;
            fi->val->val = new_val;

            l.unlock();
            cv.notify_one();
        }
        catch (...)
        {
            set_exception(current_exception());
        }
    }

    void set_exception(exception_ptr ex)
    {
        fi->val->exp = ex;
    }

    auto get_future()
    {
        return move(*fi);
    }
};

void task(my_promise<int> &&buffPromise)
{
    buffPromise.set_value(123709);
}

int main()
{
    my_promise<int> p;
    my_future<int> fi = p.get_future();
    std::jthread tp(task, move(p));
    cout << fi.get() << endl;
}
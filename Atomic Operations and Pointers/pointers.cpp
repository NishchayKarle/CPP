#include <iostream>

using namespace std;

struct A
{
    int x;
    float y;
    double z;

    A()
    {
        x = 10;
        y = 2.0;
        z = 3.0;
    }

    int func3(int *a)
    {
        cout << "value: " << (*a) + 1 << endl;
        return (*a)++;
    }

    int func4(double (*a)(float &))
    {
        cout << "BEFORE: y: " << y << ", z: " << z << endl;
        z = a(y);
        cout << " AFTER: y: " << y << ", z: " << z << endl;
        return 0;
    }
};

int func1()
{
    return 12;
}

char *func2(char *a, char *b)
{
    return a;
}

void func5(void (*a)())
{
    cout << "what up ";
    a();
}

void func6()
{
    cout << "Prashant?" << endl;
}

double func7(float &y)
{
    y /= 2;
    return 2.0 * y;
}

int main()
{
    int exp1 = 1;
    char const exp2 = 'a';
    float exp3 = 1.2;

    int *p1 = &exp1;

    int &p2 = exp1;

    double p3 = 2.0 / exp1;

    A *p4 = new A();

    char const *p5 = &exp2;

    char const &p6 = exp2;

    long p7[7] = {8647627343L, 8647627343L, 8647627343L, 8647627343L, 8647627343L, 8647627343L, 8647627343L};

    int **p8 = &p1;

    int *&p9 = p1;

    float &p10 = exp3;

    int (*p11)() = &func1;

    int (*&p12)() = p11;

    char *(*p13)(char *, char *) = &func2;

    int A::*p14 = &A::x;

    int (A::*p15)(int *) = &A::func3;

    int (A::* * p16)(int *) = &p15;

    int (A::* & p17)(int *) = p15;

    int (A::*p18)(double (*)(float &)) = &A::func4;

    void (*p19[10])(void (*)()) = {func5, func5, func5, func5, func5, func5, func5, func5, func5, func5};

    for (int i = 0; i < 10; i++)
        p19[i](&func6);

    cout << endl;

    A a;
    (a.*p18)(func7);

    cout << endl;

    (a.*p17)(p1);

    cout << endl;

    (a.**p16)(p1);

    cout << endl;

    (a.*p15)(p1);

    cout << endl;

    cout << "BEFORE: a.x: " << a.x << endl;
    (a.*p14)++;
    cout << " AFTER: a.x: " << a.x << endl;

    cout << endl;

    return 0;
}
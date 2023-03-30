#include <iostream>
#include "LockFreeStack.h"

using namespace std;
using namespace mpcs51044;

int main()
{
    Stack *s = new Stack();
    s->push(1);
    s->push(2);
    s->push(3);
    cout << s->pop() << endl;
    cout << s->pop() << endl;
    cout << s->pop() << endl;
}
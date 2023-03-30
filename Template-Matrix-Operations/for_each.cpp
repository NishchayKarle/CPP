#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct maxlenftn
{
    maxlenftn() { maxlen = 0; }
    void operator()(string s)
    {
        maxlen = max(maxlen, s.size());
    }
    string::size_type maxlen;
};
int main()
{
    vector<string> names{"Smith", "Jones", "Johnson", "Grant"};
    maxlenftn maxf;
    for_each(names.begin(), names.end(), [&](string n) -> void
             { maxf(n); });
    cout << maxf.maxlen << endl;
    return 0;
}
/*
It didn't work before becuase for_each creates a copy of maxf for each index, and our original maxf defined on line 18 was never used.
It can be fixed by using a lambda function that calls maxf(n) for each name n where maxf is passed by ref.
*/
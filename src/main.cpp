#include"ring.h"

#include <iostream>

using namespace std;

struct A
{
    unsigned long long x;
    A(unsigned long long x) : x(x) {}
};

int main()
{
    ring<A> r;
    ring<A>::iterator it;

    unsigned long long count = 0;
    while (count < 5)
        r.insert_next(new A(count++));

    cout << (*r.get_iterator_current()).x << endl;
    cout << (*--r.get_iterator_current()).x << endl;
    cout << (*++r.get_iterator_current()).x << endl;

    it = r.get_iterator_current();
    for (auto count = r.get_size(); count-->0;)
        cout << (*it++).x << " ";
    cout << endl;

    A *a = r.move();
    cout << (*a).x << endl;
    delete a;

    it = r.get_iterator_current();
    for (auto count = r.get_size(); count-->0;)
        cout << (*it--).x << " ";
    cout << endl;

    return 0;
}

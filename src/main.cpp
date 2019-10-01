//************************************************//
//                                                //
//  ring container C++                            //
//  created by Ilya Shishkin                      //
//  cortl@8iter.ru                                //
//  http://8iter.ru                               //
//  https://github.com/cortl0/ring_container_cpp  //
//  licensed by GPL v3.0                          //
//                                                //
//************************************************//

#include <iostream>
#include <stdexcept>

#include "ring.h"

using namespace std;

struct A
{
    int x;
    A(int x) : x(x) {}
};

int main()
{
    ring<A> r;
    ring<A>::iterator it;

    try { r.move(); }
    catch (exception& e) { cout << e.what() << endl; }

    try { r.insert(nullptr); }
    catch (exception& e) { cout << e.what() << endl; }

    int count = 0;
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

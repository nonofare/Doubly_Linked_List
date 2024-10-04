#include <iostream>
#include "DLL.h";
using namespace std;

struct some_object {
    int field_1;
    char field_2;
};

int main()
{
    DLL::List<some_object>* ll = new DLL::List<some_object>();
    some_object so;
    so.field_1 = 123;
    so.field_2 = 'a';
    ll->add_at_head(so);
    delete ll;
}
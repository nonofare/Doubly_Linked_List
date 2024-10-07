#include <iostream>
#include <cmath>
#include <time.h>
#include "DLL.h"
using namespace std;
using namespace DLL;

struct some_object {
	int field_1;
	char field_2;
};

int main()
{
	const int MAX_ORDER = 6;
	DoubLinList <some_object*>* ll = new DoubLinList <some_object*>();

	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o);
		clock_t t1 = clock();
		for (int i = 0; i < n; i++) {
			some_object* so = new some_object();
			so->field_1 = rand() % 100;
			so->field_2 = 'A' + rand() % 26;
			ll->push(so);
		}
		clock_t t2 = clock();
		//cout << ll->to_string() << t1 << t2 << endl;

		const int m = pow(10, 4);
		t1 = clock();
		for (int i = 0; i < m; i++) {
			some_object* so = new some_object();
			so->field_1 = rand() % 100;
			so->field_2 = 'A' + rand() % 26;
			//ll->remove(so, some_objects_cmp);
			delete so;
		}
		t2 = clock();
		//cout << ll->to_string() << t1 << t2 << endl;
		ll->erase();
	}
	delete ll;

	return 0;
}
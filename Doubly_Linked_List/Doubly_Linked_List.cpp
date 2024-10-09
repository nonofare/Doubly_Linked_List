#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <time.h>
#include "DLL.h"
using namespace std;
using namespace DLL;

struct some_object {
	int field_1;
	char field_2;
};

std::string some_objects_to_str(some_object* so) {
	std::string text = "(" + std::to_string(so->field_1) + ", " + so->field_2 + ") ";
	return text;
}

bool some_objects_cmp(some_object* so1, some_object* so2) {
	return so1->field_1 == so2->field_1;
}

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
		cout << ll->to_str(some_objects_to_str) << "t1: " << t1 << " t2: " << t2 << endl;

		const int m = pow(10, 4);
		t1 = clock();
		for (int i = 0; i < m; i++) {
			some_object* so = new some_object();
			so->field_1 = rand() % 100;
			so->field_2 = 'A' + rand() % 26;

			ll->remove(so, some_objects_cmp);
			delete so;
		}
		t2 = clock();
		cout << ll->to_str(some_objects_to_str) << "t1: " << t1 << " t2: " << t2 << endl;
		ll->erase();
	}
	delete ll;

	return 0;
}
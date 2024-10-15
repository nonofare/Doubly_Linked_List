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

std::string some_objects_str(some_object* so) {
	std::string text = "(" + std::to_string(so->field_1) + ", " + so->field_2 + ")\n";
	return text;
}

bool some_objects_cmp1(some_object* so1, some_object* so2) {
	return so1->field_1 == so2->field_1;
}

bool some_objects_cmp2(some_object* so1, some_object* so2) {
	return so1->field_1 >= so2->field_1;
}

int main()
{
	double time = 0;
	const int MAX_PUSH_ORDER = 7;
	const int MAX_SEARCH_ORDER = 4;
	DoubLinList <some_object*>* ll = new DoubLinList <some_object*>();

	for (int i = 1; i <= MAX_PUSH_ORDER; i++)
	{
		const int n = pow(10, i);
		clock_t t1 = clock();
		for (int j = 0; j < n; j++) {
			some_object* so = new some_object();
			so->field_1 = rand() % 100;
			so->field_2 = 'A' + rand() % 26;

			ll->push(so);
		}
		clock_t t2 = clock();

		time += (double(t2 - t1) / CLOCKS_PER_SEC);
		cout << i << "# Push done - time passed: " << time << " seconds" << endl << ll->to_str(some_objects_str, 10) << endl;

		const int m = pow(10, MAX_SEARCH_ORDER);
		t1 = clock();
		for (int j = 0; j < m; j++) {
			some_object* so = new some_object();
			so->field_1 = rand() % 100;
			so->field_2 = 'A' + rand() % 26;

			ll->remove(so, some_objects_cmp1);

			delete so;
		}
		t2 = clock();

		time += (double(t2 - t1) / CLOCKS_PER_SEC);
		cout << i << "# Remove done - time passed: " << time << " seconds" << endl << ll->to_str(some_objects_str, 10) << endl;

		ll->erase();
	}
	delete ll;

	cout << "Test done - push order: 10^" << MAX_PUSH_ORDER << ", search order: 10^" << MAX_SEARCH_ORDER << ", time passed : " << time << " seconds\n";

	return 0;
}
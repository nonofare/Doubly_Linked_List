#include <iostream>
#include <random>
#include <chrono>
#include "DLL.h"

struct some_object {
	int field_1;
	char field_2;
};

std::string some_objects_str(some_object* so) {
	return "(" + std::to_string(so->field_1) + ", " + so->field_2 + ")";
}

bool some_objects_cmp(some_object* so1, some_object* so2) {
	return so1->field_1 == so2->field_1;
}

int main()
{
	const int MAX_ORDER = 6;
	const int LETTES_SIZE = 26;
	const char LETTERS[LETTES_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	static std::random_device rd;
	static std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> rnd_num(0, MAX_ORDER * 1000);
	std::uniform_int_distribution<int> rnd_let(0, LETTES_SIZE - 1);

	DLL::DoubLinList<some_object*>* dll = new DLL::DoubLinList<some_object*>();

	for (int i = 1; i <= MAX_ORDER; i++)
	{
		std::cout << "--------------------------------" << std::endl;
		std::cout << "Test: " << i << std::endl << std::endl;

		const int n = pow(10, i);

		std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
		for (int j = 0; j < n; j++) {
			some_object* so = new some_object();
			so->field_1 = rnd_num(dre);
			so->field_2 = LETTERS[rnd_let(dre)];
			dll->Push(so);
		}
		std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> pushing_time = end_time - start_time;
		std::cout << "Pushing time: " << pushing_time.count() << "s" << std::endl;
		std::cout << dll->ToString(10, some_objects_str) << std::endl;

		int hits = 0;
		const int m = pow(10, 4);

		start_time = std::chrono::high_resolution_clock::now();
		for (int j = 0; j < m; j++) {
			some_object* so = new some_object();
			so->field_1 = rnd_num(dre);
			so->field_2 = LETTERS[rnd_let(dre)];
			if (dll->Remove(so, some_objects_cmp)) hits++;
			delete so;
		}
		end_time = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> removing_time = end_time - start_time;
		std::cout << "Removing time: " << removing_time.count() << "s" << std::endl;
		std::cout << "Hits: " << hits << std::endl;
		std::cout << dll->ToString(10, some_objects_str) << std::endl;

		double total_time = pushing_time.count() + removing_time.count();
		std::cout << "Total time: " << total_time << "s" << std::endl;

		dll->Erase();
	}

	delete dll;
	return 0;
}
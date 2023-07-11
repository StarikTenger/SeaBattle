#pragma once
#include <cstdlib>
#include <sys/timeb.h>

int get_milli_count();

class Random {
public:
	static void init(int seed) {
		std::srand(seed);
	}
	static int random_int(int min, int max) {
		return std::rand() % (max + 1 - min) + min;
	}
};


#include <iostream>
#include "tests.h"

using namespace std;

int main() {
	run_tests();
	Board board;
	board.place_ship({1,1}, {1,2});
	board.place_ship({3,3}, {5,3});
	board.place_ship({6,5}, {6,8});
	board.hit({1, 1});
	board.hit({5, 5});
	board.hit({5, 6});
	board.render();
}
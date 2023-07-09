#include <iostream>
#include "tests.h"
#include "Game.h"
#include "TestAI.h"

using namespace std;

int main() {
	run_tests();
	Game game;
	TestAI* ai1 = new TestAI();
	TestAI* ai2 = new TestAI();
	assert(game.init(shared_ptr<AI>(ai1), shared_ptr<AI>(ai2)));
	int res = 0;
	for (int i = 0; i < 100 && !res; i++) {
		res = game.step();
	}
	cout << res << " wins";
}
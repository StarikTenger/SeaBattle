#include "TestAI.h"

TestAI::TestAI(Board board) : board(board) {
}

Board TestAI::init() {
    return board;
}

Vec2 TestAI::do_turn() {
	auto v = Vec2(cur_turn % 10, cur_turn / 10);
	cur_turn++;
	return v;
}

void TestAI::handle_result(int hit_status) {
}

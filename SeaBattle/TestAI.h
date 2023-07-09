#pragma once
#include "AI.h"

class TestAI : public AI {
public:
	TestAI(Board board);
	Board init() override;
	Vec2 do_turn() override;
	void handle_result(int hit_status) override;
private:
	int cur_turn = 0;
	Board board;
};


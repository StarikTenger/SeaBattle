#pragma once
#include "Board.h"

class AI {
public:
	virtual Board init() = 0;
	virtual Vec2 do_turn() = 0;
	virtual void handle_result(int hit_status) = 0;
};


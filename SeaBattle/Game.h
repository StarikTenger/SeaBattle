#pragma once
#include <memory>
#include "Board.h"
#include "AI.h"

enum GameStstus {
	GAME_CONTINUES,
	FIRST_WINS,
	SECOND_WINS,
	DRAW
};

class Game {
public:
	bool init(std::shared_ptr<AI> ai1, std::shared_ptr<AI> ai2);
	int step();
private:
	size_t step_number = 0;
	struct Player {
		Board board;
		std::shared_ptr<AI> ai;
	};
	bool init_player(Player& p);
	// Player p1 attacks player p2
	void attack(Player& p1, Player& p2);

	Player player_first;
	Player player_second;
};


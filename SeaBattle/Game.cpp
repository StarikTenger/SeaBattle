#include "Game.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Game::init(std::shared_ptr<AI> ai1, std::shared_ptr<AI> ai2) {
	player_first.ai = ai1;
	player_second.ai = ai2;
	return init_player(player_first) && init_player(player_second);
}

int Game::step() {
	attack(player_first, player_second);
	attack(player_second, player_first);
	int gameover_first = player_first.board.gameover();
	int gameover_second = player_second.board.gameover();

	// Render
	//cout << " -- " << step_number << " -- \n";
	//player_first.board.render();
	//player_second.board.render();
	stringstream ss;
	ss << " -- " << step_number << " -- \n";
	ss << player_first.board.render() << "\n";
	ss << player_second.board.render() << "\n\n";
	rendered = ss.str();

	step_number++;
	return gameover_first * 2 + gameover_second;
}

void Game::render() {
	cout << rendered;
}

bool Game::init_player(Player& p) {
	p.board = p.ai->init();
	return p.board.verify();
}

void Game::attack(Player& p1, Player& p2) {
	p1.ai->handle_result(p2.board.hit(p1.ai->do_turn()));
}

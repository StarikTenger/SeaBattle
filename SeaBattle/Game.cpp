#include "Game.h"
#include <iostream>
#include <sstream>
#include <iterator>

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
	

	step_number++;
	return gameover_first * 2 + gameover_second;
}

void Game::render() {
	stringstream ss;
	cout << "\n\n -- " << step_number << " -- \n\n";
	ss << player_first.board.render();
	string str1 = ss.str();
	ss.clear();
	ss << player_second.board.render();
	string str2 =  ss.str();
	auto until_newline = [](string::const_iterator& str) {
		while (*str != '\n') {
			cout << *str;
			str++;
		}
		str++;
	};
	auto it1 = str1.begin();
	auto it2 = str2.begin();
	for (int i = 0; i < player_first.board.get_rules().size.x; i++) {
		until_newline(it1);
		cout << "   ";
		until_newline(it2);
		cout << "\n";
	}
}

bool Game::init_player(Player& p) {
	p.board = p.ai->init();
	return p.board.verify();
}

void Game::attack(Player& p1, Player& p2) {
	p1.ai->handle_result(p2.board.hit(p1.ai->do_turn()));
}

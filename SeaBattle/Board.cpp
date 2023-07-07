#include <cassert>
#include <iostream>
#include "Board.h"

using namespace std;

Board::Board(Rules rules) : rules(rules) {
	field = {};
	for (int x = 0; x < rules.size.x; x++) {
		field.push_back({});
		for (int y = 0; y < rules.size.y; y++) {
			field[x].push_back({});
		}
	}
	ship_number = vector<size_t>(rules.ship_number.size(), 0);
	assert(field.size() == rules.size.x && field[0].size() == rules.size.y);
}

int Board::place_ship(Vec2 beg, Vec2 end) {
	Vec2 step = end - beg;        // Representing ship as a vector
	if (step.x && step.y) {       // If beg and end are not in one line
		return WRONG_ALIGN;
	}

	// Chose direction, normalize step, determine ship size
	size_t ship_size;
	if (step.x) {                  // Ship aligned along X
		ship_size = abs(step.x) + 1;
		step.x = step.x > 0 ? 1 : -1;
	}
	else {                         // Ship aligned along Y
		ship_size = abs(step.y) + 1;
		if (step.y) {
			step.y = step.y > 0 ? 1 : -1;
		}
		else {
			step.y = 1;
		}
	}

	if (ship_size >= rules.ship_number.size()) { // Ship is too big
		return WRONG_SIZE;
	}

	int return_code = 0;           // This code would contain all errors
	if (ship_number[ship_size] + 1 > rules.ship_number[ship_size]) {
		return_code |= SHIP_LIMIT; // If enough ships of this size
	}
	if (!in_borders(beg) || !in_borders(end)) {
		return_code |= BORDER_INTERSECTION; // Ship intersects field border
	}

	if (return_code) {             // If any error encountered
		return return_code;
	}

	// Sort beg and end
	if (beg.x > end.x || beg.y > end.y) {
		swap(beg, end);
		step *= -1;
	}

	// Check for ship itersections with other ships
	for (Vec2 pos = beg - Vec2(1, 1); pos != end + Vec2(1, 1); pos += Vec2(1, 0)) {
		for (pos.y = beg.y - 1; pos.y != end.y + 1; pos += Vec2(0, 1)) {
			if (in_borders(pos) && get(pos).ship) {
				return_code |= SHIP_INTERSECTION;
				break;
			}
		}
	}

	if (return_code) {             // If any error encountered
		return return_code;
	}

	// Place ship cells
	size_t ship_id = ship_hp.size();
	ship_hp.push_back(ship_size);
	for (Vec2 pos = beg; pos != end + step; pos += step) {
		get(pos).ship = ship_id;
	}

	ship_number[ship_size]++;
	return 0;
}

int Board::hit(Vec2 pos) {
	assert(in_borders(pos));
	get(pos).hit = 1;
	if (ship_hp[get(pos).ship]) {
		ship_hp[get(pos).ship]--;
	}
	return 0;
}

bool Board::verify() {
	if (ship_number.size() != rules.ship_number.size()) {
		return false;
	}
	for (int i = 0; i < ship_number.size(); i++) {
		if (ship_number[i] != rules.ship_number[i]) {
			return false;
		}
	}
	return true;
}

void Board::clear_hits() {
	for (int x = 0; x < rules.size.x; x++) {
		for (int y = 0; y < rules.size.y; y++) {
			get({ x, y }).hit = 0;
		}
	}
}

bool Board::gameover() {
	size_t hp_sum = 0;
	for (const auto hp : ship_hp) {
		hp_sum += hp;
	}
	return !hp_sum;
}

void Board::render() {
	for (int x = 0; x < rules.size.x; x++) {
		for (int y = 0; y < rules.size.y; y++) {
			switch ((bool)field[x][y].ship * 2 + field[x][y].hit) {
			case 0:
				cout << ". ";
				break;
			case 1:
				cout << "_ ";
				break;
			case 2:
				cout << "O ";
				break;
			case 3:
				cout << "X ";
				break;
			}
		}
		cout << "\n";
	}
	cout << "\n";
}

bool Board::in_borders(Vec2 pos) {
	return pos.x >= 0 && pos.y >= 0 &&
		pos.x < rules.size.x&&
		pos.y < rules.size.y;
}

Cell& Board::get(Vec2 pos) {
	if (!in_borders(pos)) {
		assert(in_borders(pos));
	}
	return field[pos.x][pos.y];
}

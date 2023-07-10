#pragma once
#include <vector>
#include <string>
#include "Vec2.h"

// The board cell
struct Cell {
	int ship = 0;                  // Ship number. 0 if no ship
	bool hit = false;              // Is this cell hit
	Cell(bool ship = 0, bool hit = 0) : ship(ship), hit(hit) {}
};

// Parameters of the game
struct Rules {
	Vec2 size = { 10, 10 };        // Board size
	// Numbers of ships of each size, bypass 0
	std::vector<size_t> ship_number = { 0, 4, 3, 2, 1 };
	Rules(Vec2 size = { 10, 10 },
		std::vector<size_t> ship_number = { 0, 4, 3, 2, 1 }) :
		size(size), ship_number(ship_number) {}
};

enum PlaceError {
	WRONG_ALIGN = 1,
	WRONG_SIZE = 2,
	SHIP_LIMIT = 4,
	BORDER_INTERSECTION = 8,
	SHIP_INTERSECTION = 16
};

enum HitStatus {
	MISS = 0,
	HIT = 1,
	KILL = 2
};

class Board {
public:
	Board(Rules rules = {});

	// Place ship on given coordinates, return 0 if success
	int place_ship(Vec2 beg, Vec2 end);
	// Hit given pos, retunn HitStatus
	int hit(Vec2 pos);
	// Check if position is correct
	bool verify();
	// Clear all hits
	void clear_hits();
	// Check if all ships are destroyed
	bool gameover();
	// Render to string
	std::string render();
	// Get rules
	Rules get_rules();

	friend void test_board();
private:
	std::vector<std::vector<Cell>> field;
	std::vector<size_t> ship_number;   // Numbers of ship responding to size
	std::vector<size_t> ship_hp = {0}; // Hp of each ship on board
	Rules rules;
	bool in_borders(Vec2 pos);
	Cell& get(Vec2 pos);
};


#pragma once
#include <vector>

struct Cell {
	bool ship = false;
	bool hit = false;
	Cell(bool ship = 0, bool hit = 0) : ship(ship), hit(hit) {}
};

struct Vec2 {
	int x = 0;
	int y = 0;
	Vec2(int x = 0, int y = 0) : x(x), y(y) {}
	bool operator==(const Vec2& other) {
		return x == other.x && y == other.y;
	}
	bool operator!=(const Vec2& other) {
		return !(*this == other);
	}
	Vec2 operator+(const Vec2& other) {
		return { x + other.x, y + other.y };
	}
	Vec2 operator+=(const Vec2& other) {
		*this = *this + other;
		return *this;
	}
	Vec2 operator-(const Vec2& other) {
		return { x - other.x, y - other.y };
	}
	Vec2 operator-=(const Vec2& other) {
		*this = *this - other;
		return *this;
	}
	Vec2 operator*(int k) {
		return { x * k, y * k };
	}
	Vec2 operator*=(int k) {
		*this = *this * k;
		return *this;
	}
};

struct Rules {
	Vec2 size = { 10, 10 };
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
	// Render to console
	void render();
private:
	std::vector<std::vector<Cell>> field;
	std::vector<size_t> ship_number;
	Rules rules;
	bool in_borders(Vec2 pos);
	Cell& get(Vec2 pos);
};


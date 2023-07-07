#pragma once
#include <cassert>
#include <iostream>
#include "Board.h"

void test_vector() {
	assert(Vec2(1, 2) + Vec2(2, 1) == Vec2(3, 3));
	assert(Vec2(1, 2) - Vec2(2, 1) == Vec2(-1, 1));
	assert(Vec2(1, 2) * 2 == Vec2(2, 4));
	assert(Vec2(1, 2) * 2 == Vec2(2, 4));
	assert(Vec2(1, 1) != Vec2(1, 2));
	{
		Vec2 a(1, 2);
		a += Vec2(1, 1);
		assert(a == Vec2(2, 3));
	}
	{
		Vec2 a(1, 2);
		a -= Vec2(1, 1);
		assert(a == Vec2(0, 1));
	}
}

void test_board() {
	// Wrong align
	assert(Board().place_ship({ 0, 0 }, { -1, -1 }) == WRONG_ALIGN);
	assert(Board().place_ship({ 4, 3 }, { 3, 4 }) == WRONG_ALIGN);
	// Wrong size
	assert(Board().place_ship({ 1, 1 }, { 1, 6 }) == WRONG_SIZE);
	assert(Board().place_ship({ 1, 6 }, { 1, 1 }) == WRONG_SIZE);
	assert(Board().place_ship({ 0, 1 }, { 4, 1 }) == WRONG_SIZE);
	assert(Board().place_ship({ 5, 1 }, { 1, 1 }) == WRONG_SIZE);
	// Ship limit
	{ // 4-cell
		Board board;
		assert(!board.place_ship({ 0, 0 }, { 0, 3 }));
		assert(board.place_ship({ 2, 0 }, { 2, 3 }) == SHIP_LIMIT);
	}
	{ // 3-cell
		Board board;
		assert(!board.place_ship({ 0, 0 }, { 0, 2 }));
		assert(!board.place_ship({ 2, 0 }, { 2, 2 }));
		assert(board.place_ship({ 4, 0 }, { 4, 2 }) == SHIP_LIMIT);
	}
	{ // 2-cell
		Board board;
		assert(!board.place_ship({ 0, 0 }, { 0, 1 }));
		assert(!board.place_ship({ 2, 0 }, { 2, 1 }));
		assert(!board.place_ship({ 4, 0 }, { 4, 1 }));
		assert(board.place_ship({ 6, 0 }, { 6, 1 }) == SHIP_LIMIT);
	}
	{ // 1-cell
		Board board;
		assert(!board.place_ship({ 0, 0 }, { 0, 0 }));
		assert(!board.place_ship({ 2, 0 }, { 2, 0 }));
		assert(!board.place_ship({ 4, 0 }, { 4, 0 }));
		assert(!board.place_ship({ 6, 0 }, { 6, 0 }));
		assert(board.place_ship({ 6, 0 }, { 6, 0 }) == SHIP_LIMIT);
	}
	// Border intersection
	assert(Board().place_ship({ 0, 2 }, { 0, -1 }) == BORDER_INTERSECTION);
	assert(Board().place_ship({ -1, 0 }, { 2, 0 }) == BORDER_INTERSECTION);
	assert(Board().place_ship({ 2, 9 }, { 2, 11 }) == BORDER_INTERSECTION);
	// Ship intersection
	{
		Board board;
		assert(!board.place_ship({ 0, 0 }, { 0, 2 }));
		assert(board.place_ship({ 0, 0 }, { 2, 0 }) == SHIP_INTERSECTION);
	}
	{
		Board board;
		assert(!board.place_ship({ 0, 0 }, { 0, 2 }));
		assert(board.place_ship({ 2, 0 }, { 0, 0 }) == SHIP_INTERSECTION);
	}
	{
		Board board;
		assert(!board.place_ship({ 0, 2 }, { 0, 0 }));
		assert(board.place_ship({ 2, 0 }, { 0, 0 }) == SHIP_INTERSECTION);
	}
	{
		Board board;
		assert(!board.place_ship({ 0, 2 }, { 0, 0 }));
		assert(board.place_ship({ 1, 2 }, { 1, 0 }) == SHIP_INTERSECTION);
	}
	{
		Board board;
		assert(!board.place_ship({ 3, 3 }, { 3, 5 }));
		assert(board.place_ship({ 4, 3 }, { 6, 3 }) == SHIP_INTERSECTION);
	}
	// Hits
	{
		Board board;
		assert(!board.place_ship({ 1,1 }, { 1,2 }));
		assert(!board.place_ship({ 3,3 }, { 5,3 }));
		assert(!board.place_ship({ 6,5 }, { 6,8 }));
		std::vector<size_t> ship_hp = { 0, 2, 3, 4 };
		assert(board.ship_hp == ship_hp);
		board.hit({ 1, 1 });
		board.hit({ 5, 5 });
		board.hit({ 5, 6 });
		ship_hp = { 0, 1, 3, 4 };
		assert(board.ship_hp == ship_hp);
		board.hit({ 1, 2 });
		board.hit({ 4, 3 });
		ship_hp = { 0, 0, 2, 4 };
		assert(board.ship_hp == ship_hp);
	}
	// Verify
	{
		Board board;
		assert(!board.place_ship({ 2, 0 }, { 4,0 }));
		assert(!board.verify());
		assert(!board.place_ship({ 6, 0 }, { 9,0 }));
		assert(!board.verify());
		assert(!board.place_ship({ 4,2 }, { 5,2 }));
		assert(!board.verify());
		assert(!board.place_ship({ 7,2 }, { 9,2 }));
		assert(!board.verify());
		assert(!board.place_ship({ 5,4 }, { 6,4 }));
		assert(!board.verify());
		assert(!board.place_ship({ 8,4 }, { 9,4 }));
		assert(!board.verify());
		assert(!board.place_ship({ 0,5 }, { 0,5 }));
		assert(!board.verify());
		assert(!board.place_ship({ 2,5 }, { 2,5 }));
		assert(!board.verify());
		assert(!board.place_ship({ 7,6 }, { 7,6 }));
		assert(!board.verify());
		assert(!board.place_ship({ 4,7 }, { 4,7 }));
		assert(board.verify());
		board.render();
	}
}

void run_tests() {
	test_vector();
	test_board();
}
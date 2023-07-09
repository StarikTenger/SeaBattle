#include "TestAI.h"

Board TestAI::init() {
	Board board;
	board.place_ship({ 2, 0 }, { 4,0 });	
	board.place_ship({ 6, 0 }, { 9,0 });	
	board.place_ship({ 4,2 }, { 5,2 });	
	board.place_ship({ 7,2 }, { 9,2 });	
	board.place_ship({ 5,4 }, { 6,4 });	
	board.place_ship({ 8,4 }, { 9,4 });	
	board.place_ship({ 0,5 }, { 0,5 });	
	board.place_ship({ 2,5 }, { 2,5 });	
	board.place_ship({ 7,6 }, { 7,6 });	
	board.place_ship({ 4,7 }, { 4,7 });
    return board;
}

Vec2 TestAI::do_turn() {
	auto v = Vec2(cur_turn % 10, cur_turn / 10);
	cur_turn++;
	return v;
}

void TestAI::handle_result(int hit_status) {
}

#include "Board.h"

Board::Board() {
	map = gcnew array<BoardCell^, 2>(11, 11);
	ships = gcnew List<Ship^>;
	shipsAlive = 10;
}

Ship^ Board::getShip(int x, int y) {
	for each (Ship ^ ship in ships) {
		if (ship->isLocatedAt(x, y)) {
			return ship;
		}
	}
	return nullptr;
}

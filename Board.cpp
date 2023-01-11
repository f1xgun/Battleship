#include "Board.h"

// конструктор без аргументов класса Board, в результате получим новый объект типа Board
Board::Board() {
	map = gcnew array<BoardCell^, 2>(11, 11);
	ships = gcnew List<Ship^>;
	shipsAlive = 10;
}

// функция получения корабля или нулевого указателя в случае отсутствия \
args: координаты х и у
Ship^ Board::getShip(int x, int y) {
	for each (Ship ^ ship in ships) {
		if (ship->isLocatedAt(x, y)) {
			return ship;
		}
	}
	return nullptr;
}

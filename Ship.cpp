#include "Ship.h"

// конструктор с аргументами класса Ship, args: координаты начала корабля, его длина и направление \
в результате получим новый объект типа Ship
Ship::Ship(int _x, int _y, int _length, int _orientation) {
	x = _x;
	y = _y;
	length = _length;
	orientation = _orientation;
}

// функция проверки находится ли корабль по данным координатам, args: координаты х и y \
в результате получим правдивость нахождения кораблю в данных координатах или нет
bool Ship::isLocatedAt(int _x, int _y) {
	int yRight = y, xRight = x;
	if (orientation) {
		yRight = y + length - 1;
	}
	else {
		xRight = x + length - 1;
	}
	return (_x >= x && _x <= xRight && _y >= y && _y <= yRight);
}

// функция получения значения свойства состояния потопления корабля
bool Ship::isSunk::get() {
	return hitCount == length;
}
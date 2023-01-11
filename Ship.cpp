#include "Ship.h"

// ����������� � ����������� ������ Ship, args: ���������� ������ �������, ��� ����� � ����������� \
� ���������� ������� ����� ������ ���� Ship
Ship::Ship(int _x, int _y, int _length, int _orientation) {
	x = _x;
	y = _y;
	length = _length;
	orientation = _orientation;
}

// ������� �������� ��������� �� ������� �� ������ �����������, args: ���������� � � y \
� ���������� ������� ����������� ���������� ������� � ������ ����������� ��� ���
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

// ������� ��������� �������� �������� ��������� ���������� �������
bool Ship::isSunk::get() {
	return hitCount == length;
}
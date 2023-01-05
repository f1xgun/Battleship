#pragma once

ref class Ship
{
public:
	Ship(int x, int y, int length, int orientation);
	int x;
	int y;
	int length;
	int hitCount;
	int orientation;
	bool isSunk;

	bool isLocatedAt(int x, int y);
};
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
	property bool isSunk{
		bool get();
	}

	bool isLocatedAt(int x, int y);
};
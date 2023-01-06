#pragma once
#include "BoardCell.h"
#include "Ship.h"
using namespace System::Collections::Generic;

ref class Board : Control {
public:
	array<BoardCell^, 2>^ map;
	List<Ship^>^ ships;
	int shipsAlive;
	Board();
	Ship^ getShip(int x, int y);
};
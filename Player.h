#pragma once
#include "Board.h"
using namespace System::Collections::Generic;

public enum struct ShotResult
{
	Missed,
	ShipHit,
	ShipSunked
};



ref class Player {
public:
	Dictionary<Point, ShotResult>^ historyShots;
	Board^ board;
	List<Point>^ targets;

	Player(Board^ enemyBoard);
	void addShotResult(int x, int y, ShotResult result);
	ShotResult shotTo(int x, int y);
};

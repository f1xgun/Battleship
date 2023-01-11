#include "Player.h"

// ����������� ������ Player \
args: ������ ���� Board, ���������� ������ ����������, � ���������� ������� ����� ������ ���� Player
Player::Player(Board^ enemyBoard) {
	board = enemyBoard;
	historyShots = gcnew Dictionary<Point, ShotResult>();
	targets = gcnew List<Point>();
}

// ������� ���������� ��������� �������� � ��� ���������� � ������� ��������� \
args: ���������� ��������, ��������� ��������
void Player::addShotResult(int x, int y, ShotResult result) {
	historyShots[Point(x, y)] = result;
}

// ������� �������� \
args: ���������� ��������, � ���������� ������� ��������� ��������� ������, � ������� ��������� ������� � ��������� ��������
ShotResult Player::shotTo(int x, int y) {
	Ship^ ship = board->getShip(x, y);
	
	if (ship == nullptr)
	{
		board->map[y, x]->State = BoardCellState::MissedShot;
		return ShotResult::Missed;
	}
	board->map[y, x]->State = BoardCellState::ShotShip;

	ship->hitCount++;

	if (ship->isSunk) {
		board->shipsAlive--;
		int yRight = ship->y, xRight = ship->x;
		if (ship->orientation) {
			yRight = ship->y + ship->length - 1;
		}
		else {
			xRight = ship->x + ship->length - 1;
		}
		for (int i = ship->x; i < xRight + 1; i++)
			for (int j = ship->y; j < yRight + 1; j++)
				board->map[j, i]->State = BoardCellState::ShipSunked;
		return ShotResult::ShipSunked;
	}
	return ShotResult::ShipHit;
}
#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public enum struct BoardCellState
{
	Empty,
	MissedShot,
	Ship,
	ShotShip,
	ShipSunked
};

ref class BoardCell : Label
{
private:
	static initonly Color DefaultBorderColor = Color::FromArgb(214, 214, 214);
	static initonly Color DefaultBackgroundColor = Color::FromArgb(222, 222, 222);
	static initonly Color ShipColor = Color::FromArgb(0, 255, 25);
	static initonly Color ShipSunkedColor = Color::FromArgb(222, 0, 0);

	static initonly Char ShipHitChar = 'x';
	static initonly Char MissedHitChar = (Char)(0x2022);

	void OnCellStateChenged();
	BoardCellState _state;

protected:
	virtual void OnPaint(PaintEventArgs^ e) override;


public:
	BoardCell(int x, int y);
	property int X;
	property int Y;

	property BoardCellState State
	{
		BoardCellState get();
		void set(BoardCellState value);
	};
};


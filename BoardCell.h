#pragma once
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public enum struct BoardCellState
{
	Empty,
	MissedShot,
	Ship,
	ShotShip
};

ref class BoardCell : Label
{
private:
	static initonly Color DefaultBorderColor = Color::FromArgb(214, 214, 214);
	static initonly Color DefaultBackgroundColor = Color::FromArgb(222, 222, 222);
	static initonly Color ShipColor = Color::FromArgb(0, 255, 25);

	static initonly Char ShipHitChar = (Char)(0x72);
	static initonly Char MissedHitChar = (Char)(0x3D);

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

ref class BoardCellEventArgs : EventArgs {
private:
	int _x, _y;
public:
	BoardCellEventArgs(int x, int y);
	int getX();
	int getY();
};
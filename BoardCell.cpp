#include "BoardCell.h"


// ����������� � ����������� ������ BoardCell \
args: ���������� x � y, � ���������� ������� ����� ������ ���� BoardCell
BoardCell::BoardCell(int x, int y)
{
	X = x;
	Y = y;
	TextAlign = ContentAlignment::MiddleCenter;
	Location = Point(x, y);
	BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	State = BoardCellState::Empty;
}

// ������� ��������� �������� ���� ������ ����� ��� ��������� �� ���������
void BoardCell::OnCellStateChenged()
{
	SuspendLayout();
	switch (_state)
	{
	case BoardCellState::Empty:
		Text = String::Empty;
		BackColor = DefaultBackgroundColor;
		break;
	case BoardCellState::MissedShot:
		Text = MissedHitChar.ToString();
		BackColor = DefaultBackgroundColor;
		break;
	case BoardCellState::Ship:
		Text = String::Empty;
		BackColor = ShipColor;
		break;
	case BoardCellState::ShotShip:
		Text = ShipHitChar.ToString();
		BackColor = ShipColor;
		break;
	case BoardCellState::ShipSunked:
		BackColor = ShipSunkedColor;
		Text = ShipHitChar.ToString();
		break;
	}
	Invalidate();
	ResumeLayout();
}

// ������� ��������� ������ �����
void BoardCell::OnPaint(PaintEventArgs^ e)
{
	Label::OnPaint(e);

	Pen^ pen = gcnew Pen(DefaultBorderColor);
	pen->Alignment = PenAlignment::Inset;
	pen->DashStyle = DashStyle::Solid;

	Rectangle rect = ClientRectangle;
	rect.Height -= 1;
	rect.Width -= 1;

	e->Graphics->DrawRectangle(pen, rect);

	delete pen;
}

// ������� ��� ��������� �������� �������� ��������� ������
BoardCellState BoardCell::State::get()
{
	return _state;
}

// ������� ��� ��������� �������� ��������� ������, args: ����� ��������� \
� ���������� ������� ����������� ������ � ����������� �� ������ ���������
void BoardCell::State::set(BoardCellState value)
{
	_state = value;
	OnCellStateChenged();
}


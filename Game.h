#pragma once
#include <cstdlib>
#include "MainForm.h"
#include "BoardCell.h"
#include <iostream>


namespace Battleship {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Game
	/// </summary>
	public ref class Game : public System::Windows::Forms::Form
	{
	public:
		Random^ random = gcnew Random();

		Game(MainForm^ parent)
		{
			InitializeComponent();
			this->Text = "Морской бой";
			Init();
			parentForm = parent;
		}

		

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Game()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		const int mapSize = 11;
		const int cellSize = 30;
		const int distanceBetween = 50;
		String^ alphabet = "АБВГДЕЖЗИК";
		MainForm^ parentForm;
		array<BoardCell^, 2>^ _cellsMap = gcnew array<BoardCell^, 2>(11, 11);
		array<BoardCell^, 2>^ _cellsEnemyMap = gcnew array<BoardCell^, 2>(11, 11);

		void Init() {
			CreateMaps();
		}

		void CreateMaps() {
			this->Width = mapSize * 2 * cellSize + distanceBetween;
			this->Height = mapSize * cellSize + 100;
			for (int i = 0; i < mapSize; i++) {
				for (int j = 0; j < mapSize; j++) {
					BoardCell^ cell = gcnew BoardCell(j * cellSize, i * cellSize);
					cell->State = BoardCellState::Empty;
					cell->Size = System::Drawing::Size(cellSize, cellSize);
					if (j == 0 || i == 0) {
						cell->BackColor = Color::Gray;
						if (i == 0 && j > 0) {
							cell->Text = alphabet[j - 1].ToString();
						}
						if (j == 0 && i > 0) {
							cell->Text = i.ToString();
						}
					}
					else {
						_cellsMap[i, j] = cell;
					}
					this->Controls->Add(cell);
				}
			}

			GenerateShips(_cellsMap);

			for (int i = 0; i < mapSize; i++) {
				for (int j = 0; j < mapSize; j++) {
					BoardCell^ cell = gcnew BoardCell(360 + j * cellSize, i * cellSize);
					cell->State = BoardCellState::Empty;
					cell->Size = System::Drawing::Size(cellSize, cellSize);
					if (j == 0 || i == 0) {
						cell->BackColor = Color::Gray;
						if (i == 0 && j > 0) {
							cell->Text = alphabet[j - 1].ToString();
						}
						if (j == 0 && i > 0) {
							cell->Text = i.ToString();
						}
					}
					else {
						_cellsEnemyMap[i, j] = cell;
					}
					this->Controls->Add(cell);
				}
			}

			GenerateShips(_cellsEnemyMap);

			Label^ map1Title = gcnew Label();
			map1Title->Text = "Карта игрока 1";
			map1Title->Location = Point(mapSize * cellSize / 2 - map1Title->Size.Width / 2, mapSize * cellSize + 20);
			this->Controls->Add(map1Title);

			Label^ map2Title = gcnew Label();
			map2Title->Text = "Карта игрока 2";
			map2Title->Location = Point(3 * mapSize * cellSize / 2 + distanceBetween - map2Title->Size.Width / 2, mapSize * cellSize + 20);
			this->Controls->Add(map2Title);
		}

		void GenerateShips(array<BoardCell^, 2>^ _cells) {
			int ships[] = { 4, 3, 2, 1 };
			int x, y;
			int dir = 0;
			int type = 3;
			while (ships[0] > 0) {
				if (ships[type] == 0) type--;
				x = random->Next(1, 10);
				y = random->Next(1, 10);
				dir = random->Next(2);
				if (insertShip(x, y, type, dir, _cells)) {
					ships[type]--;
				}
			}
		}

		bool insertShip(int x, int y, int type, int dir, array<BoardCell^, 2>^ _cells) {
			int lengthShip = type + 1;
			if (x < 1 || x > mapSize - 1 || y < 1 || y > mapSize - 1)
				return false;
			bool flag = true;
			switch (dir) {
			case 0:
				if (lengthShip + x > mapSize - 1)
					return false;
				for (int i = x; i < x + lengthShip; i++) {
					if (flag)
						flag = test(i, y, _cells);
					else break;
				}
				if (!flag) {
					return false;
				}
				else {
					for (int i = x; i < x + lengthShip; i++) {
						_cells[i, y]->State = BoardCellState::Ship;
					}
					return true;
				}
				break;
			case 1:
				if (lengthShip + y > mapSize - 1)
					return false;
				for (int i = y; i < y + lengthShip; i++) {
					if (flag)
						flag = test(x, i, _cells);
					else break;
				}
				if (!flag) {
					return false;
				}
				else {
					for (int i = y; i < y + lengthShip; i++) {
						_cells[x, i]->State = BoardCellState::Ship;
					}
					return true;
				}
				break;
			}
		}

		bool test(int x, int y, array<BoardCell^, 2>^ _cells) {
			if (x == 1) {
				if (y != 1 && y != mapSize - 1 && (_cells[x, y]->State == BoardCellState::Ship || _cells[x + 1, y]->State == BoardCellState::Ship ||
					_cells[x, y + 1]->State == BoardCellState::Ship || _cells[x + 1, y + 1]->State == BoardCellState::Ship ||
					_cells[x, y - 1]->State == BoardCellState::Ship || _cells[x + 1, y - 1]->State == BoardCellState::Ship))
					return false;
				else return true;
				if (y == mapSize - 1 && (_cells[x, y - 1]->State == BoardCellState::Ship || _cells[x + 1, y - 1]->State == BoardCellState::Ship ||
					_cells[x, y]->State == BoardCellState::Ship || _cells[x + 1, y]->State == BoardCellState::Ship))
					return false;
				else return true;
				if (y == 1 && (_cells[x, y + 1]->State == BoardCellState::Ship || _cells[x + 1, y + 1]->State == BoardCellState::Ship ||
					_cells[x, y]->State == BoardCellState::Ship || _cells[x + 1, y]->State == BoardCellState::Ship))
					return false;
				else return true;
			}
			if (x == mapSize - 1) {
				if (y != 1 && y != mapSize - 1 && (_cells[x, y]->State == BoardCellState::Ship || _cells[x - 1, y]->State == BoardCellState::Ship ||
					_cells[x, y + 1]->State == BoardCellState::Ship || _cells[x - 1, y + 1]->State == BoardCellState::Ship ||
					_cells[x, y - 1]->State == BoardCellState::Ship || _cells[x - 1, y - 1]->State == BoardCellState::Ship))
					return false;
				else return true;
				if (y == mapSize - 1 && (_cells[x, y - 1]->State == BoardCellState::Ship || _cells[x - 1, y - 1]->State == BoardCellState::Ship ||
					_cells[x, y]->State == BoardCellState::Ship || _cells[x - 1, y]->State == BoardCellState::Ship))
					return false;
				else return true;
				if (y == 1 && (_cells[x, y + 1]->State == BoardCellState::Ship || _cells[x - 1, y + 1]->State == BoardCellState::Ship ||
					_cells[x, y]->State == BoardCellState::Ship || _cells[x - 1, y]->State == BoardCellState::Ship))
					return false;
				else return true;
			}
			if (y == 1) {
				if (x != 1 && x != mapSize - 1 && (_cells[x - 1, y]->State == BoardCellState::Ship || _cells[x, y]->State == BoardCellState::Ship ||
					_cells[x + 1, y]->State == BoardCellState::Ship || _cells[x - 1, y + 1]->State == BoardCellState::Ship ||
					_cells[x, y + 1]->State == BoardCellState::Ship || _cells[x + 1, y + 1]->State == BoardCellState::Ship))
					return false;
				else return true;
				if (x == 1 && (_cells[x, y + 1]->State == BoardCellState::Ship || _cells[x + 1, y + 1]->State == BoardCellState::Ship ||
					_cells[x, y]->State == BoardCellState::Ship || _cells[x + 1, y]->State == BoardCellState::Ship))
					return false;
				else return true;
				if (x == mapSize - 1 && (_cells[x, y + 1]->State == BoardCellState::Ship || _cells[x - 1, y + 1]->State == BoardCellState::Ship ||
					_cells[x, y]->State == BoardCellState::Ship || _cells[x - 1, y]->State == BoardCellState::Ship))
					return false;
				else return true;
			}
			if (y == mapSize - 1) {
				if (x != 1 && x != mapSize - 1 && (_cells[x - 1, y]->State == BoardCellState::Ship || _cells[x, y]->State == BoardCellState::Ship ||
					_cells[x + 1, y]->State == BoardCellState::Ship || _cells[x - 1, y - 1]->State == BoardCellState::Ship ||
					_cells[x, y - 1]->State == BoardCellState::Ship || _cells[x + 1, y - 1]->State == BoardCellState::Ship))
					return false;
				else return true;
				if (x == mapSize - 1 && (_cells[x, y - 1]->State == BoardCellState::Ship || _cells[x - 1, y - 1]->State == BoardCellState::Ship ||
					_cells[x, y]->State == BoardCellState::Ship || _cells[x - 1, y]->State == BoardCellState::Ship))
					return false;
				else return true;
				if (x == 1 && (_cells[x, y - 1]->State == BoardCellState::Ship || _cells[x + 1, y - 1]->State == BoardCellState::Ship ||
					_cells[x, y]->State == BoardCellState::Ship || _cells[x + 1, y]->State == BoardCellState::Ship))
					return false;
				else return true;
			}
			if (_cells[x - 1, y - 1]->State == BoardCellState::Ship || _cells[x, y - 1]->State == BoardCellState::Ship ||
				_cells[x + 1, y - 1]->State == BoardCellState::Ship || _cells[x - 1, y]->State == BoardCellState::Ship ||
				_cells[x, y]->State == BoardCellState::Ship || _cells[x + 1, y]->State == BoardCellState::Ship ||
				_cells[x - 1, y + 1]->State == BoardCellState::Ship || _cells[x, y + 1]->State == BoardCellState::Ship ||
				_cells[x + 1, y + 1]->State == BoardCellState::Ship)
				return false;
			return true;
		}

		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(300,300);
			this->Text = L"Game";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}

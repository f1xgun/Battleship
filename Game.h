#pragma once
#include <cstdlib>
#include "MainForm.h"
#include "Player.h"
#include <iostream>


const int PLAYER_INDEX = 1;
const int COMPUTER_INDEX = 2;

namespace Battleship {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

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

			//StartGame();
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
		const int MAP_SIZE = 11;
		const int cellSize = 30;
		const int distanceBetween = 60;
		String^ alphabet = "АБВГДЕЖЗИК";
		MainForm^ parentForm;
		int playerIndex = PLAYER_INDEX;
		Board^ _board = gcnew Board();
		Board^ _enemyBoard = gcnew Board();
		Player^ player1;
		Player^ player2;
		//Timer^ timer = gcnew Timer();

		void Init() {
			CreateMaps();
		}

		void CreateMaps() {
			this->Width = (MAP_SIZE + 1) * 2 * cellSize;
			this->Height = MAP_SIZE * cellSize + 100;
			CreateBoard(_board, true, 0);
			CreateBoard(_enemyBoard, false, 360);

			player1 = gcnew Player(_enemyBoard);
			player2 = gcnew Player(_board);


			Label^ map1Title = gcnew Label();
			map1Title->Text = "Карта игрока 1";
			map1Title->Location = Point(MAP_SIZE * cellSize / 2 - map1Title->Size.Width / 2, MAP_SIZE * cellSize + 20);
			map1Title->Click += gcnew System::EventHandler(this, &Battleship::Game::startGame);
			this->Controls->Add(map1Title);


			Label^ map2Title = gcnew Label();
			map2Title->Text = "Карта игрока 2";
			map2Title->Location = Point(3 * MAP_SIZE * cellSize / 2 + cellSize * 2 - map2Title->Size.Width / 2, MAP_SIZE * cellSize + 20);
			this->Controls->Add(map2Title);
		}

		void CreateBoard(Board^ board, bool isPlayer, int right) {
			for (int i = 0; i < MAP_SIZE; i++) {
				for (int j = 0; j < MAP_SIZE; j++) {
					BoardCell^ cell = gcnew BoardCell(j * cellSize + right, i * cellSize);
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
						if (!isPlayer)
							cell->Click += gcnew EventHandler(this, &Game::OnCellClick);
						board->map[i, j] = cell;
					}
					this->Controls->Add(cell);
				}
			}
			GenerateShips(board, isPlayer);
		}

		void GenerateShips(Board^ board, bool drawShips) {
			int ships[] = { 4, 3, 2, 1 };
			int x, y;
			int dir = 0;
			int type = 3;
			while (ships[0] > 0) {
				if (ships[type] == 0) type--;
				x = random->Next(1, 11);
				y = random->Next(1, 11);
				dir = random->Next(2);
				if (insertShip(x, y, type, dir, board, drawShips)) {
					ships[type]--;
				}
			}
		}

		bool insertShip(int x, int y, int type, int dir, Board^ board, bool drawShips) {
			int lengthShip = type + 1;
			if (x < 1 || x > MAP_SIZE - 1 || y < 1 || y > MAP_SIZE - 1)
				return false;
			if (test(x, y, lengthShip, dir, board->ships)) {
				switch (dir) {
				case 0:
					if (lengthShip + x > MAP_SIZE - 1)
						return false;
					board->ships->Add(gcnew Ship(x, y, lengthShip, dir));
					if (drawShips) {
						for (int i = x; i < x + lengthShip; i++) {
							board->map[i, y]->State = BoardCellState::Ship;
						}
					}
					break;
				case 1:
					if (lengthShip + y > MAP_SIZE - 1)
						return false;
					board->ships->Add(gcnew Ship(x, y, lengthShip, dir));
					if (drawShips) {
						for (int i = y; i < y + lengthShip; i++) {
							board->map[x, i]->State = BoardCellState::Ship;
						}
					}
					break;
				}
				return true;
			}
			else {
				return false;
			}
		}

		bool test(int x, int y, int length, int orientation, List<Ship^>^ ships) {
			int width, height;
			if (orientation == 0) {
				width = length + 2;
				height = 3;
				x -= 1;
				y -= 1;
			}
			else {
				width = 3;
				height = length + 2;
				x -= 1;
				y -= 1;
			}

			for each (Ship ^ ship in ships) {
				int yRight = ship->y, xRight = ship->x;
				if (ship->orientation) {
					yRight = ship->y + ship->length - 1;
				}
				else {
					xRight = ship->x + ship->length - 1;
				}
				if (!(ship->x > x + width - 1 || xRight < x || ship->y > y + height - 1 || yRight < y)) {
					return false;
				}
			}
			return true;
		}


		//void StartGame() {
		//	playerIndex = random->Next(1, 3);
		//	int i = 100;
		//	while (i--) {
		//		if (playerIndex == COMPUTER_INDEX) {
		//			//timer->Stop();
		//			if (computerShot(player2) == ShotResult::Missed)
		//				playerIndex = PLAYER_INDEX;
		//		}
		//		/*else {
		//			if (computerShot(player1) == ShotResult::Missed)
		//				playerIndex = COMPUTER_INDEX;
		//		}*/
		//		/*else {
		//			timer->Interval = random->Next(100, 1000);
		//			timer->Start();
		//		}*/
		//	}
		//}

		bool isWin() {
			if (player1->board->shipsAlive == 0) {
				this->Controls->Clear();
				Label^ Win = gcnew Label();
				Win->Text = "Выиграл игрок #1";
				Win->Location = Point(this->ClientSize.Width / 2 - Win->Width / 2, this->ClientSize.Height / 2 - Win->Height / 2);
				this->Controls->Add(Win);
				return true;
			}
			if (player2->board->shipsAlive == 0) {
				this->Controls->Clear();
				Label^ Win = gcnew Label();
				Win->Text = "Выиграл игрок #2";
				Win->Location = Point(this->ClientSize.Width / 2 - Win->Width / 2, this->ClientSize.Height / 2 - Win->Height / 2);
				this->Controls->Add(Win);
				return true;
			}
			return false;
		}

		ShotResult computerShot(Player^ computer) {
			int x, y;
			do {
				x = random->Next(1, MAP_SIZE);
				y = random->Next(1, MAP_SIZE);
			} while (computer->historyShots->ContainsKey(Point(x, y)));

			//_board->map[x, y]->State = computer->board->map[x, y]->State;
			ShotResult result = computer->shotTo(y, x);
			computer->addShotResult(x, y, result);
			return result;
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
	void OnCellClick(Object^ sender, EventArgs^ e)
	{
		if (playerIndex == COMPUTER_INDEX)
			return;
		BoardCell^ cell = safe_cast<BoardCell^>(sender);
		int x = (int)ceil((cell->X - cellSize * 12) / cellSize);
		int y = (int)ceil(cell->Y / cellSize);
		ShotResult result;
		if (player1->historyShots->ContainsKey(Point(x, y)))
			return;
		result = player1->shotTo(x, y);
		isWin();
		player1->addShotResult(x, y, result);
		if (result == ShotResult::Missed) {
			playerIndex = COMPUTER_INDEX;
			do {
				result = computerShot(player2);
			} while (result != ShotResult::Missed && !isWin());
			playerIndex = PLAYER_INDEX;
		}
		return;
	};

	private: System::Void startGame(System::Object^ sender, System::EventArgs^ e) {
		//StartGame();
	};
	};


}

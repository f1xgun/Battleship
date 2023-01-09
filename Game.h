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
	using namespace System::IO;

	/// <summary>
	/// Сводка для Game
	/// </summary>
	public ref class Game : public System::Windows::Forms::Form
	{
	public:

		StreamWriter^ pwriter;
		StreamReader^ preader;
		Random^ random = gcnew Random();

		Game(MainForm^ parent)
		{
			InitializeComponent();
			this->Text = "Морской бой";
			parentForm = parent;
			parentForm->button1->Enabled = false;
			parentForm->button2->Enabled = false;
			Init();

			StartGame();
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
		MainForm^ parentForm;

		const int MAP_SIZE = 11;
		const int CELL_SIZE = 30;
		
		int playerIndex;
		String^ alphabet = "АБВГДЕЖЗИК";
		Board^ _board = gcnew Board();
		Board^ _enemyBoard = gcnew Board();
		Player^ player1;
		Player^ player2;
		Timer^ timer = gcnew Timer();
		ShotResult lastShotResult;
		bool read;

		void Init() {
			read = parentForm->isResume;
			if (!read) {
				pwriter = gcnew StreamWriter("game.txt");
				pwriter->WriteLine(((int)parentForm->twoComputers).ToString());
			}
			else {
				preader = File::OpenText("game.txt");
				parentForm->twoComputers = Int32::Parse(preader->ReadLine());
			}
			CreateMaps();
		}

		void CreateMaps() {
			timer->Enabled = false;
			this->Width = (MAP_SIZE + 1) * 2 * CELL_SIZE;
			this->Height = MAP_SIZE * CELL_SIZE + 100;
			CreateBoard(_board, !(parentForm->twoComputers), 0);
			CreateBoard(_enemyBoard, false, 360);

			player1 = gcnew Player(_enemyBoard);
			player2 = gcnew Player(_board);
			playerIndex = random->Next(1, 3);

			if (read) {
				uploadSteps();
				preader->Close();
				read = false;
				pwriter = gcnew StreamWriter("game.txt", true);
			}
				

			Label^ map1Title = gcnew Label();
			map1Title->Text = "Карта игрока 1";
			map1Title->Location = Point(MAP_SIZE * CELL_SIZE / 2 - map1Title->Size.Width / 2, MAP_SIZE * CELL_SIZE + 20);
			this->Controls->Add(map1Title);


			Label^ map2Title = gcnew Label();
			map2Title->Text = "Карта игрока 2";
			map2Title->Location = Point(3 * MAP_SIZE * CELL_SIZE / 2 + CELL_SIZE * 2 - map2Title->Size.Width / 2, MAP_SIZE * CELL_SIZE + 20);
			this->Controls->Add(map2Title);
		}

		void CreateBoard(Board^ board, bool isPlayer, int right) {
			for (int i = 0; i < MAP_SIZE; i++) {
				for (int j = 0; j < MAP_SIZE; j++) {
					BoardCell^ cell = gcnew BoardCell(j * CELL_SIZE + right, i * CELL_SIZE);
					cell->State = BoardCellState::Empty;
					cell->Size = System::Drawing::Size(CELL_SIZE, CELL_SIZE);
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
						if (!isPlayer && !parentForm->twoComputers)
							cell->Click += gcnew EventHandler(this, &Game::OnCellClick);
						board->map[i, j] = cell;
					}
					this->Controls->Add(cell);
				}
			}
			if (read)
				try {
					for (int i = 0; i < 10; i++) {
						array<String^>^ s = preader->ReadLine()->Split(' ');
						drawShipsOnBoard(Int32::Parse(s[0]), Int32::Parse(s[1]), Int32::Parse(s[2]), Int32::Parse(s[3]), board, isPlayer);
					}
				}
				catch (Exception^ ex) {
					GenerateShips(board, isPlayer);
					return;
				}
			else
				GenerateShips(board, isPlayer);
		}

		void uploadSteps() {
			String^ temp;
			while ((temp = preader->ReadLine()) != nullptr) {
				array<String^>^ s = temp->Split(' ');
				playerIndex = Int32::Parse(s[0]);
				if (playerIndex == PLAYER_INDEX && !parentForm->twoComputers) {
					int x = Int32::Parse(s[1]), y = Int32::Parse(s[2]);
					lastShotResult = player1->shotTo(x, y);
					player1->addShotResult(x, y, lastShotResult);
				}
				else if (playerIndex == PLAYER_INDEX && parentForm->twoComputers) {
					int x = Int32::Parse(s[1]), y = Int32::Parse(s[2]);
					lastShotResult = player1->shotTo(x, y);
					shipShotted(player1, x, y);
				}
				else {
					int x = Int32::Parse(s[1]), y = Int32::Parse(s[2]);
					lastShotResult = player2->shotTo(x, y);
					shipShotted(player2, x, y);
				}
			}
		}

		void drawShipsOnBoard(int x, int y, int lengthShip, int dir, Board^ board, bool drawShips) {
			board->ships->Add(gcnew Ship(x, y, lengthShip, dir));
			switch (dir) {
			case 0:
				if (drawShips) {
					for (int i = x; i < x + lengthShip; i++) {
						board->map[y, i]->State = BoardCellState::Ship;
					}
				}
				break;
			case 1:
				if (drawShips) {
					for (int i = y; i < y + lengthShip; i++) {
						board->map[i, x]->State = BoardCellState::Ship;
					}
				}
				break;
			}
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
			if (test(x, y, lengthShip, dir, board->ships)) {
				switch (dir) {
				case 0:
					if (lengthShip + x > MAP_SIZE - 1)
						return false;
					board->ships->Add(gcnew Ship(x, y, lengthShip, dir));
					pwriter->WriteLine(x.ToString() + " " + y.ToString() + " " + lengthShip.ToString() + " " + dir.ToString());
					if (drawShips) {
						for (int i = x; i < x + lengthShip; i++) {
							board->map[y, i]->State = BoardCellState::Ship;
						}
					}
					break;
				case 1:
					if (lengthShip + y > MAP_SIZE - 1)
						return false;
					board->ships->Add(gcnew Ship(x, y, lengthShip, dir));
					pwriter->WriteLine(x.ToString() + " " + y.ToString() + " " + lengthShip.ToString() + " " + dir.ToString());
					if (drawShips) {
						for (int i = y; i < y + lengthShip; i++) {
							board->map[i, x]->State = BoardCellState::Ship;
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


		void StartGame() {
			if (lastShotResult == ShotResult::Missed) {
				if (playerIndex == PLAYER_INDEX)
					playerIndex = COMPUTER_INDEX;
				else
					playerIndex = PLAYER_INDEX;
			}
 			timer->Tick += gcnew System::EventHandler(this, &Battleship::Game::OnTick);
			timer->Interval = 1000;
			timer->Enabled = true;
		}

		bool isWin() {
			if (player1->board->shipsAlive == 0) {
				this->Controls->Clear();
				Label^ Win = gcnew Label();
				Win->Text = "Выиграл игрок #1";
				Win->Location = Point(this->ClientSize.Width / 2 - Win->Width / 2, this->ClientSize.Height / 2 - Win->Height / 2);
				this->Controls->Add(Win);
				pwriter->Close();
				timer->Enabled = false;
				return true;
			}
			if (player2->board->shipsAlive == 0) {
				this->Controls->Clear();
				Label^ Win = gcnew Label();
				Win->Text = "Выиграл игрок #2";
				Win->Location = Point(this->ClientSize.Width / 2 - Win->Width / 2, this->ClientSize.Height / 2 - Win->Height / 2);
				this->Controls->Add(Win);
				pwriter->Close();
				timer->Enabled = false;
				return true;
			}
			return false;
		}

		void computerShot(Player^ computer) {
			int x, y;
			if (computer->targets->Count == 0)
				randomShot(computer, x, y);
			else {
				tryShotShip(computer, x, y);
			}
			lastShotResult = computer->shotTo(x, y);
			if (!read)
				pwriter->WriteLine(playerIndex.ToString() + " " + x.ToString() + " " + y.ToString());
			shipShotted(computer, x, y);
		}

		void shipShotted(Player^ computer, int x, int y) {
			if (lastShotResult == ShotResult::ShipSunked || lastShotResult == ShotResult::ShipHit) {
				computer->targets->Add(Point(x, y));
			}
			if (lastShotResult == ShotResult::ShipSunked) {
				for each (Point point in computer->targets) {
					computer->historyShots[Point(point.X - 1, point.Y - 1)] = lastShotResult;
					computer->historyShots[Point(point.X, point.Y - 1)] = lastShotResult;
					computer->historyShots[Point(point.X + 1, point.Y - 1)] = lastShotResult;
					computer->historyShots[Point(point.X - 1, point.Y)] = lastShotResult;
					computer->historyShots[Point(point.X, point.Y)] = lastShotResult;
					computer->historyShots[Point(point.X + 1, point.Y)] = lastShotResult;
					computer->historyShots[Point(point.X - 1, point.Y + 1)] = lastShotResult;
					computer->historyShots[Point(point.X, point.Y + 1)] = lastShotResult;
					computer->historyShots[Point(point.X + 1, point.Y + 1)] = lastShotResult;
				}

				computer->targets->Clear();
			}
			else {
				computer->addShotResult(x, y, lastShotResult);
			}
		}

		void tryShotShip(Player^ computer, int& x, int& y) {
			int _x, _y;
			Point lastShot, prevShot, nextShot;
			if (computer->targets->Count == 1) {
				lastShot = computer->targets[0];
				do {
					do
					{
						_x = random->Next(-1, 2);
						_y = random->Next(-1, 2);
					} while (Math::Abs(_x + _y) != 1);
					x = lastShot.X + _x;
					y = lastShot.Y + _y;

				} while (!isValidShot(computer, x, y));
				return;
			}
			else {
				lastShot = computer->targets[computer->targets->Count - 1];
				prevShot = computer->targets[computer->targets->Count - 2];
				nextShot = Point(2 * lastShot.X - prevShot.X, 2 * lastShot.Y - prevShot.Y);
				if (!isValidShot(computer, nextShot.X, nextShot.Y)) {
					x = computer->targets[0].X - computer->targets[1].X;
					y = computer->targets[0].Y - computer->targets[1].Y;

					nextShot = Point(computer->targets[0].X + x, computer->targets[0].Y + y);
					if (!isValidShot(computer, nextShot.X, nextShot.Y)) {
						nextShot = Point(computer->targets[computer->targets->Count - 1].X + x, computer->targets[computer->targets->Count - 1].Y + y);
						if (!isValidShot(computer, nextShot.X, nextShot.Y)) {
							computer->targets->Clear();
							randomShot(computer, x, y);
							return;
						}
					}
				}
			}
			x = nextShot.X;
			y = nextShot.Y;
		}

		void randomShot(Player^ computer, int& x, int& y) {
			do {
				x = random->Next(1, MAP_SIZE);
				y = random->Next(1, MAP_SIZE);
			} while (computer->historyShots->ContainsKey(Point(x, y)));
		}


		bool isValidShot(Player^ computer, int x, int y) {
			if (computer->historyShots->ContainsKey(Point(x, y))
				|| (x < 1 || x >= MAP_SIZE)
				|| (y < 1 || y >= MAP_SIZE))
				return false;
			return true;
		}

		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(300, 300);
			this->Text = L"Game";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Battleship::Game::OnFormClosing);
		}
#pragma endregion
	void OnCellClick(Object^ sender, EventArgs^ e) {
		if (playerIndex == COMPUTER_INDEX)
			return;

		BoardCell^ cell = safe_cast<BoardCell^>(sender);
		int x = (int)ceil((cell->X - CELL_SIZE * (MAP_SIZE + 1)) / CELL_SIZE);
		int y = (int)ceil(cell->Y / CELL_SIZE);

		if (player1->historyShots->ContainsKey(Point(x, y)))
			return;

		lastShotResult = player1->shotTo(x, y);
		pwriter->WriteLine(playerIndex.ToString() + " " + x.ToString() + " " + y.ToString());
		isWin();
		player1->addShotResult(x, y, lastShotResult);

		if (lastShotResult == ShotResult::Missed) {
			playerIndex = COMPUTER_INDEX;
		}
	};

	void Battleship::Game::OnTick(Object^ sender, EventArgs^ e) {
		if (playerIndex == PLAYER_INDEX && parentForm->twoComputers) {
			computerShot(player1);
			if (lastShotResult != ShotResult::Missed)
				playerIndex = PLAYER_INDEX;
			else
				playerIndex = COMPUTER_INDEX;
		}
		else if (playerIndex == COMPUTER_INDEX) {
			computerShot(player2);
			if (lastShotResult != ShotResult::Missed)
				playerIndex = COMPUTER_INDEX;
			else
				playerIndex = PLAYER_INDEX;
		}
		isWin();
	}

	void Battleship::Game::OnFormClosing(Object^ sender, FormClosingEventArgs^ e) {
		timer->Enabled = false;
		parentForm->button1->Enabled = true;
		parentForm->button2->Enabled = true;
		try {
			pwriter->Close();
		}
		catch (Exception^ ex) {
			return;
		}
		try {
			if (File::ReadAllLines("game.txt")->Length != 0) {
				parentForm->button2->Visible = true;
			}
		}
		catch (Exception^ ex) {
			return;
		}
	}
	};

}

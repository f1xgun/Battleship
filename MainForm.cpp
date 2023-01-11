#include "MainForm.h"
#include "Game.h"

using namespace System;
using namespace System::Windows::Forms;

// функция обработчик события нажатия на кнопку "Новая игра", которая устанавливает, что играют пользователь и компьютер \
и это не продолжение игры, и отображает окно игры
System::Void Battleship::MainForm::newGameButton_Click(System::Object^ sender, System::EventArgs^ e) {
	twoComputers = false;
	this->isResume = false;
	Game^ game = gcnew Game(this);
	game->Show();
}

// функция обработчик события нажатия на кнопку "Новая игра" -> "Игрок и компьютер" в "Меню", которая устанавливает,\
// что играют пользователь и компьютер и это не продолжение игры, и отображает окно игры
System::Void Battleship::MainForm::игрокИКомпьютерToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	twoComputers = false;
	this->isResume = false;
	Game^ game = gcnew Game(this);
	game->Show();
}

// функция обработчик события нажатия на кнопку "Новая игра" -> "Компьютер и компьютер" в "Меню", которая устанавливает,\
// что играют два компьютера и это не продолжение игры, и отображает окно игры
System::Void Battleship::MainForm::компьютерИКомпьютерToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	twoComputers = true;
	this->isResume = false;
	Game^ game = gcnew Game(this);
	game->Show();
}

// функция обработчик события нажатия на кнопку "Продолжить игру", которая устанавливает,\
// что играют пользователь и компьютер и это продолжение игры, и отображает окно игры
System::Void Battleship::MainForm::continueGameButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->isResume = true;
	Game^ game = gcnew Game(this);
	game->Show();
}

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Battleship::MainForm form;
	Application::Run(% form);

	return 0;
}
#include "MainForm.h"
#include "Game.h"

using namespace System;
using namespace System::Windows::Forms;

System::Void Battleship::MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
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
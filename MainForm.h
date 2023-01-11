#pragma once

namespace Battleship {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		bool twoComputers;
		bool isResume;
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::Button^ newGameButton;
	protected:
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ менюToolStripMenuItem;
	public: System::Windows::Forms::ToolStripMenuItem^ новаяИграToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ игрокИКомпьютерToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ компьютерИКомпьютерToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ обАвтореToolStripMenuItem;
	public: System::Windows::Forms::Button^ continueGameButton;
	private: Label^ text;
		   Button^ exitButton;
		   PictureBox^ picture;




	private:
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
			this->newGameButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->менюToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->новаяИграToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->игрокИКомпьютерToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->компьютерИКомпьютерToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->обАвтореToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->continueGameButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// newGameButton
			// 
			this->newGameButton->Location = System::Drawing::Point(130, 94);
			this->newGameButton->Name = L"newGameButton";
			this->newGameButton->Size = System::Drawing::Size(75, 25);
			this->newGameButton->TabIndex = 0;
			this->newGameButton->Text = L"Новая игра";
			this->newGameButton->UseVisualStyleBackColor = true;
			this->newGameButton->Click += gcnew System::EventHandler(this, &MainForm::newGameButton_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->менюToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(335, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"Меню";
			// 
			// менюToolStripMenuItem
			// 
			this->менюToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->новаяИграToolStripMenuItem,
					this->оПрограммеToolStripMenuItem, this->обАвтореToolStripMenuItem
			});
			this->менюToolStripMenuItem->Name = L"менюToolStripMenuItem";
			this->менюToolStripMenuItem->Size = System::Drawing::Size(53, 20);
			this->менюToolStripMenuItem->Text = L"Меню";
			// 
			// новаяИграToolStripMenuItem
			// 
			this->новаяИграToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->игрокИКомпьютерToolStripMenuItem,
					this->компьютерИКомпьютерToolStripMenuItem
			});
			this->новаяИграToolStripMenuItem->Name = L"новаяИграToolStripMenuItem";
			this->новаяИграToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->новаяИграToolStripMenuItem->Text = L"Новая игра";
			// 
			// игрокИКомпьютерToolStripMenuItem
			// 
			this->игрокИКомпьютерToolStripMenuItem->Name = L"игрокИКомпьютерToolStripMenuItem";
			this->игрокИКомпьютерToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->игрокИКомпьютерToolStripMenuItem->Text = L"Игрок и компьютер";
			this->игрокИКомпьютерToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::игрокИКомпьютерToolStripMenuItem_Click);
			// 
			// компьютерИКомпьютерToolStripMenuItem
			// 
			this->компьютерИКомпьютерToolStripMenuItem->Name = L"компьютерИКомпьютерToolStripMenuItem";
			this->компьютерИКомпьютерToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->компьютерИКомпьютерToolStripMenuItem->Text = L"Компьютер и компьютер";
			this->компьютерИКомпьютерToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::компьютерИКомпьютерToolStripMenuItem_Click);
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::оПрограммеToolStripMenuItem_Click);
			// 
			// обАвтореToolStripMenuItem
			// 
			this->обАвтореToolStripMenuItem->Name = L"обАвтореToolStripMenuItem";
			this->обАвтореToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->обАвтореToolStripMenuItem->Text = L"Об авторе";
			this->обАвтореToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::обАвтореToolStripMenuItem_Click);
			// 
			// continueGameButton
			// 
			this->continueGameButton->Location = System::Drawing::Point(102, 136);
			this->continueGameButton->Name = L"continueGameButton";
			this->continueGameButton->Size = System::Drawing::Size(131, 25);
			this->continueGameButton->TabIndex = 2;
			this->continueGameButton->Text = L"Продолжить игру";
			this->continueGameButton->UseVisualStyleBackColor = true;
			this->continueGameButton->Visible = false;
			this->continueGameButton->Click += gcnew System::EventHandler(this, &MainForm::continueGameButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(335, 387);
			this->Controls->Add(this->continueGameButton);
			this->Controls->Add(this->newGameButton);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"Морской бой";
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion


	private: System::Void newGameButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void игрокИКомпьютерToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void компьютерИКомпьютерToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void continueGameButton_Click(System::Object^ sender, System::EventArgs^ e);

		   // Функция для формирования содержания для пункта "О программе" при нажатии на соответствующую кнопку в меню
	private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Controls->Remove(this->text);
		this->Controls->Remove(this->exitButton);
		this->Controls->Remove(this->picture);
		this->Width = 640;
		this->Height = 640;
		this->Controls->Remove(newGameButton);
		this->Controls->Remove(continueGameButton);
		this->text = gcnew Label();
		text->TextAlign = ContentAlignment::MiddleCenter;
		text->AutoSize = false;
		text->Font = gcnew Drawing::Font("Roboto", 12);
		text->Size = System::Drawing::Size(this->ClientSize.Width - 40, this->Height - 200);
		text->Location = Point(this->ClientSize.Width / 2 - text->Width / 2, this->menuStrip1->Height);
		text->Text = "Правила игры. \
«Морской бой» — игра для двух участников, в которой игроки по очереди называют координаты на неизвестной им карте соперника. \
Если у соперника по этим координатам имеется корабль (координаты заняты), то корабль или его часть «топится», а попавший получает право сделать ещё один ход. \
Цель игрока — первым потопить все корабли противника.\n\n Корабли размещаются автоматически. После этого случайным образом определяется игрок, который ходит первым. \
Игрок, выполняющий ход, совершает выстрел нажатием левой клавиши мыши по свободной ячейке. При попадании в корабль противника - на чужом поле ставится крестик \
при промахе - точка. Если игрок попал, то он ходит еще раз, иначе ход переходит другому игроку.\n\n Победителем считается тот, кто первым потопит \
все 10 кораблей противника.\n\n В данном приложении можно играть как пользователь с компьютером, так и компьютер с компьютером. \
Также есть возможность сохранения игры и ее продолжение.";
		this->Controls->Add(text);
		this->exitButton = gcnew Button();
		exitButton->Text = "Назад";
		exitButton->Font = gcnew Drawing::Font("Roboto", 10);
		exitButton->Padding.All = 10;
		exitButton->Size = System::Drawing::Size(80, 40);
		exitButton->Location = Point(this->ClientSize.Width / 2 - exitButton->Width / 2, text->Location.Y + text->Size.Height + 20);
		exitButton->TextAlign = ContentAlignment::MiddleCenter;
		this->Controls->Add(exitButton);
		exitButton->Click += gcnew System::EventHandler(this, &Battleship::MainForm::OnClick);
	}

		   // Функция обработчик события при нажатии на кнопку "Назад" в пунктах "О программе" и "Об авторе", которая удаляет из контроллеров \
		   	   ранее добавленные компоненты и формирует кнопки для главного экрана
	private: System::Void Battleship::MainForm::OnClick(System::Object^ sender, System::EventArgs^ e) {
		this->Controls->Remove(this->text);
		this->Controls->Remove(this->exitButton);
		this->Controls->Remove(this->picture);
		this->Controls->Add(newGameButton);
		this->Controls->Add(continueGameButton);
		this->ClientSize = System::Drawing::Size(335, 387);
	}

		   // Функция для формирования содержания для пункта "Об авторе" при нажатии на соответствующую кнопку в меню
	private: System::Void обАвтореToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Controls->Remove(this->text);
		this->Controls->Remove(this->exitButton);
		this->Width = 640;
		this->Height = 640;
		this->Controls->Remove(newGameButton);
		this->Controls->Remove(continueGameButton);
		this->picture = gcnew PictureBox();
		try {
			picture->Image = Image::FromFile("ava.jpg");
			picture->Width = 180;
			picture->Height = 200;
			picture->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			picture->Location = Point(this->ClientSize.Width / 2 - picture->Width / 2, this->menuStrip1->Height + 30);
			this->Controls->Add(picture);
		}
		catch (Exception^ ex) {
			MessageBox::Show("Не удалось загрузить фотографию: " + ex->Message, "Ошибка",
				MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
		}
		this->text = gcnew Label();
		text->TextAlign = ContentAlignment::TopCenter;
		text->AutoSize = false;
		text->Font = gcnew Drawing::Font("Roboto", 12);
		text->Size = System::Drawing::Size(this->ClientSize.Width - 40, this->ClientSize.Height - picture->Height - 300);
		text->Location = Point(this->ClientSize.Width / 2 - text->Width / 2, picture->Location.Y + picture->Height + this->menuStrip1->Height + 50);
		text->Text = "Михайлов Д. С.\n 221-3210\n 2023 г.\n f1xgun@yandex.ru \n github: f1xgun";
		this->Controls->Add(text);
		this->exitButton = gcnew Button();
		exitButton->Text = "Назад";
		exitButton->Font = gcnew Drawing::Font("Roboto", 10);
		exitButton->Padding.All = 10;
		exitButton->Size = System::Drawing::Size(80, 40);
		exitButton->Location = Point(this->ClientSize.Width / 2 - exitButton->Width / 2, text->Location.Y + text->Size.Height + 20);
		exitButton->TextAlign = ContentAlignment::MiddleCenter;
		this->Controls->Add(exitButton);
		exitButton->Click += gcnew System::EventHandler(this, &Battleship::MainForm::OnClick);
	}

		   // Функция обработчик события загрузки формы, которая првоеряет наличие сохраненной игры и отображает кнопку продолжить, \
		   	   если оно имеется
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		try {
			if (File::ReadAllLines("game.txt")->Length != 0) {
				this->continueGameButton->Visible = true;
		}
	}
	catch (Exception^ ex) {
		return;
	}
}

};
}

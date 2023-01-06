#pragma once

namespace Battleship {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Ñâîäêà äëÿ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Îñâîáîäèòü âñå èñïîëüçóåìûå ğåñóğñû.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ ìåíşToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ íîâàÿÈãğàToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ èãğîêÈÊîìïüşòåğToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ êîìïüşòåğÈÊîìïüşòåğToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ îÏğîãğàììåToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ îáÀâòîğåToolStripMenuItem;
	private: System::Windows::Forms::Button^ button2;



	private:
		/// <summary>
		/// Îáÿçàòåëüíàÿ ïåğåìåííàÿ êîíñòğóêòîğà.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Òğåáóåìûé ìåòîä äëÿ ïîääåğæêè êîíñòğóêòîğà — íå èçìåíÿéòå 
		/// ñîäåğæèìîå ıòîãî ìåòîäà ñ ïîìîùüş ğåäàêòîğà êîäà.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ìåíşToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->íîâàÿÈãğàToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->èãğîêÈÊîìïüşòåğToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->êîìïüşòåğÈÊîìïüşòåğToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->îÏğîãğàììåToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->îáÀâòîğåToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(130, 94);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 25);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Íîâàÿ èãğà";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->ìåíşToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(335, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"Ìåíş";
			// 
			// ìåíşToolStripMenuItem
			// 
			this->ìåíşToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->íîâàÿÈãğàToolStripMenuItem,
					this->îÏğîãğàììåToolStripMenuItem, this->îáÀâòîğåToolStripMenuItem
			});
			this->ìåíşToolStripMenuItem->Name = L"ìåíşToolStripMenuItem";
			this->ìåíşToolStripMenuItem->Size = System::Drawing::Size(53, 20);
			this->ìåíşToolStripMenuItem->Text = L"Ìåíş";
			// 
			// íîâàÿÈãğàToolStripMenuItem
			// 
			this->íîâàÿÈãğàToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->èãğîêÈÊîìïüşòåğToolStripMenuItem,
					this->êîìïüşòåğÈÊîìïüşòåğToolStripMenuItem
			});
			this->íîâàÿÈãğàToolStripMenuItem->Name = L"íîâàÿÈãğàToolStripMenuItem";
			this->íîâàÿÈãğàToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->íîâàÿÈãğàToolStripMenuItem->Text = L"Íîâàÿ èãğà";
			// 
			// èãğîêÈÊîìïüşòåğToolStripMenuItem
			// 
			this->èãğîêÈÊîìïüşòåğToolStripMenuItem->Name = L"èãğîêÈÊîìïüşòåğToolStripMenuItem";
			this->èãğîêÈÊîìïüşòåğToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->èãğîêÈÊîìïüşòåğToolStripMenuItem->Text = L"Èãğîê è êîìïüşòåğ";
			// 
			// êîìïüşòåğÈÊîìïüşòåğToolStripMenuItem
			// 
			this->êîìïüşòåğÈÊîìïüşòåğToolStripMenuItem->Name = L"êîìïüşòåğÈÊîìïüşòåğToolStripMenuItem";
			this->êîìïüşòåğÈÊîìïüşòåğToolStripMenuItem->Size = System::Drawing::Size(214, 22);
			this->êîìïüşòåğÈÊîìïüşòåğToolStripMenuItem->Text = L"Êîìïüşòåğ è êîìïüşòåğ";
			// 
			// îÏğîãğàììåToolStripMenuItem
			// 
			this->îÏğîãğàììåToolStripMenuItem->Name = L"îÏğîãğàììåToolStripMenuItem";
			this->îÏğîãğàììåToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->îÏğîãğàììåToolStripMenuItem->Text = L"Î ïğîãğàììå";
			// 
			// îáÀâòîğåToolStripMenuItem
			// 
			this->îáÀâòîğåToolStripMenuItem->Name = L"îáÀâòîğåToolStripMenuItem";
			this->îáÀâòîğåToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->îáÀâòîğåToolStripMenuItem->Text = L"Îá àâòîğå";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(102, 136);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(131, 25);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Ïğîäîëæèòü èãğó";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(335, 387);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"Ìîğñêîé áîé";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
};
}

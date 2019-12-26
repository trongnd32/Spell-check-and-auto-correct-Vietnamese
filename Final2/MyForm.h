#pragma once

#include <string>
#include "Correct.h"

namespace Final2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ inpTextBox;
	protected:
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;

	private: System::Windows::Forms::Button^ correct;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ outTextBox;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->inpTextBox = (gcnew System::Windows::Forms::TextBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->correct = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->outTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// inpTextBox
			// 
			this->inpTextBox->BackColor = System::Drawing::Color::WhiteSmoke;
			this->inpTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->inpTextBox, L"inpTextBox");
			this->inpTextBox->Name = L"inpTextBox";
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			resources->ApplyResources(this->contextMenuStrip1, L"contextMenuStrip1");
			// 
			// correct
			// 
			this->correct->BackColor = System::Drawing::Color::SkyBlue;
			this->correct->Cursor = System::Windows::Forms::Cursors::Hand;
			this->correct->FlatAppearance->BorderSize = 0;
			resources->ApplyResources(this->correct, L"correct");
			this->correct->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->correct->Name = L"correct";
			this->correct->UseVisualStyleBackColor = false;
			this->correct->Click += gcnew System::EventHandler(this, &MyForm::correct_Click);
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Name = L"label1";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Name = L"label2";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// outTextBox
			// 
			this->outTextBox->BackColor = System::Drawing::Color::WhiteSmoke;
			this->outTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->outTextBox, L"outTextBox");
			this->outTextBox->Name = L"outTextBox";
			this->outTextBox->ReadOnly = true;
			// 
			// MyForm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->Controls->Add(this->outTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->correct);
			this->Controls->Add(this->inpTextBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Auto Correct";
			this->Text = L"Auto Correct";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}


//////
private: void MarshalString(String^ s, wstring& os) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

private: System::Void correct_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ inpText = inpTextBox->Text;


	wstring winpText;
	MarshalString(inpText, winpText);
	wstring wstr = autoCorrect(winpText);

	String^ inp = gcnew String(wstr.c_str());

	outTextBox->Text = inp;
	outTextBox->Refresh();
}
};
}

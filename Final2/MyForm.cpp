#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(cli::array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Final2::MyForm form; //Name of project, name of form, delete hyphen //Modify Example71
	Application::Run(% form);
}
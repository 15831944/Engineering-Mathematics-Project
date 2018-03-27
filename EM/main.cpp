#include "WinForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(cli::array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	EM::WinForm form;
	Application::Run(%form);
}
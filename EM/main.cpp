#include "WinForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int WinMain()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	EM::WinForm form;
	Application::Run(%form);
}
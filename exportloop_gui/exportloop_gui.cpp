// exportloop_gui.cpp : main project file.

#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace exportloop_gui;

[STAThread]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainForm());
}

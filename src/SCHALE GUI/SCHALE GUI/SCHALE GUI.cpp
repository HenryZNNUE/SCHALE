#include "SCHALE GUI.h"
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SCHALEGUI::SCHALEGUI SG;
	Application::Run(% SG);
}
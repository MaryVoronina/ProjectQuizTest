#include "quiz.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace ProjectQuizTest;
[STAThread]
int main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew quiz());

	return 0;
}

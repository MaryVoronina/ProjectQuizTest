#include "quiz.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace ProjectQuizTest;


[STAThreadAttribute]
int main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ProjectQuizTest::quiz form;
	Application::Run(gcnew quiz());

	return 0;
}

#include "Application.hpp"
#include "MainFrame.hpp"


wxIMPLEMENT_APP(Application);

bool Application::OnInit()
{
	MainFrame* mainFrame = new MainFrame("Crime Map Update Assistant");
	mainFrame->SetClientSize(800, 283);
	mainFrame->Show();

	return true;
}
#include "DoneFrame.hpp"
#include <wx/animate.h>
#include <wx/event.h>
#include <wx/statline.h>


DoneFrame::DoneFrame(const std::string& title) :
	wxFrame(nullptr, wxID_ANY, title, wxPoint(wxDefaultPosition),
		wxSize(wxDefaultSize), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX))
{
	wxPanel* panel = new wxPanel(this);

	CreateStatusBar();
	wxLogStatus("Questions, comments?  Contact Austin Bachurski at 406-758-7943 or abachurski@kalispell.com");

	wxStaticText* done = new wxStaticText(panel, wxID_ANY, (
		"All done!"),
		wxPoint(0, 10), wxSize(800, 100), wxALIGN_CENTER_HORIZONTAL);
	wxFont doneFont = done->GetFont();
	doneFont.SetPointSize(24);
	done->SetFont(doneFont);

	wxStaticText* information = new wxStaticText(panel, wxID_ANY, (
		"If you want to check your work you can click the 'Open Web Page' button\n"
		"to open a web browser to the Kalispell Crime Map."),
		wxPoint(0, 80), wxSize(800, 50), wxALIGN_CENTER_HORIZONTAL);
	wxFont informationFont = information->GetFont();
	informationFont.SetPointSize(16);
	information->SetFont(informationFont);

	wxButton* exitButton = new wxButton(panel, wxID_ANY, ("Exit"), wxPoint(5, 172));
	exitButton->Bind(wxEVT_BUTTON, &DoneFrame::exit, this);

	wxButton* helpButton = new wxButton(panel, wxID_ANY, ("Help!"), wxPoint(83, 172));
	helpButton->Bind(wxEVT_BUTTON, &DoneFrame::help, this);

	wxButton* openWebPage = new wxButton(panel, wxID_ANY, ("Open Web Page"), wxPoint(688, 172));
	openWebPage->Bind(wxEVT_BUTTON, &DoneFrame::webPage, this);
}

void DoneFrame::exit(wxCommandEvent& evt)
{
	Close();
}

void DoneFrame::help(wxCommandEvent& evt)
{
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData(new wxTextDataObject("abachurski@kalispell.com"));
		wxTheClipboard->Close();
		wxLogStatus("'abachurski@kalispell.com' copied to clipboard.");
	}

	wxMessageDialog* showHelp = new wxMessageDialog(NULL,
		"If you need help, please contact Austin Bachurski at 406-758-7943\n\
		or abachurski@kalispell.com - the email address has been copied to your clipboard.",
		"Help!", wxOK | wxICON_DEFAULT_TYPE);
	showHelp->ShowModal();
}

void DoneFrame::webPage(wxCommandEvent& evt)
{
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	SHELLEXECUTEINFOW execute = { sizeof execute };
	execute.lpVerb = L"open";
	execute.lpFile = L"microsoft-edge:https://maps.ci.kalispell.mt.us/portal/apps/webappviewer/index.html?id=ec7071a3155e4d47a87262290611acd2";
	ShellExecuteExW(&execute);
}

DoneFrame::~DoneFrame()
{}
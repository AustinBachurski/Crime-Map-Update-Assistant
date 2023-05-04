#include "CSVVideoFrame.hpp"
#include "DoneFrame.hpp"
#include "UploadFrame.hpp"
#include <wx/animate.h>
#include <wx/event.h>
#include <wx/statline.h>


UploadFrame::UploadFrame(const std::string& title) :
	wxFrame(nullptr, wxID_ANY, title, wxPoint(wxDefaultPosition),
		wxSize(wxDefaultSize), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX)),
	/*
	m_appendFeatures{ "python \"./subprocesses/append features.py\"" },
	m_deleteFeatures{ "python \"./subprocesses/delete features.py\"" },
	m_tableToPoint{ "python \"./subprocesses/table to point.py\"" }
	UNC paths used to redirect the user's desktop aren't supported,
	had to use absolute path to get it to work on the PD machine...
	*/
	m_appendFeatures{ "python \"Y:/Crime Mapping/Update Assistant/subprocesses/append features.py\"" },
	m_deleteFeatures{ "python \"Y:/Crime Mapping/Update Assistant/subprocesses/delete features.py\""},
	m_tableToPoint{ "python \"Y:/Crime Mapping/Update Assistant/subprocesses/table to point.py\""}
{
	wxPanel* panel = new wxPanel(this);

	CreateStatusBar();

	wxStaticText* instructions = new wxStaticText(panel, wxID_ANY, (
		"The CSV file has been updated, you may review the 'Animal Welfare' items\n"
		"in New World and change the incident type to 'Animal Cruelty' as needed.\n"
		"Once done, save the CSV file and click 'Next >' to upload the data to the web map."),
		wxPoint(0, 5), wxSize(800, 100), wxALIGN_CENTER_HORIZONTAL);
	wxFont instructionsFont = instructions->GetFont();
	instructionsFont.SetPointSize(16);
	instructions->SetFont(instructionsFont);

	wxStaticText* notice = new wxStaticText(panel, wxID_ANY, (
		"Due to API constraints, a separate console window will be opened for each geoprocessing process.\n"
		"Please allow each process to finish, this window will be automatically updated as each process completes."),
		wxPoint(0, 110), wxSize(800, 20), wxALIGN_CENTER_HORIZONTAL);
	wxFont noticeFont = notice->GetFont();
	noticeFont.SetPointSize(12);
	notice->SetFont(noticeFont);

	wxButton* exitButton = new wxButton(panel, wxID_ANY, ("Exit"), wxPoint(5, 172));
	exitButton->Bind(wxEVT_BUTTON, &UploadFrame::exit, this);

	wxButton* helpButton = new wxButton(panel, wxID_ANY, ("Help!"), wxPoint(83, 172));
	helpButton->Bind(wxEVT_BUTTON, &UploadFrame::help, this);

	wxButton* nextButton = new wxButton(panel, wxID_ANY, ("Next >"), wxPoint(720, 172));
	nextButton->Bind(wxEVT_BUTTON, &UploadFrame::next, this);

	wxButton* openExcelButton = new wxButton(panel, wxID_ANY, ("Open Excel"), wxPoint(637, 172));
	openExcelButton->Bind(wxEVT_BUTTON, &UploadFrame::openExcel, this);

	wxButton* showMeHowButton = new wxButton(panel, wxID_ANY, ("Show Me How!"), wxPoint(350, 172));
	showMeHowButton->Bind(wxEVT_BUTTON, &UploadFrame::showVideo, this);
}

void UploadFrame::exit(wxCommandEvent& evt)
{
	Close();
}

void UploadFrame::help(wxCommandEvent& evt)
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

void UploadFrame::next(wxCommandEvent& evt)
{
	wxLogStatus("Performing geoprocessing operations...");
	system(m_tableToPoint.c_str());
	system(m_deleteFeatures.c_str());
	system(m_appendFeatures.c_str());
	Close();

	DoneFrame* doneFrame = new DoneFrame("Crime Map Update Assistant");
	doneFrame->SetClientSize(800, 200);
	doneFrame->Show();
}

void UploadFrame::openExcel(wxCommandEvent& evt)
{
	// Get current working directory, trim string to move up one directory,
	// append path to csv, convert to wide string for SHELLEXECUTE.
	constexpr int currentDirectory = 16;
	std::string cwd = std::filesystem::current_path().string();
	std::string path = cwd.substr(0, cwd.size() - currentDirectory);
	path.append("Data/Crimecurrent.csv");
	std::wstring spreadsheetPath(path.length(), L' ');
	std::copy(path.begin(), path.end(), spreadsheetPath.begin());

	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	SHELLEXECUTEINFOW execute = { sizeof execute };
	execute.lpVerb = L"open";
	execute.lpFile = spreadsheetPath.c_str();
	ShellExecuteExW(&execute);
	Sleep(1000);
	HWND hwnd = FindWindowW(L"XLMAIN", nullptr);
	if (hwnd != nullptr)
	{
		ShowWindow(hwnd, SW_MAXIMIZE);
	}
}

void UploadFrame::showVideo(wxCommandEvent& evt)
{
	CSVVideoFrame* videoFrame = new CSVVideoFrame(
		"How to Animation",
		"./animations/CSV Instructions.mp4"
		);
	videoFrame->SetClientSize(800, 600);
	videoFrame->Show();
}

UploadFrame::~UploadFrame()
{}
#include "DSSVideoFrame.hpp"
#include "MainFrame.hpp"
#include "Parser.hpp"
#include "UploadFrame.hpp"
#include <wx/animate.h>
#include <wx/event.h>
#include <wx/statline.h>
#include <chrono>
#include <ctime>


MainFrame::MainFrame(const std::string& title) :
	wxFrame(nullptr, wxID_ANY, title, wxPoint(wxDefaultPosition),
	wxSize(wxDefaultSize), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX))
{
	wxPanel* panel = new wxPanel(this);

	CreateStatusBar();

	wxStaticText* welcome = new wxStaticText(
		panel, wxID_ANY, ("Welcome to the Crime Map Update Assistant"),
		wxPoint(0, 5), wxSize(800, 100), wxALIGN_CENTER_HORIZONTAL);
	wxFont welcomeFont = welcome->GetFont();
	welcomeFont.SetPointSize(28);
	welcome->SetFont(welcomeFont);

	wxStaticText* displayWeekNumber = new wxStaticText(
		panel, wxID_ANY, ("It is currently ISO week number: "
			+ std::format("{:%V}", std::chrono::system_clock::now())), // Current week number in ISO format.
		wxPoint(0, 75), wxSize(800, 100), wxALIGN_CENTER_HORIZONTAL);
	wxFont weekNumberFont = displayWeekNumber->GetFont();
	weekNumberFont.SetPointSize(22);
	displayWeekNumber->SetFont(weekNumberFont);

	wxStaticText* selectPrompt = new wxStaticText(panel, wxID_ANY, (
		"Please open the 'DSS Data.xlsx' spreadsheet - you can use \n"
		"the 'Open Excel' button below if you wish - refresh the data, select the\n"
		"appropriate week, save the spreadsheet, and click 'Next >' to continue."),
		wxPoint(0, 135), wxSize(800, 100), wxALIGN_CENTER_HORIZONTAL);
	wxFont selectPromptFont = selectPrompt->GetFont();
	selectPromptFont.SetPointSize(16);
	selectPrompt->SetFont(selectPromptFont);

	wxButton* exitButton = new wxButton(panel, wxID_ANY, ("Exit"), wxPoint(5, 255));
	exitButton->Bind(wxEVT_BUTTON, &MainFrame::exit, this);
	
	wxButton* helpButton = new wxButton(panel, wxID_ANY, ("Help!"), wxPoint(83, 255));
	helpButton->Bind(wxEVT_BUTTON, &MainFrame::help, this);

	wxButton* nextButton = new wxButton(panel, wxID_ANY, ("Next >"), wxPoint(720, 255));
	nextButton->Bind(wxEVT_BUTTON, &MainFrame::next, this);

	wxButton* openExcelButton = new wxButton(panel, wxID_ANY, ("Open Excel"), wxPoint(637, 255));
	openExcelButton->Bind(wxEVT_BUTTON, &MainFrame::openExcel, this);

	wxButton* showMeHowButton = new wxButton(panel, wxID_ANY, ("Show Me How!"), wxPoint(350, 255));
	showMeHowButton->Bind(wxEVT_BUTTON, &MainFrame::showVideo, this);
}

void MainFrame::exit(wxCommandEvent& evt)
{
	Close();
}

void MainFrame::help(wxCommandEvent& evt)
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

void MainFrame::next(wxCommandEvent& evt)
{
	try
	{
		parseDSS();
		Close();

		UploadFrame* uploadFrame = new UploadFrame("Crime Map Update Assistant");
		uploadFrame->SetClientSize(800, 200);
		uploadFrame->Show();
	}
	catch (...)
	{
		wxMessageDialog* noSheet = new wxMessageDialog(NULL,
			"It appears there was an error parsing the DSS data,\nplease contact Austin at 406-758-7943.",
			"Spreadsheet Error!", wxOK | wxICON_ERROR);
		noSheet->ShowModal();
		wxLogStatus("Error parsing DSS Data, please contact Austin at 406-758-7943.");
	}
}

void MainFrame::openExcel(wxCommandEvent& evt)
{
	// Get current working directory, trim string to move up one directory,
	// append path to spreadsheet, convert to wide string for SHELLEXECUTE.
	constexpr int currentDirectory = 16;
	std::string cwd = std::filesystem::current_path().string();
	std::string path = cwd.substr(0, cwd.size() - currentDirectory);
	path.append("Data/DSS Data.xlsx");
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

void MainFrame::parseDSS()
{
	Parser parse;
	parse.parseSheets();
	parse.generateCSV();
}

void MainFrame::showVideo(wxCommandEvent& evt)
{
	DSSVideoFrame* videoFrame = new DSSVideoFrame(
		"How to Video",
		"./animations/DSS Instructions.mp4"
	);
	videoFrame->SetClientSize(800, 600);
	videoFrame->Show();
}

MainFrame::~MainFrame()
{}
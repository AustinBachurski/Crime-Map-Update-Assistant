#include "CSVVideoFrame.hpp"


CSVVideoFrame::CSVVideoFrame(const std::string& title, const std::string&& videoPath) :
	wxFrame(nullptr, wxID_ANY, title, wxPoint(wxDefaultPosition),
	wxSize(wxDefaultSize), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX))
{
	wxPanel* panel = new wxPanel(this);
	
	wxMediaCtrl* video = new wxMediaCtrl(panel, wxID_ANY);
	video->Load(videoPath);
	video->SetSize(800, 600);
	video->ShowPlayerControls();
}

CSVVideoFrame::~CSVVideoFrame()
{}
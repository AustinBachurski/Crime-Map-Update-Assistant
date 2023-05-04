#pragma once

#include <algorithm>
#include <filesystem>
#include <string>
#include <wx/clipbrd.h>
#include <wx/wx.h>


class MainFrame : public wxFrame
{
public:
	MainFrame(const std::string& title);
	~MainFrame();

private:
	void exit(wxCommandEvent& evt);
	void help(wxCommandEvent& evt);
	void next(wxCommandEvent& evt);
	void openExcel(wxCommandEvent& evt);
	void parseDSS();
	void showVideo(wxCommandEvent& evt);
};
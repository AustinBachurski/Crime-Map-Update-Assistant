#pragma once

#include <string>
#include <wx/wx.h>
#include <wx/animate.h>
#include <wx/clipbrd.h>


class DoneFrame : public wxFrame
{
public:
	DoneFrame(const std::string& title);
	~DoneFrame();

private:
	void exit(wxCommandEvent& evt);
	void help(wxCommandEvent& evt);
	void webPage(wxCommandEvent& evt);
};
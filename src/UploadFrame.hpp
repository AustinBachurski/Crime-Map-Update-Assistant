#pragma once

#include <algorithm>
#include <filesystem>
#include <string>
#include <wx/clipbrd.h>
#include <wx/wx.h>
#include <wx/animate.h>


class UploadFrame : public wxFrame
{
public:
	UploadFrame(const std::string& title);
	~UploadFrame();

private:
	const std::string m_appendFeatures;
	const std::string m_deleteFeatures;
	const std::string m_tableToPoint;

	void exit(wxCommandEvent& evt);
	void help(wxCommandEvent& evt);
	void next(wxCommandEvent& evt);
	void openExcel(wxCommandEvent& evt);
	void showVideo(wxCommandEvent& evt);
};
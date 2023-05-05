#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
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
	// Python scripts.
	const std::string m_appendFeaturesScript;
	const std::string m_deleteFeaturesScript;
	const std::string m_tableToPointScript;

	// Path to subprocess folder.
	const std::string m_pathFile;

	// Methods
	std::string callPython(const std::string& script);
	void exit(wxCommandEvent& evt);
	void help(wxCommandEvent& evt);
	void next(wxCommandEvent& evt);
	void openExcel(wxCommandEvent& evt);
	void showVideo(wxCommandEvent& evt);
};

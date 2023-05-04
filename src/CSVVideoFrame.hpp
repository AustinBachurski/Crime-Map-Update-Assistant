#pragma once

#include <string>
#include <wx/wx.h>
#include <wx/mediactrl.h>


class CSVVideoFrame : public wxFrame
{
public:
	CSVVideoFrame(const std::string& title, const std::string&& videoPath);
	~CSVVideoFrame();
};
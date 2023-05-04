#pragma once

#include <string>
#include <wx/wx.h>
#include <wx/mediactrl.h>


class DSSVideoFrame : public wxFrame
{
public:
	DSSVideoFrame(const std::string& title, const std::string&& videoPath);
	~DSSVideoFrame();
};
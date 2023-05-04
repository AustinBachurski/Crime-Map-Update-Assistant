#pragma once

#include <OpenXLSX.hpp>
#include <fstream>
#include <string>
#include <vector>


// Column names in the spreadsheet.
struct Columns
{
	const std::string latitude = "A";
	const std::string longitude = "B";
	const std::string date = "C";
	const std::string incidentNumber = "D";
	const std::string incidentType = "E";
};

// Each column of data we're interested in.
struct CrimeData
{
	std::string latitude;
	std::string longitude;
	std::string date;
	std::string incidentNumber;
	std::string incidentType;
	std::string category;
};

class Parser
{
public:
	Parser();
	void generateCSV();
	void parseSheets();
	~Parser();

private:
	Columns column;
	std::vector<CrimeData> m_assembledData;
	const std::string m_pathToCSV;
	const std::string m_pathToSpreadsheet;
	int m_populatedRows;
	const std::vector<std::string> m_sheetNames;
	const int m_startingRow;
	std::vector<OpenXLSX::XLWorksheet> m_worksheets;

	void getWorksheets(const OpenXLSX::XLDocument& spreadsheet);
	void setPopulatedRows(const OpenXLSX::XLWorksheet& sheet);
};
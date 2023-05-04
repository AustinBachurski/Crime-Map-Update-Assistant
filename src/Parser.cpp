#include "Parser.hpp"

Parser::Parser() :
	m_assembledData{},
	m_pathToCSV{ "../Data/Crimecurrent.csv" },
	m_pathToSpreadsheet{ "../Data/DSS Data.xlsx" },
	m_populatedRows{},
	m_sheetNames{
		"Animal Incidents", // Putting "Animal Incidents" at the top so they're easier to review.
		"Crimes Against Persons",
		"Crimes Against Property",
		"Crimes Against Society",
		"Other Calls for Service",
		"Traffic Incidents",
		"Miscellaneous Investigations"
	},
	m_startingRow{ 7 }, // Row 7 is where the actual data begins.
	m_worksheets{}
{}

void Parser::generateCSV()
{
	std::fstream csv;
	csv.open(m_pathToCSV, std::ios::out | std::ios::trunc); // Open File for Writing | Discard Existing Data
	if (csv.is_open())
	{
		csv << "Lat," << "Lon," << "Date," << "Incident_N," << "Incident_T," << "Category" << '\n';
		for (const CrimeData& data : m_assembledData)
		{
			csv << data.latitude << ", "
				<< data.longitude << ", "
				<< data.date << ", "
				<< data.incidentNumber << ", "
				<< data.incidentType << ", "
				<< data.category << '\n';
		}
	}
	csv.close();
}

void Parser::setPopulatedRows(const OpenXLSX::XLWorksheet& sheet)
{
	m_populatedRows = 0; // Zero populated rows count before processing the sheet.

	OpenXLSX::XLCellRange range = sheet.range(	// Entire range of column 'A'.
		OpenXLSX::XLCellReference(column.latitude + std::to_string(m_startingRow)),
		OpenXLSX::XLCellReference(OpenXLSX::MAX_ROWS, column.latitude));

	for (const auto& cell : range)
	{
		if (cell.value().type() == OpenXLSX::XLValueType::Empty)
		{
			break;
		}
		++m_populatedRows;
	}
}

void Parser::getWorksheets(const OpenXLSX::XLDocument& spreadsheet)
{
	for (const std::string& sheetName : m_sheetNames)
	{
		std::cout << spreadsheet.workbook().worksheet(sheetName).name() << '\n';

		m_worksheets.push_back(spreadsheet.workbook().worksheet(sheetName));
	}
}

void Parser::parseSheets()
{
	OpenXLSX::XLDocument spreadsheet(m_pathToSpreadsheet);

	if (spreadsheet.isOpen())
	{
		getWorksheets(spreadsheet);

		for (const OpenXLSX::XLWorksheet& currentSheet : m_worksheets)
		{
			setPopulatedRows(currentSheet);

			if (m_populatedRows)
			{
				for (int currentRow = m_startingRow; currentRow < m_populatedRows + m_startingRow; ++currentRow)
				{
					m_assembledData.push_back(CrimeData
						{
						currentSheet.cell(column.latitude + std::to_string(currentRow)).value().get<std::string>(),
						currentSheet.cell(column.longitude + std::to_string(currentRow)).value().get<std::string>(),
						currentSheet.cell(column.date + std::to_string(currentRow)).value().get<std::string>(),
						currentSheet.cell(column.incidentNumber + std::to_string(currentRow)).value().get<std::string>(),
						currentSheet.cell(column.incidentType + std::to_string(currentRow)).value().get<std::string>(),
						currentSheet.name()
						});
				}
			}
		}
	}
}

Parser::~Parser()
{}
#pragma once
#include "ViewAutomates.h"

using MinimizateTable = std::map<std::string, std::map<std::string, std::vector<std::string>>>;

class CMinimizate
{
public:
	CMinimizate(table const & mealy);
	table GetMinimizateMeale() const;
private:
	void FirstFillTable();
	void FillTable();
	bool IsEquale() const;
	bool IsEqualeTable() const;
	void Output(MinimizateTable const & table);
private:
	table m_mealy;
	MinimizateTable m_predTable;
	MinimizateTable m_currentTable;
};


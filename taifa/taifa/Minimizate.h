#pragma once
#include "ViewAutomates.h"

using MinimizateTable = std::map<std::string, std::map<std::string, std::vector<std::string>>>;

class CMinimizate
{
public:
	CMinimizate() = default;
	CMinimizate(CViewAutomates const & mealy);
	CViewAutomates GetMinimizedMachine() const;
private:
	void FirstFillingTable(); 
	void FillingTable();
	void CompilingEmptyTable();
	bool IsEqualeTable() const; 
private:
	table m_mealy;
	MinimizateTable m_predTable;
	MinimizateTable m_currentTable;
};


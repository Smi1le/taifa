#pragma once
#include "stdafx.h"



struct SElementMatrix
{
	SElementMatrix(std::string const &o, std::string const &t)
		: output(o)
		, to(t)
	{
		
	}
	std::string output;
	std::string to;
};

using table = std::map<std::string, std::map<std::string, SElementMatrix>>;//Первая строка - имя вершины откуда идет, вторая строка - по какому символу

class CViewAutomates
{
public:
	CViewAutomates() = default;
	void addState(SSymbols const &elementMatrix);
	table GetMachine() const;
private:
	table m_meale;
	bool m_notDetermined = false;
};
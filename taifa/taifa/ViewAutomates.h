#pragma once
#include "stdafx.h"



struct SElementMatrix
{
	SElementMatrix(std::string const &o, std::string const &t)
		: output(o)
		, to(t)
	{}
	
	std::string output;
	std::string to;
};

struct compareElement
{
	bool operator()(SElementMatrix const &a, SElementMatrix const &b)
	{
		return (a.output < b.output && a.to < b.to);
	}
};

//Первая строка - имя вершины откуда идет, вторая строка - по какому символу
using table = std::map<std::string, std::map<std::string, std::multiset<SElementMatrix, compareElement>>>;

class CViewAutomates
{
public:
	CViewAutomates() = default;
	void addState(SSymbols const &elementMatrix);
	table GetMachine() const;
	bool isMealy = true;
private:
	table m_meale;
	bool m_notDetermined = false;
};


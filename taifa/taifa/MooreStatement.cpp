#include "stdafx.h"
#include "MooreStatement.h"


using namespace std;

/*void CMooreStatement::AddState(SSymbols const &elementTable)
{
	SMooreElement element = {elementTable.output, elementTable.from };

	auto posElementInTable = Find(element);
	if (posElementInTable == m_moore.size())
	{
		map<string, string> needingElement = { {elementTable.input, elementTable.to} };
		m_moore.insert({element, needingElement});
	}
	else
	{

		auto column = At(element);
		auto cell = column.second.find(elementTable.to);
		if (cell == column.second.end())
		{
			m_moore.at(element).insert({ elementTable.input, elementTable.to });
		}
		else
		{
			m_notDetermined = true;
		}
	}
	
}*/

/*mooreTable CMooreStatement::GetMachine() const
{
	return m_moore;
}

bool operator <(SMooreElement const &f, SMooreElement const &s)
{
	return f.from == s.from;
}

size_t CMooreStatement::Find(SMooreElement const &cell) const
{
	size_t number = 0;
	for (auto element = m_moore.begin(); element != m_moore.end(); ++element)
	{
		if (cell.from == (*element).first.from)
		{
			return number;
		}
		++number;
	}
	return m_moore.size();
}*/

/*std::pair<SMooreElement, std::map<std::string, std::string>>& CMooreStatement::At(SMooreElement const &val)
{
	for (auto element = m_moore.begin(); element != m_moore.end(); ++element)
	{
		if (val.from == (*element).first.from)
		{
			return &*element;
		}
	}
	return{};
}

std::pair<SMooreElement, std::map<std::string, std::string>> &operator[](CMooreStatement &f, size_t const &s)
{
	size_t count = 0;
	for (auto &elem : m_moore)
	{

	}
}*/
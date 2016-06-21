#include "stdafx.h"
#include "Minimizate.h"



using namespace std;

void Output(MinimizateTable const & table)
{
	for (auto const & it : table)
	{
		cout << "Group " << it.first << " : " << endl;
		for (auto const & vertex : it.second)
		{
			cout << "vertex " << vertex.first << endl;
			for (auto const & group : vertex.second)
			{
				cout << "\t : " << group << endl;
			}
		}
		cout << "////////////////" << endl;
	}

}

CMinimizate::CMinimizate(CViewAutomates const & mealy)
	: m_mealy(mealy.GetMachine())
{
	FirstFillingTable();
	while (!IsEqualeTable())
	{	
		m_predTable = m_currentTable;
		CompilingEmptyTable();
	}	
}

CViewAutomates CMinimizate::GetMinimizedMachine() const
{
	
	CViewAutomates automate;
	for (auto const & it : m_currentTable)
	{
		auto from = it.first;
		automate.addState({ "", from, "", "" });
		auto iterMap = it.second.begin();
		if (it.second.size() > 1)
		{
			++iterMap;
		}
		auto vertex = iterMap->first;
		auto states = iterMap->second;
		auto st = m_mealy.find(vertex);
		size_t count = 0;
		cout << states.size() << " " << st->second.size() << endl;
		auto iter = ++st->second.begin();
		for (iter; iter != st->second.end(); ++iter)
		{

			auto to = states[count];
			auto output = (*iter->second.begin()).output;
			auto input = iter->first;
			automate.addState({ to, from, input, output });
			++count;
		}
	}
	return automate;
}

void CMinimizate::FirstFillingTable()
{
	// Разделяю вершины по группам
	map<string, vector<string>> groups;
	for (auto &vertex : m_mealy)
	{
		string signal;
		for (auto const &state : vertex.second)
		{
			signal += (*state.second.begin()).output;
		}
		groups[signal].push_back(vertex.first);
		int count = 1;
		for (auto it : groups)
		{
			if (it.first == signal)
			{
				break;
			}
			++count;
		}
		/*for (auto &state : vertex.second)
		{
			
			auto *kp = &state.second.begin();
			(*kp)->output = to_string(count);
			kp->output = to_string(count);
		}*/
	}
	
	// Заполняю таблицу по группам, которые содержат вершины с пустыми значениями
	size_t count = 1;
	for (auto const &id : groups)
	{
		string name = to_string(count);
		for (auto const & vertex : id.second)
		{
			m_currentTable[name].insert(pair<string, vector<string>>(vertex, {}));
		}
		++count;
	}

	FillingTable();
}

void CMinimizate::FillingTable()
{
	// Заполняет таблицу символами групп
	for (auto &it : m_currentTable)
	{
		for (auto &vertex : it.second)
		{
			auto state = m_mealy.find(vertex.first);
			auto iter = ++state->second.begin();
			for (iter; iter != state->second.end(); ++iter)
			{
				auto to = (*iter->second.begin()).to;
				for (auto l : m_currentTable)
				{
					auto iterat = l.second.find(to);
					if (iterat != l.second.end())
					{
						vertex.second.push_back(l.first);
						break;
					}
				}
			}
		}
	}
}

void CMinimizate::CompilingEmptyTable()
{
	// Разделяю вершины по группам
	map<string, vector<string>> groups;
	for (auto const & vertex : m_currentTable)
	{
		for (auto const & l : vertex.second) // map<string, vector<group>>
		{
			string signal;
			for (auto const & group : l.second)
			{
				signal += group;
			}
			groups[signal].push_back(l.first);
		}
	}
	m_currentTable.clear();
	// Заполняю таблицу по группам, которые содержат вершины с пустыми значениями
	size_t count = 1;
	for (auto const &id : groups)
	{
		string name = "D" + to_string(count);
		for (auto const & vertex : id.second)
		{
			m_currentTable[name].insert(pair<string, vector<string>>(vertex, {}));
		}
		++count;
	}

	FillingTable();
}

bool CMinimizate::IsEqualeTable() const
{
	return m_predTable.size() == m_currentTable.size();
}
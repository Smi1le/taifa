#include "stdafx.h"
#include "Minimizate.h"



using namespace std;


CMinimizate::CMinimizate(table const & mealy)
	: m_mealy(mealy)
{
	FirstFillTable();

	/*while (!IsEqualeTable())
	{
		FillTable();
	}*/
}

table CMinimizate::GetMinimizateMeale() const
{
	return table();
}

void CMinimizate::FirstFillTable()
{
	// Разделяю вершины по группам
	map<string, vector<string>> groups;
	for (auto vertex : m_mealy)
	{
		string signal;
		for (auto state : vertex.second)
		{
			signal += state.second.output;
		}
		groups[signal].push_back(vertex.first);
	}
	// m_currentTable["sa"].emplace(pair<string, vector<string>>());
	
	// Заполняю таблицу по группам, которые содержат вершины с пустыми значениями
	size_t count = 1;
	for (auto id : groups)
	{
		string name = "A" + to_string(count);
		for (auto vertex : id.second)
		{
			m_currentTable[name].insert(pair<string, vector<string>>(vertex, {}));
		}
		++count;
	}

	// Заполняет таблицу символами групп
	for (auto &it : m_currentTable) 
	{
		for (auto &vertex : it.second)
		{
			auto state = m_mealy.find(vertex.first);
			auto iter = state->second.begin();
			++iter;
			for (iter; iter != state->second.end(); ++iter)
			{
				auto to = iter->second.to;
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

void CMinimizate::FillTable()
{
}

bool CMinimizate::IsEquale() const
{
	return false;
}

bool CMinimizate::IsEqualeTable() const
{
	return m_predTable == m_currentTable;
}

void CMinimizate::Output(MinimizateTable const & table)
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

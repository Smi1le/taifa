#include "DeterminateAutomates.h"
#include <iostream>

CDetermAutomates::CDetermAutomates(SNotDeterState & notDeterData)
{
	for (auto &it : notDeterData.m_stateData)
	{
		fromSet.clear();
		fromSet.insert(it.second->m_name);
		localMap.clear();
		//
		for (auto &kj : it.second->to)
		{
			localMap.emplace(kj.first, kj.second);//kj.first - им€ вершины куда идет переход, kj.second - символ по которому переход€ты
		}
		//в fromSet хранитс€ им€ изла, а в localMap хран€тс€ все переходы из данного узла в другие 
		//по определенным символам, даже если переходов по одному символу несколько
		localSet.emplace(fromSet, localMap);
	}
	while (Recursion())
	{}
	for (auto const &ut : determVector)
	{
		if (ut.to.size() != 0)
		{
			m_deterAuto.addState(ut);
		}
	}
}


/*

—оздает таблицу переходов вида
|x0|x1
__|__|__
S0|S1|S2 
__|__|__
S1|S2|S6
__|__|__
S2|S4|S5
__|__|__
S6|--|S8
__|__|__
S4|S9|S0
и т.д.

*/
bool CDetermAutomates::Recursion()
{
	bool result = false;
	for (auto it = localSet.begin(); it != localSet.end(); ++it)
	{
		std::string name = "";
		//—оздаетс€ им€ вершины с помощью конкатенации имен вершин, которые создают эту вершину
		for (auto &nam : it->first)
		{
			name += nam;
		}
		//—оздаетс€ детерминированный узел
		SStateDeterm determ(name);
		
		for (auto &asd : it->second)
		{
			name = "";
			//—оздает им€ отдельного узла , т.е. имена всех вершин, в которые есть переходы из данной вершины по одному символу
			for (auto &names : asd.second)
			{
				name += names;
			}
			determ.SetPath(name, asd.first);
			if (localSet.find(asd.second) == localSet.end())
			{
				result = true;
				toSet.clear();
				localMap.clear();
				for (auto yui : asd.second)
				{
					toSet.clear();
					toSet.insert(yui);

					for (auto &lastsa : localSet.at(toSet))
					{
						if (localMap.find(lastsa.first) == localMap.end())
						{
							localMap.emplace(lastsa.first, lastsa.second);
						}
						else
						{
							for (auto &uh : lastsa.second)
							{
								localMap.at(lastsa.first).insert(uh);
							}
						}
					}
				}
				localSet.emplace(asd.second, localMap);
			}
		}
		determVector.push_back(determ);
	}
	return result;
}

SDeterStatesment CDetermAutomates::GetDeterAutomates() const
{
	return m_deterAuto;
}

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
			localMap.emplace(kj.first, kj.second);//kj.first - ��� ������� ���� ���� �������, kj.second - ������ �� �������� ����������
		}
		//� fromSet �������� ��� ����, � � localMap �������� ��� �������� �� ������� ���� � ������ 
		//�� ������������ ��������, ���� ���� ��������� �� ������ ������� ���������
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

������� ������� ��������� ����
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
� �.�.

*/
bool CDetermAutomates::Recursion()
{
	bool result = false;
	for (auto it = localSet.begin(); it != localSet.end(); ++it)
	{
		std::string name = "";
		//��������� ��� ������� � ������� ������������ ���� ������, ������� ������� ��� �������
		for (auto &nam : it->first)
		{
			name += nam;
		}
		//��������� ����������������� ����
		SStateDeterm determ(name);
		
		for (auto &asd : it->second)
		{
			name = "";
			//������� ��� ���������� ���� , �.�. ����� ���� ������, � ������� ���� �������� �� ������ ������� �� ������ �������
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

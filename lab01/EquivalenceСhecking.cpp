#include "EquivalenceÑhecking.h"

bool SEquivalenceÑhecking::MoorEquivalence(CMooraStatesment & first, CMooraStatesment & second)
{
	for (auto const &firstElement : first.m_stateData)
	{
		if (second.m_stateData.find(firstElement.first) != second.m_stateData.end())
		{
			if (second.m_stateData.at(firstElement.first)->m_output != firstElement.second->m_output)
			{
				return false;
			}
			for (auto const &secondElement : firstElement.second->to)
			{
				if (second.m_stateData.at(firstElement.first)->to.find(secondElement.first) == second.m_stateData.at(firstElement.first)->to.end())
				{
					return false;
				}
				else
				{
					if (first.m_stateData.at(firstElement.first)->to.at(secondElement.first) != secondElement.second)
					{
						return false;
					}
				}
			}
		}
		else
		{
			return false;
		}
	}

	for (auto &firstElement : second.m_stateData)
	{
		if (first.m_stateData.find(firstElement.first) != first.m_stateData.end())
		{
			if (first.m_stateData.at(firstElement.first)->m_output != firstElement.second->m_output)
			{
				return false;
			}
			for (auto &secondElement : firstElement.second->to)
			{
				if (first.m_stateData.at(firstElement.first)->to.find(secondElement.first) == first.m_stateData.at(firstElement.first)->to.end())
				{
					return false;
				}
				else
				{
					if (first.m_stateData.at(firstElement.first)->to.at(secondElement.first) != secondElement.second)
					{
						return false;
					}
				}
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool SEquivalenceÑhecking::MelleeEquivalence(SMelleeStatesment & firstStatement, SMelleeStatesment & secondStatement)
{
	for (auto &it : firstStatement.m_stateData)
	{
		if (secondStatement.m_stateData.find(it.first) != secondStatement.m_stateData.end())
		{
			for (auto &jd : it.second->to)
			{
				if ((secondStatement.m_stateData.at(it.first)->to.find(jd.first) == secondStatement.m_stateData.at(it.first)->to.end()) ||
					(firstStatement.m_stateData.at(it.first)->to.at(jd.first).first != jd.second.first) ||
					(firstStatement.m_stateData.at(it.first)->to.at(jd.first).second != jd.second.second))
				{
					return false;
				}
				/*else
				{
					if (firstStatement.m_stateData.at(it.first)->to.at(jd.first).first != jd.second.first)
					{
						return false;
					}
					if (firstStatement.m_stateData.at(it.first)->to.at(jd.first).second != jd.second.second)
					{
						return false;
					}
				}*/
			}
		}
		else
		{
			return false;
		}
	}

	for (auto &it : secondStatement.m_stateData)
	{
		if (firstStatement.m_stateData.find(it.first) != firstStatement.m_stateData.end())
		{
			for (auto &jd : it.second->to)
			{
				if ((firstStatement.m_stateData.at(it.first)->to.find(jd.first) == firstStatement.m_stateData.at(it.first)->to.end()) ||
					(firstStatement.m_stateData.at(it.first)->to.at(jd.first).first != jd.second.first) ||
					(firstStatement.m_stateData.at(it.first)->to.at(jd.first).second != jd.second.second))
				{
					return false;
				}
				/*else
				{
					if 
					{
						return false;
					}
					if ()
					{
						return false;
					}
				}*/
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

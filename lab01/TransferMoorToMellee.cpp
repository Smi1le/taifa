#include "TransferMoorToMellee.h"

// В автомате Мура все выходные состояния относятся к вершинам, а не переходам, так что при переводе 
// просто эти все состояния приписываются переходам, убирая их с вершины
CTransferMoorToMellee::CTransferMoorToMellee(CMooraStatesment & moorData)
{
	for (auto &it : moorData.m_stateData)
	{
		SStateMelee mellee(it.second->m_name);
		for (auto &jd : it.second->to)
		{
			mellee.SetPath(jd.first, jd.second, moorData.m_stateData.at(jd.second)->m_output);
		}
		vectorStates.push_back(mellee);
	}
	for (auto &sa : vectorStates)
	{
		m_resultMellee.addState(sa);
	}
}

SMelleeStatesment CTransferMoorToMellee::GetMelleeState() const
{
	return m_resultMellee;
}

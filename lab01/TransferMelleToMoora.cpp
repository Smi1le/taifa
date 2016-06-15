#include "TransferMelleToMoora.h"


//Выбираются из автомата Meale все уникальные состояния, не повторяющиеся
//потом создается новая таблица переходов по данным переходам(x1, x2)
// и заполняется, выходные символы проставляются в соответствии с теми, что были у 
//тех уникальных состояний в автомате Meale
CTransferMelleToMoora::CTransferMelleToMoora(SMelleeStatesment &melleeData)
{
	for (auto &it : melleeData.m_stateData)
	{
		for (auto & kj : it.second->to)
		{
			if (unicalState.find(kj.second) == unicalState.end())
			{
				std::string nameNode = "b" + std::to_string(unicalState.size());
				unicalState.emplace(kj.second, nameNode);
				unicalId.emplace(nameNode, kj.second);
			}
		}
	}
	for (auto &ids : unicalId)
	{
		SStateMoora moora(ids.first, ids.second.second);
		
		for (auto &res : melleeData.m_stateData.at(ids.second.first)->to)
		{
			moora.SetPath(res.first, unicalState.at(res.second));
		}
		vectorStates.push_back(moora);
	}
	for (auto &as : vectorStates)
	{
		m_resultMoora.AddState(as);
	}
}

CMooraStatesment CTransferMelleToMoora::GetMooraState() const
{
	return m_resultMoora;
}

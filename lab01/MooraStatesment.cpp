#include "MooraStatesment.h"


bool CMooraStatesment::AddState(const SStateMoora & stateNode)
{
	std::string nameNode = stateNode.m_name;
	if (m_stateData.find(nameNode) != m_stateData.end())
	{
		for (auto &it : stateNode.to)
		{
			m_stateData.at(nameNode)->to.emplace(it.first, it.second);
		}
	}
	else
	{
		m_stateData.emplace(nameNode, std::make_shared<SStateMoora>(stateNode));
	}
	return false;
}


std::shared_ptr<SStateMoora> CMooraStatesment::operator[](const std::string & id)
{
	return m_stateData.at(id);
}

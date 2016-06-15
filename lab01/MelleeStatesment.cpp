#include "MelleeStatesment.h"



std::shared_ptr<SStateMelee> SMelleeStatesment::addState(const SStateMelee & stateNode)
{
	std::string nameNode = stateNode.name;
	if (m_stateData.find(nameNode) != m_stateData.end())
	{
		for (auto &it : stateNode.to)
		{
			m_stateData.at(nameNode)->to.emplace(it.first, it.second);
		}
		return m_stateData.at(nameNode);
	}
	m_stateData.emplace(nameNode, std::make_shared<SStateMelee>(stateNode));
	return m_stateData.at(nameNode);
}

std::shared_ptr<SStateMelee> SMelleeStatesment::operator[](const std::string & id)
{
	return m_stateData.at(id);
}

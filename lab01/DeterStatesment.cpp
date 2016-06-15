#include "DeterStatesment.h"

std::shared_ptr<SStateDeterm> SDeterStatesment::addState(const SStateDeterm & stateNode)
{
	std::string nameNode = stateNode.m_name;
	if (m_stateData.find(nameNode) != m_stateData.end())
	{
		for (auto &it : stateNode.to)
		{
			m_stateData.at(nameNode)->to.emplace(it.first, it.second);
		}
		return m_stateData.at(nameNode);
	}
	m_stateData.emplace(nameNode, std::make_shared<SStateDeterm>(stateNode));
	return m_stateData.at(nameNode);
}

std::shared_ptr<SStateDeterm> SDeterStatesment::operator[](const std::string & id)
{
	return m_stateData.at(id);
}
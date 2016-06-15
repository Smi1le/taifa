#pragma once
#include "StateMelee.h"

struct SMelleeStatesment
{
	std::shared_ptr<SStateMelee> addState(const SStateMelee & stateNode);
	std::map<std::string, std::shared_ptr<SStateMelee>> m_stateData;
	std::string id;
	std::shared_ptr<SStateMelee> operator[](const std::string & id);
};

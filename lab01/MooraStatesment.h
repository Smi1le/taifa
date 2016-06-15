#pragma once
#include "stdafx.h"
#include "StateMoora.h"



struct CMooraStatesment
{
	bool AddState(const SStateMoora & stateNode);
	std::shared_ptr<SStateMoora> operator[](const std::string & id);

	std::map<std::string, std::shared_ptr<SStateMoora>> m_stateData;
	std::string id;
};


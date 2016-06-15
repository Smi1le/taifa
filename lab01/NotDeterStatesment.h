#pragma once
#include "StateNotDeterm.h"

struct SNotDeterState
{
	std::shared_ptr<SStateNotDetermine> AddState(const SStateNotDetermine & stateNode);
	std::map<std::string, std::shared_ptr<SStateNotDetermine>> m_stateData;
	std::string id;
	std::shared_ptr<SStateNotDetermine> operator[](const std::string & id);
};


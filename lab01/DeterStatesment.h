#pragma once
#include "stdafx.h"
#include "StateDeterm.h"

struct SDeterStatesment
{
	std::shared_ptr<SStateDeterm> addState(const SStateDeterm & stateNode);
	std::map<std::string, std::shared_ptr<SStateDeterm>> m_stateData;
	std::string id;
	std::shared_ptr<SStateDeterm> operator[](const std::string & id);
};


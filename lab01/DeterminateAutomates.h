#pragma once
#include "stdafx.h"
#include "NotDeterStatesment.h"
#include "DeterStatesment.h"


class CDetermAutomates
{
public:
	CDetermAutomates(SNotDeterState & notDeterData);
	SDeterStatesment GetDeterAutomates() const;
private:
	bool Recursion();
	SDeterStatesment m_deterAuto;
	std::map<std::set<std::string>, std::map<std::string, std::set<std::string>>> localSet;
	std::vector<SStateDeterm> determVector;
	std::set<std::string> fromSet;
	std::set<std::string> toSet;
	std::map<std::string, std::set<std::string>> localMap;
};


#pragma once
#include "stdafx.h"

struct SStateNotDetermine
{
	SStateNotDetermine(const std::string & name);
	void SetPath(std::string nameTo, std::string inpState); // std::map<куда, входной символ>
	std::string m_name = "";
	std::map<std::string, std::set<std::string>> to; // std::map<входной символ, куда>
};


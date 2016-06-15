#pragma once
#include "stdafx.h"

struct SStateDeterm
{
	SStateDeterm(const std::string & name);
	void SetPath(std::string nameTo, std::string inpState); // std::map<куда, входной символ>
	std::string m_name = "";
	std::vector<std::string> NamesNode;
	std::map<std::string, std::string> to; // std::map<входной символ, куда>
};


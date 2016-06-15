#include "StateNotDeterm.h"

SStateNotDetermine::SStateNotDetermine(const std::string & name)
	: m_name(name)
{
}

void SStateNotDetermine::SetPath(std::string inpState, std::string toName)
{
	if (to.find(inpState) != to.end())
	{
		to.at(inpState).insert(toName);
	}
	else
	{
		std::set<std::string> as = {toName};
		to.emplace(inpState, as);

	}
	
}

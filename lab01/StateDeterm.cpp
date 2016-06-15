#include "StateDeterm.h"


SStateDeterm::SStateDeterm(const std::string & name)
	: m_name(name)
{
}

void SStateDeterm::SetPath(std::string toName, std::string inpState)
{
	to.emplace(toName, inpState);
}
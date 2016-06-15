#include "StateMelee.h"

SStateMelee::SStateMelee(const std::string & name)
	: name(name)
{
}

void SStateMelee::SetPath(std::string inpSym, std::string toName, std::string out)
{
	if (to.find(inpSym) != to.end())
	{
		toNoDeterm[inpSym].insert(toName);
		noDeterm = true;
	}
	else
	{
		to.emplace(inpSym, std::make_pair(toName, out));
		toNoDeterm.emplace(inpSym, std::set<std::string>({ toName }));
	}
}


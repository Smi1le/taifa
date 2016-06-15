#include "StateMoora.h"



SStateMoora::SStateMoora(const std::string & name, const std::string & output)
	: m_name(name)
	, m_output(output)
{
}

void SStateMoora::SetPath(std::string toName, std::string out)
{
	//inp toName
	to.emplace(toName, out);
}
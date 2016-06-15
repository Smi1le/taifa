#pragma once
#include "MelleeStatesment.h"
#include "MooraStatesment.h"
//#include <vector>

class CTransferMoorToMellee
{
public:
	CTransferMoorToMellee(CMooraStatesment & moorData);
	SMelleeStatesment GetMelleeState() const;
private:
	SMelleeStatesment m_resultMellee;
	std::vector<SStateMelee> vectorStates;
};


#pragma once
#include "stdafx.h"

#include "MelleeStatesment.h"
#include "MooraStatesment.h"


class CTransferMelleToMoora
{
public:
	CTransferMelleToMoora(SMelleeStatesment &melleeData);
	CMooraStatesment GetMooraState() const;
private:
	std::map<std::pair<std::string, std::string>, std::string> unicalState;
	std::map<std::string, std::pair<std::string, std::string>> unicalId;
	CMooraStatesment m_resultMoora;
	std::vector<SStateMoora> vectorStates;
};


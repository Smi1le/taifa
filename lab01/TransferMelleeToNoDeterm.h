#pragma once
#include "stdafx.h"

#include "NotDeterStatesment.h"
#include "MelleeStatesment.h"


struct STransferMelleeToNoDeterm
{
	STransferMelleeToNoDeterm(SMelleeStatesment &notDeterData);
	SNotDeterState m_deterData;
	std::vector<SStateNotDetermine> vectorNodes;
};
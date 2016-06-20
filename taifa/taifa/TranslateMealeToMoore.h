#pragma once
#include "ViewAutomates.h"

struct STranslateMealeToMoore
{
	static CViewAutomates Translate(CViewAutomates const &meale);
};

bool operator==(SSymbols const &rVal, SSymbols const &lVal);
bool operator!=(SSymbols const &rVal, SSymbols const &lVal);
bool operator==(SSymbols const &rVal, SElementMatrix const &lVal);
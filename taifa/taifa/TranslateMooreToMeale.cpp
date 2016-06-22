#include "stdafx.h"
#include "TranslateMooreToMeale.h"

CViewAutomates STranslateMooreToMeale::Translate(CViewAutomates const &moore)
{
	CViewAutomates meale;
	for (auto const & columnTable : moore.GetMachine())
	{
		std::string from = columnTable.first;
		meale.addState({ from, "", "", "" });
		int count = 0;
		for (auto const &cellMatrix : columnTable.second)
		{
			if (count > 0)
			{
				auto ccc = (*cellMatrix.second.begin());
				SSymbols symbols = SSymbols((*cellMatrix.second.begin()).to, from, cellMatrix.first, (*(*columnTable.second.begin()).second.begin()).output);
				meale.addState(symbols);
			}
			++count;
		}
	}
	meale.isMeale = true;
	return meale;
}
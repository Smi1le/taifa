#include "stdafx.h"
#include "ViewAutomates.h"


using namespace std;

void CViewAutomates::addState(SSymbols const &elementMatrix)
{
	auto vertexFrom = elementMatrix.from;
	auto symbolInput = elementMatrix.input;
	auto posVertexFrom = m_meale.find(vertexFrom);
	if (posVertexFrom == m_meale.end())
	{
		map<string, SElementMatrix> element = {{symbolInput, SElementMatrix(elementMatrix.output, elementMatrix.to)}};
		m_meale.insert({ vertexFrom,  element });
	}
	else
	{
		auto vertex = m_meale.at(vertexFrom);
		auto posSymbolInput = vertex.find(symbolInput);
		if (posSymbolInput == vertex.end())
		{
			m_meale.at(vertexFrom).insert({ symbolInput, SElementMatrix(elementMatrix.output, elementMatrix.to) });
		}
		else
		{
			m_notDetermined = true;
		}
	}
}

table CViewAutomates::GetMachine() const
{
	return m_meale;
}



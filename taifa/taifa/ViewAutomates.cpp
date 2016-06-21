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
		multiset<SElementMatrix, compareElement> many;
		auto elem = SElementMatrix(elementMatrix.output, elementMatrix.to);
		many.insert(elem);
		map<string, multiset<SElementMatrix, compareElement>> element = {{symbolInput, many }};
		m_meale.insert({ vertexFrom,  element });
	}
	else
	{
		auto vertex = m_meale.at(vertexFrom);
		auto posSymbolInput = vertex.find(symbolInput);
		if (posSymbolInput == vertex.end())
		{
			multiset<SElementMatrix, compareElement> many;
			many.insert(SElementMatrix(elementMatrix.output, elementMatrix.to));
			m_meale.at(vertexFrom).insert({ symbolInput, many });
		}
		else
		{
			multiset<SElementMatrix, compareElement> many;
			for (auto const &it2 : m_meale.at(vertexFrom).at(symbolInput))
			{
				many.insert(it2);
			}
			auto elem = SElementMatrix(elementMatrix.output, elementMatrix.to);
			many.insert(elem);
			//m_meale.at(vertexFrom).at(symbolInput).insert(elem);
			m_meale.at(vertexFrom).at(symbolInput).insert(elem);
			m_notDetermined = true;
		}
	}
}

table CViewAutomates::GetMachine() const
{
	return m_meale;
}


#include "stdafx.h"
#include "TranslateMealeToMoore.h"

bool Find(std::vector<SSymbols> const &newStates, SSymbols const &el)
{
	for (auto const &ss : newStates)
	{
		if (ss == el)
		{
			return true;
		}
	}
	return false;
}

CViewAutomates STranslateMealeToMoore::Translate(CViewAutomates const &meale)
{
	std::vector<SSymbols> newStates;

	//Находим уникальные ячейки и даем им новые имена
	for (auto const &tableColumn : meale.GetMachine())
	{
		int count = 0;
		for (auto const &cell : tableColumn.second)
		{
			if (count != tableColumn.second.size() && count > 0)
			{
				SSymbols autonomCell = SSymbols((*cell.second.begin()).to, tableColumn.first, cell.first, (*cell.second.begin()).output);
				if (newStates.empty())
				{
					newStates.push_back(autonomCell);
				}
				else
				{
					if (!Find(newStates, autonomCell))
					{
						newStates.push_back(autonomCell);
					}
				}
			}
			++count;
		}
	}


	CViewAutomates moore;
	size_t number = 0;
	std::vector<std::string> newNames;
	//Создаем автомат Meale, в котором пока что имеются только вершины, из которых идут пути
	for (const auto & uniqueState : newStates)
	{
		std::string newName = "q" + std::to_string(number++);
		newNames.push_back(newName);
		moore.addState(SSymbols("", newName, "", uniqueState.output));
	}

	auto mealeAutomate = meale.GetMachine();
	size_t count = 0;
	//Заполнение таблицы переходами, там показано откуда, куда, по какому входному символу идет путь
	for (auto & elementNewTable : newStates)
	{
		auto column = mealeAutomate.at(elementNewTable.to);
		for (auto state : column)
		{
			auto cell = state.second;
			for (size_t i = 0; i < newStates.size(); ++i)
			{
				if (newStates.at(i) == (*cell.begin()))
				{
					SSymbols element = SSymbols(newNames.at(i), newNames.at(count), state.first, "");
					moore.addState(element);
				}
			}
		}
		++count;
	}
	moore.isMeale = false;
	return moore;
}



bool operator==(SSymbols const &rVal, SElementMatrix const &lVal)
{
	return ((rVal.output == lVal.output) && (rVal.to == lVal.to));
}

bool operator==(SSymbols const &rVal, SSymbols const &lVal)
{
	return ((rVal.output == lVal.output) && (rVal.to == lVal.to));
}

bool operator!=(SSymbols const &rVal, SSymbols const &lVal)
{
	return (!(rVal == lVal));
}
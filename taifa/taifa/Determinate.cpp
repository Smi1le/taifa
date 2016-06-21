#include "stdafx.h"
#include "Determinate.h"


using namespace std;

CViewAutomates SDeterminate::Determinate(CViewAutomates const &automate)
{
	CViewAutomates newAutomate;
	map<string, vector<string>> newNames;
	//Пробегается по основной матрице и создает новые вершины в которые идут пути
	/*for (auto const &tableColumn : automate.GetMachine())
	{
		newAutomate.addState(SSymbols("", tableColumn.first, "", ""));
		for (auto const &tableRow : tableColumn.second)
		{
			string inputSymbol = tableRow.first;
			string newNameVertex = "";
			for (auto const &outputVertexs : tableRow.second)
			{
				newNameVertex.append(outputVertexs.to);
			}
			newAutomate.addState({ newNameVertex, tableColumn.first, inputSymbol, "" });
		}
	}*/
	auto tableAutomate = automate.GetMachine();
	auto firstColumn = (*tableAutomate.begin());
	queue<string> myQueue;
	myQueue.push(firstColumn.first);


	while (!myQueue.empty())
	{
		auto column = tableAutomate.find(myQueue.front());
		auto machine = newAutomate.GetMachine();
		auto check = machine.find(myQueue.front());
		auto nameVertex = myQueue.front();
		myQueue.pop();
		if ((column != tableAutomate.end()) && (check == machine.end()))
		{
			size_t k = 0;
			for (auto const &tableRow : (*column).second)
			{
				if (k > 0)
				{
				
					string inputSymbol = tableRow.first;
					string newNameVertex = "";
					vector<string> vectorNames;
					size_t count = 0;
					for (auto const &outputVertexs : tableRow.second)
					{
						newNameVertex += outputVertexs.to;
						vectorNames.push_back(outputVertexs.to);
						++count;
					}
					/*if (count == 0)
					{
						auto posPlus = (*newNames.find((*column).first));
						size_t numberVertexs = posPlus.second.size();
						for (size_t c = 0; c < numberVertexs; ++c)
						{


							for (auto const &nameVertex : posPlus.second)
							{
								auto pos = tableAutomate.find(nameVertex);
								if (pos != tableAutomate.end())
								{
									auto col = (*pos).second;
									size_t p = 0;
									for (auto const &element : (*pos).second)
									{
										if (p == c)
										{
											for (auto const &outputVertexs : element.second)
											{
												newNameVertex.append(outputVertexs.to);
												vectorNames.push_back(outputVertexs.to);
												//++count;
											}
										}
										++p;

									}
									bool flag = false;
									for (auto const &it : newNames)
									{
										if (it.second == vectorNames)
										{
											flag = true;
										}
									}
									if (!flag)
									{
										newAutomate.addState({ newNameVertex, (*column).first, inputSymbol, "" });
										myQueue.push(newNameVertex);
										newNames.insert({ newNameVertex, vectorNames });
									}
								}
							}
						}
					}*/
					newAutomate.addState({ newNameVertex, (*column).first, inputSymbol, "" });
					myQueue.push(newNameVertex);
					newNames.insert({ newNameVertex, vectorNames });
				}
				++k;
			}
		}
		else if ((column == tableAutomate.end()) && (check == machine.end()))
		{
			auto listVertex = newNames.at(nameVertex);
			if (listVertex.size() > 1)
			{
				for (size_t number = 0; number != listVertex.size(); ++number)
				{

					string nameNewVertex("");
					vector<string> vectorNames;
					for (auto const &element : listVertex)
					{
						auto v = machine.at(element);
						size_t count = 0;
						for (auto const &it : v)
						{
							if (count == number)
							{
								for (auto const &it2 : it.second)
								{
									bool flag = false;
									for (auto it3 : vectorNames)
									{
										if (it2.to == it3)
										{
											flag = true;
										}
									}
									if (!flag)
									{
										//nameNewVertex += it2.to;
										auto tt = newNames.at(it2.to);
										size_t ko = 0;
										for (auto const &ll : tt)
										{
											bool flag2 = false;
											size_t po = 0;
											for (auto kj : vectorNames)
											{
												if (ll == kj)
												{
													flag2 = true;
													break;
												}
												++po;
											}
											if (!flag2)
											{
												nameNewVertex += ll;
												vectorNames.push_back(ll);
											}
											++ko;
										}
										
									}
								}
							}
							++count;
						}
					}

					newAutomate.addState({ nameNewVertex, nameVertex, "x" + std::to_string(number), "" });
					myQueue.push(nameNewVertex);
					newNames.insert({ nameNewVertex, vectorNames });
					//newAutomate.addState({ nameNewVertex, nameVertex, "x" + std::to_string(number), "" });
					//myQueue.push(nameNewVertex);
					//newNames.insert({ nameNewVertex, vectorNames });
				}
			}
		}
	}
	return newAutomate;
}

/*bool operator==(std::vector<std::string> rVal, std::vector<std::string> lVal)
{
	if (rVal.size() != lVal.size())
	{
		return false;
	}
	for (size_t i = 0; i < rVal.size(); ++i)
	{
		for (size_t j = 0; j < lVal.size(); ++j)
		{
			if (rVal[i] == lVal[j])
			{
				rVal.erase(rVal.begin() + i);
				lVal.erase(lVal.begin() + j);
				break;
				i = -1;
			}
		}
	}
	if (rVal.size() == 0)
	{
		return true;
	}
	return false;
}

bool operator!=(std::vector<std::string> rVal, std::vector<std::string> lVal)
{
	return !(rVal == lVal);
}*/
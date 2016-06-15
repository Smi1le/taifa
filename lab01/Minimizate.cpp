#include "Minimizate.h"
using namespace std;

CMinimizate::CMinimizate(map<string, shared_ptr<SStateMelee>> &originalMachine)
	: m_originalMachine(originalMachine)
{
	m_check.resize(m_originalMachine.size());
}


CMinimizate::~CMinimizate()
{
}
//ћинимизирует автомат первый раз, не заполн€€ таблицу названи€ми классов
void CMinimizate::SearchEquivalenceInOriginalMachine(string const &state, string const &name,
	vector<pair<string, string>> const &second )
{
	unsigned i = 0;
	std::string stateOther;
	Word word;
	for (auto const &element : m_originalMachine)
	{
		for (auto const &it : element.second->to)
		{
			stateOther += it.second.second;
		}
		if (state == stateOther && !m_check[i])
		{
			word.emplace(element.first,second);
			m_check[i] = true;
		}
		stateOther = "";
		++i;
	}
	bool wasFalse = false;
	for(auto const &checker :m_check)
	{
		if(!checker)
		{
			wasFalse = true;
		}
	}
	if(!wasFalse)
	{
		m_wasFalse = true;
	}
	if (!word.empty())
	{
		m_parts.push_back(word);
	}
}

//≈сли надо - разбивает на части класс
void CMinimizate::SearchEquivalenceInParts(string const &state)
{
	unsigned i = 0;
	string stateOther;
	Word word;
	for (auto &it : m_parts)
	{
		for (auto &q : it) 
		{
			for (auto &states : q.second)
			{
				stateOther += states.second;
			}
			if (state == stateOther && m_check[i] != true)
			{
				word.emplace(q.first, q.second);
				m_check[i] = true;
			}
			stateOther = "";
			++i;
		}
	}
	bool wasFalse = false;
	for (auto checker : m_check)
	{
		if (!checker)
		{
			wasFalse = true;
		}
	}
	if (!wasFalse)
	{
		m_wasFalse = true;
	}
	if(!word.empty())
	{
		m_partsCopy.push_back(word);
	}
}


/*
ѕолучает на вход автомат Meale


  |  q1 |  q2 |q3
 _|_____|_____|____
x1|q2/y1|q0/y1|q0/y2
__|_____|_____|____
x2|q0/y1|q2/y2|q1/y1
__|_____|_____|____
*/

map<string, shared_ptr<SStateMelee>> CMinimizate::GetMinimizateMachine()
{
	string state;
	for(auto &iter : m_originalMachine)
	{
		//¬ектор входной - выходной символ
		vector<pair<string, string>> second;
		for (auto &it : iter.second->to)
		{
			state += it.second.second;
			second.push_back(std::make_pair(it.first,it.second.second));
		}
		if(!m_wasFalse)
		{
			//ѕровер€ет надо ли вообще минимизировать автомат или же нет
			SearchEquivalenceInOriginalMachine(state, iter.first, second);
		}
		state = "";
	}
	FillTheCell();
	for (auto &classes : m_parts)
	{
		for (auto &states : classes)
		{
			for (auto &ite : states.second)
			{
				state += ite.second;
			}
			if (!m_wasFalse)
			{
				SearchEquivalenceInParts(state);
			}
			state = "";
		}
	}
	while(m_parts.size() != m_partsCopy.size())
	{
		FillTheCell();
		m_partsCopy.clear();
		for (auto &classes : m_parts)
		{
			for (auto &states : classes)
			{
				for (auto &ite : states.second)
				{
					state += ite.second;
				}
				if (!m_wasFalse)
				{
					SearchEquivalenceInParts(state);
				}
				state = "";
			}
		}
	}
	return ConvertedIntoStandardView();
}
//приводит к автомату Meale
map<string, shared_ptr<SStateMelee>> CMinimizate::ConvertedIntoStandardView()
{
	SMelleeStatesment minimizateMachine;
	
	for(auto &classes : m_parts)
	{
		auto firstState = classes.begin();
		SStateMelee node(firstState->first);
		auto x = m_originalMachine.at(firstState->first);
		for (auto &iter : x->to)
		{
			node.SetPath(iter.first, iter.second.first, iter.second.second);
		}
		m_nodes.push_back(node);
	}
	for(auto &it : m_nodes)
	{
		minimizateMachine.addState(it);
	}
	return minimizateMachine.m_stateData;
}
//«аполн€ет таблицу по алгоритму заполнени€ таблицы названи€ми классов
void CMinimizate::FillTheCell()
{
	m_wasFalse = false;
	m_check.clear();
	m_check.resize(m_originalMachine.size());
	//≈сли количество классов в таблице стало больше чем в прошлый раз, то переносим нашу таблицу в прошлую
	if (m_partsCopy.size() > m_parts.size()) 
	{
		std::swap(m_parts, m_partsCopy);
	}
	for (auto &iter : m_parts)
	{
		for (auto &iterWord : iter)
		{
			int j = 1;
			for (auto &it : m_originalMachine.find(iterWord.first)->second->to)
			{
				SeachEqual(it.second.first, j, iterWord.first);
				++j;
			}
		}
	}
}

void CMinimizate::SeachEqual(string qOriginal,int count, string q)
{
	int i = 1;
	int countParts = 1;
	string result;
	for (auto &iter : m_parts)
	{
		if(iter.find(qOriginal)!= iter.end())
		{
			for(auto &iterState : iter.find(qOriginal)->second)
			{
				if(count == i)
				{
					result = std::to_string(countParts);//
					break;
				}		
				++i;
			}
		}
		++countParts;
	}
	i = 1;
	//countParts = 1;
	for(auto &iter : m_parts)
	{
		if (iter.find(q) != iter.end())
		{
			for (auto &iterState : iter.find(q)->second)
			{
				if (count == i)
				{
					iterState.second = result;//
					return;
				}
				++i;
			}
		}
	}
}
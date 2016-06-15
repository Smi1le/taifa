#pragma once
#include "stdafx.h"
#include "MelleeStatesment.h"
#include "StateMelee.h"

using Word = std::map<std::string, std::vector<std::pair<std::string, std::string>>>; //первое имя q, потом пара х1,2,3 и А1,2,3


class CMinimizate
{
public:
	CMinimizate(std::map<std::string, std::shared_ptr<SStateMelee>> &originalMachine);
	~CMinimizate();
	std::map<std::string, std::shared_ptr<SStateMelee>> GetMinimizateMachine();
	std::vector<bool> m_check;
private:
	void SearchEquivalenceInOriginalMachine(std::string const &state, std::string const &name, std::vector<std::pair<std::string, std::string>> const &second);
	std::map<std::string, std::shared_ptr<SStateMelee>> m_originalMachine;
	std::vector<std::vector<std::pair<std::string, std::string>>> m_word;
	void SearchEquivalenceInParts(std::string const &state);
	void SeachEqual(std::string qOriginal, int count, std::string q);
	void FillTheCell();
	std::map<std::string, std::shared_ptr<SStateMelee>> ConvertedIntoStandardView();
private:
	std::vector<Word> m_parts;
	std::vector<Word> m_partsCopy;
	bool m_wasFalse = false;
	std::vector<SStateMelee> m_nodes;
};



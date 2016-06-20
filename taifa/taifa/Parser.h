#pragma once
#include "stdafx.h"
#include "ViewAutomates.h"
#include "TranslateMooreToMeale.h"
#include "TranslateMealeToMoore.h"

using VectorPairs = std::vector<std::pair<std::string, std::string>>;

class CParser
{
public:
	CParser(std::string const &command, std::string const &input, std::string const & output);
private:
	void ParseInputCommand(std::string const &command);
	void ParseInputData(std::string const &input);
	void SaveToJsonFile();
	void TranslateMooreToMeale();
	void TranslateMealeToMoore();
	void OutputMeale() const;
	void OutputMeale(CViewAutomates const &automat) const;
	void OutputMoore(CViewAutomates const &automat) const;
	void OutputMoore() const;
	std::string outputFileName;
	CViewAutomates m_automat;
	//VectorPairs m_commands;
};

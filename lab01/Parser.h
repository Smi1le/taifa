#pragma once
#include "stdafx.h"

#include "MelleeStatesment.h"
#include "MooraStatesment.h"

#include "TransferMoorToMellee.h"
#include "TransferMelleToMoora.h"
#include "Minimizate.h"
#include "DeterminateAutomates.h"
#include "Equivalence—hecking.h"
#include "TransferMelleeToNoDeterm.h"


class CParser
{
public:
	CParser() = delete;
	CParser(const std::string & commandFileName, const std::string & inputFileName, const std::string & outputFileName);
	~CParser() = default;
private:
	void ParseData(const std::string & fileName);
	void ParseCommand(const std::string & fileName);
	void TranslateMilToMur(const std::string & args);
	void TranslateMurToMil(const std::string & args);
	void MinimizeMil(const std::string & args);
	void MinimizeMur(const std::string & args);
	void Determine(const std::string & args);
	void IsEquel(const std::string & arg1, const std::string & arg2);
	void IsEquelToMur(const std::string & arg1, const std::string & arg2);
	void IsEquelToMele(const std::string & arg1, const std::string & arg2);
	void Save();
private:
	std::string m_outputFile;
	std::map < std::string, std::function<void(std::string & args)>> m_commands;
	CMooraStatesment m_moora;
	SMelleeStatesment m_meale;
	std::map < std::string, SMelleeStatesment> m_melleeMachines;
	std::map < std::string, CMooraStatesment> m_mooraMachines;
	std::map < std::string, SDeterStatesment> m_determMachines;
};

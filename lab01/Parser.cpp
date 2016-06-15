#include "Parser.h"

using json = nlohmann::json;

CParser::CParser(const std::string & commandFileName, const std::string & inputFileName, const std::string & outputFileName):
	m_outputFile(outputFileName),
	m_commands({
		{ "translate-mil-to-mur", std::bind(&CParser::TranslateMilToMur, this, std::placeholders::_1) },
		{ "translate-mur-to-mil", std::bind(&CParser::TranslateMurToMil, this, std::placeholders::_1) },
		{ "minimize-mur", std::bind(&CParser::MinimizeMur, this, std::placeholders::_1)},
		{ "minimize-mil", std::bind(&CParser::MinimizeMil, this, std::placeholders::_1) },
		{ "determine", std::bind(&CParser::Determine, this, std::placeholders::_1)}
		//{ "is-equal-to", std::bind(&CParser::MinimizeMur, this, std::placeholders::_1, std::placeholders::_2) },
	})
{
	ParseData(inputFileName);
	ParseCommand(commandFileName);
}

void CParser::ParseData(const std::string & fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::invalid_argument("can not open the file " + fileName);
	}
	auto j = json::parse(file);
	//choose state machine array
	auto stateMachine = j.at("state machine");

	for (auto & machine : stateMachine)
	{
		auto machineId = machine.at("id");
		auto machineType = machine.at("type");
		auto machineStates = machine.at("states");
		auto machineTransitions = machine.at("transitions");
		//parse states array data
		if (machineType == "meale")
		{
			m_melleeMachines[machineId] = {};//add machine into array

			for (const auto & state : machineStates)
			{//add machine states
				m_melleeMachines[machineId].addState({ state.at("id") });
			}

			for (const auto & it : machineTransitions)
			{//Machine transitions
				auto from = it.at("from");
				auto to = it.at("to");
				auto input = it.at("input");
				auto output = it.at("output");

				m_melleeMachines[machineId][from]->SetPath(input, to, output);
			}
		}
		else if (machineType == "moore")
		{
			m_mooraMachines[machineId] = {};//add machine into array

			for (const auto & state : machineStates)
			{
				m_mooraMachines[machineId].AddState({ state.at("id"), state.at("output") });
			}

			for (const auto & it : machineTransitions)
			{
				auto from = it.at("from");
				auto to = it.at("to");
				auto input = it.at("input");

				m_mooraMachines[machineId][from]->SetPath(input, to);
			}
		}
		else
		{
			throw std::invalid_argument("invalid machine type");
		}
	}
}

void CParser::ParseCommand(const std::string & fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::invalid_argument("can not open the file " + fileName);
	}
	auto j = json::parse(file);
	auto commandsArr = j.at("commands");
	for (auto & command : commandsArr)
	{
		std::vector<std::string> args = command.at("arguments");
		for (auto arg : args)
		{
			m_commands.at(command.at("type"))(arg);
		}
	}

	Save();
}

void CParser::TranslateMilToMur(const std::string & arg)
{
	CTransferMelleToMoora machine(m_melleeMachines.at(arg));
	m_melleeMachines.erase(arg);
	m_mooraMachines[arg] = machine.GetMooraState();

}

void CParser::TranslateMurToMil(const std::string & arg)
{
	CTransferMoorToMellee machine(m_mooraMachines.at(arg));
	m_mooraMachines.erase(arg);
	m_melleeMachines[arg] = machine.GetMelleeState();
}

void CParser::MinimizeMil(const std::string & arg)
{
	CMinimizate machine(m_melleeMachines.at(arg).m_stateData);
	SMelleeStatesment buffer;
	buffer.m_stateData = machine.GetMinimizateMachine();
	m_melleeMachines[arg] = buffer;
}

void CParser::MinimizeMur(const std::string & arg)
{
	TranslateMurToMil(arg);
	CMinimizate machine(m_melleeMachines.at(arg).m_stateData);
	SMelleeStatesment buffer;
	buffer.m_stateData = machine.GetMinimizateMachine();
	m_melleeMachines[arg] = buffer;
	TranslateMilToMur(arg);
}

//Åñëè íóæíî äåòåðìèíèðîâàòü òî â .json ôàéëå àâòîìàò äîëæåí áûòü ïðåäñòàâëåí êàê àâòîìàò meale
void CParser::Determine(const std::string & arg)
{
	STransferMelleeToNoDeterm transferMelleeToNotDeterm(m_melleeMachines.at(arg));
	SNotDeterState notDeterData = transferMelleeToNotDeterm.m_deterData;
	CDetermAutomates machine(notDeterData);
	m_determMachines[arg] = machine.GetDeterAutomates();
}

void CParser::IsEquel(const std::string & arg1, const std::string & arg2)
{
	if (m_melleeMachines.find(arg1)!=m_melleeMachines.end())
	{
		IsEquelToMele(arg1, arg2);
	}
	else
	{
		IsEquelToMur(arg1, arg2);
	}
}

void CParser::IsEquelToMur(const std::string & arg1, const std::string & arg2)
{
	SEquivalenceÑhecking machine;
	machine.MoorEquivalence(m_mooraMachines.at(arg1), m_mooraMachines.at(arg2));
}

void CParser::IsEquelToMele(const std::string & arg1, const std::string & arg2)
{
	SEquivalenceÑhecking machine;
	machine.MelleeEquivalence(m_melleeMachines.at(arg1), m_melleeMachines.at(arg2));
}

void CParser::Save()
{
	std::ofstream file(m_outputFile);
	if (!file.is_open())
	{
		throw std::invalid_argument("can not open the file " + m_outputFile);
	}

	json jResultMachines;
	if (!m_melleeMachines.empty())
	{
		json jmeale;
		for (auto meale : m_melleeMachines)
		{
			//states block
			json jstates;
			for (auto it : meale.second.m_stateData)
			{
				jstates.push_back(it.first);
			}

			//transitions block
			json jtransitions;
			for (auto it : meale.second.m_stateData)
			{
				auto from = it.first;
				for (auto stateMelee : it.second->to)
				{
					auto input = stateMelee.first;
					auto to = stateMelee.second.first;
					auto output = stateMelee.second.second;
					json jtransition = {
						{"input", input},
						{"output", output},
						{"from", from},
						{"to", to}
					};
					jtransitions.push_back(jtransition);
				}
			}

			json j = {
				{"id", meale.first},
				{"type", "meale"},
				{"states", jstates },
				{"transitions", jtransitions}
			};
			jResultMachines.push_back(j);
		}
	}

	if (!m_mooraMachines.empty())
	{
		json jmoora;
		for (auto moora : m_mooraMachines)
		{
			//states block
			json jstates;
			for (auto it : moora.second.m_stateData)
			{
				jstates.push_back({ it.first, it.second->m_output });
			}

			//transitions block
			json jtransitions;
			for (auto it : moora.second.m_stateData)
			{
				json jtransition;
				auto from = it.second->m_name;//
				for (auto itTo : it.second->to)
				{
					auto to = itTo.second;
					auto input = itTo.first;
					jtransition = {
						{ "input", input },
						{ "from", from },
						{ "to", to }
					};
					jtransitions.push_back(jtransition);
				}
			}
			json j = {
				{ "id", moora.first },
				{ "type", "Determ moore" },
				{ "states", jstates },
				{ "transitions", jtransitions }
			};
			jResultMachines.push_back(j);
		}
	}
	//determ automate
	if (!m_determMachines.empty())
	{
		json jdeterm;
		for (auto determ : m_determMachines)
		{
			//states block
			json jstates;
			for (auto it : determ.second.m_stateData)
			{
				jstates.push_back({ it.first });
			}

			//transitions block
			json jtransitions;
			for (auto it : determ.second.m_stateData)
			{
				json jtransition;
				std::string from = it.second->m_name;//
				for (auto itTo : it.second->to)
				{
					auto to = itTo.first;
					auto input = itTo.second;
					jtransition = {
						{ "input", input },
						{ "from", from },
						{ "to", to }
					};
					jtransitions.push_back(jtransition);
				}
			}
			json j = {
				{ "id", determ.first },
				{ "type", "moore" },
				{ "states", jstates },
				{ "transitions", jtransitions }
			};
			jResultMachines.push_back(j);
		}
	}


	json j = {
		{"state machine",jResultMachines}
	};
	file << j.dump(4);
}
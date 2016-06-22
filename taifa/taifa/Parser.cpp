#include "stdafx.h"
#include "Parser.h"
#include "Minimizate.h"

using namespace std;
using json = nlohmann::json;

CParser::CParser(string const & command, string const &input, string const &output)
	: m_outputFileName(output)
{
	ParseInputData(input);
	ParseInputCommand(command);
}

void CParser::ParseInputData(std::string const &input)
{
	std::ifstream file(input);
	if (!file.is_open())
	{
		throw std::invalid_argument("can not open the file " + input);
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
			cout << "Meale machine" << std::endl;

			m_automat.isMealy = true;
			for (const auto & state : machineStates)
			{//add machine states
				m_automat.addState(SSymbols("", state.at("id"), "", "" ));
			}
			for (auto const &it : machineTransitions)
			{
				auto from = it.at("from");
				auto to = it.at("to");
				auto input = it.at("input");
				auto output = it.at("output");
				m_automat.addState({ to, from, input, output });
			}
			//OutputMeale();
		}
		else if (machineType == "moore")
		{
			cout << "Moore machine" << endl;
			m_automat.isMealy = false;;
			for (const auto & state : machineStates)
			{//add machine states
				SSymbols symbols = SSymbols("", state.at("id"), "", state.at("output"));
				m_automat.addState(symbols);
			}
			for (auto const &it : machineTransitions)
			{
				auto from = it.at("from");
				auto to = it.at("to");
				auto input = it.at("input");
				m_automat.addState({ to, from, input, "" });
			}
			//OutputMoore();
			//TranslateMooreToMeale();
		}
		else
		{
			throw std::invalid_argument("invalid machine type");
		}
	}
}

void CParser::ParseInputCommand(std::string const &command)
{
	std::ifstream file(command);
	if (!file.is_open())
	{
		throw std::invalid_argument("can not open the file " + command);
	}
	auto js = json::parse(file);//json принимает только поток ifstream 
	auto listCommand = js.at("commands");
	for (auto const &com : listCommand)
	{
		vector<string> args = com.at("arguments");
		for (auto const & arg : args)
		{
			auto type = com.at("type");
			if (type == "translate-mil-to-mur") { TranslateMealeToMoore(); }
			else if (type == "translate-mur-to-mil") { TranslateMooreToMeale(); }
			else if (type == "minimize-mur")
			{
				TranslateMooreToMeale();
				Minimize();
				TranslateMealeToMoore();
			}
			else if (type == "minimize-mil")
			{
				Minimize();
			}
			else if (type == "determine") { DeterminateMeale(); }
		}
	}
	SaveToJsonFile();
}


void CParser::TranslateMooreToMeale()
{
	OutputMeale(STranslateMooreToMeale::Translate(m_automat));
}

void CParser::TranslateMealeToMoore()
{
	OutputMoore(STranslateMealeToMoore::Translate(m_automat));
}

void CParser::DeterminateMeale()
{
	OutputMeale(SDeterminate::Determinate(m_automat));
}
void CParser::Minimize()
{
	CMinimizate minimize(m_automat);
	m_automat = minimize.GetMinimizedMachine();
	OutputMeale(m_automat);
}



void CParser::SaveToJsonFile()
{
	std::ofstream file(m_outputFileName);
	if (!file.is_open())
	{
		throw std::invalid_argument("can not open the file " + m_outputFileName);
	}

	json jResultMachines;
	auto automat = m_automat.GetMachine();
	if (!automat.empty())
	{
		json jvertex;
		json jtransitions;
		bool isMealy = m_automat.isMealy;
		for (auto const & it : automat)
		{
			jvertex.push_back(it.first);
			for (auto const & transitions : it.second)
			{
			
				auto rt = (*transitions.second.begin());
				/*json jout;
				json jto;
				for (auto const & iter : transitions.second)
				{
					jout.push_back(iter.output);
					jto.push_back(iter.to);
				}*/
				json i;
				if (isMealy)
				{
					i = {
						{"from", it.first },
						{"input", transitions.first },
						{"output", rt.output },
						{"to", rt.to }
					};
				}
				else
				{
					i = {
						{ "from", it.first },
						{ "input", transitions.first },
						{ "to", rt.to }
					};
				}
				jtransitions.push_back(i);
			}
		}
		string type = isMealy ? "mealy" : "moora";
		json j = {
			{ "id", "StateMachineX"},
			{ "type", type },
			{ "states", jvertex },
			{ "transitions", jtransitions }
		};
		jResultMachines.push_back(j);
	}

	json j = {
		{ "state machine", jResultMachines }
	};
	file << j.dump(4);

}

void CParser::OutputMeale() const
{
	for (auto const & it : m_automat.GetMachine())
	{
		cout << "Vertex -> " << it.first << endl;
		for (auto const & it2 : it.second)
		{
			cout << "******************************************************" << endl;
			cout << "input symbol -> " << it2.first << endl;
			cout << "output symbol -> " << (*it2.second.begin()).output << endl;
			cout << "Vertex to -> " << (*it2.second.begin()).to << endl;
			cout << "******************************************************" << endl;
		}
		cout << ">--------------------------------<" << endl;
	}
}


void CParser::OutputMoore() const
{
	for (auto const & it : m_automat.GetMachine())
	{
		cout << "Vertex -> " << it.first << endl;
		cout << "output symbol -> " << (*(*it.second.begin()).second.begin()).output << endl;
		for (auto const & it2 : it.second)
		{
			cout << "******************************************************" << endl;
			cout << "input symbol -> " << it2.first << endl;
			cout << "Vertex to -> " << (*it2.second.begin()).to << endl;
			cout << "******************************************************" << endl;
		}
		cout << ">--------------------------------<" << endl;
	}
}

void CParser::OutputMoore(CViewAutomates const &automat) const
{
	for (auto const & it : automat.GetMachine())
	{
		cout << "Vertex -> " << it.first << endl;
		cout << "output symbol -> " << (*(*it.second.begin()).second.begin()).output << endl;
		for (auto const & it2 : it.second)
		{
			cout << "******************************************************" << endl;
			cout << "input symbol -> " << it2.first << endl;
			cout << "Vertex to -> " << (*it2.second.begin()).to << endl;
			cout << "******************************************************" << endl;
		}
		cout << ">--------------------------------<" << endl;
	}
}

void CParser::OutputMeale(CViewAutomates const &automat) const
{
	for (auto const & it : automat.GetMachine())
	{
		cout << "Vertex -> " << it.first << endl;
		for (auto const & it2 : it.second)
		{
			cout << "******************************************************" << endl;
			cout << "input symbol -> " << it2.first << endl;
			cout << "output symbol -> " << (*it2.second.begin()).output << endl;
			cout << "Vertex to -> " << (*it2.second.begin()).to << endl;
			cout << "******************************************************" << endl;
		}
		cout << ">--------------------------------<" << endl;
	}
}
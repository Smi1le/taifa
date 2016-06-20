#include "stdafx.h"
#include "Parser.h"

using namespace std;
using json = nlohmann::json;

CParser::CParser(string const & command, string const &input, string const &output)
	: outputFileName(output)
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

			}
			else if (type == "minimize-mil")
			{

			}
			else if (type == "determine")
			{

			}
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



void CParser::SaveToJsonFile()
{

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
			cout << "output symbol -> " << it2.second.output << endl;
			cout << "Vertex to -> " << it2.second.to << endl;
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
		cout << "output symbol -> " << (*it.second.begin()).second.output << endl;
		for (auto const & it2 : it.second)
		{
			cout << "******************************************************" << endl;
			cout << "input symbol -> " << it2.first << endl;
			cout << "Vertex to -> " << it2.second.to << endl;
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
		cout << "output symbol -> " << (*it.second.begin()).second.output << endl;
		for (auto const & it2 : it.second)
		{
			cout << "******************************************************" << endl;
			cout << "input symbol -> " << it2.first << endl;
			cout << "Vertex to -> " << it2.second.to << endl;
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
			cout << "output symbol -> " << it2.second.output << endl;
			cout << "Vertex to -> " << it2.second.to << endl;
			cout << "******************************************************" << endl;
		}
		cout << ">--------------------------------<" << endl;
	}
}
#pragma once

struct SMooreElement
{
	SMooreElement(std::string const &o, std::string const &f)
		: output(o)
		, from(f)
	{}
	std::string output;
	std::string from;
};

using mooreTable = std::map<SMooreElement, std::map<std::string, std::string>>;



class CMooreStatement
{
public:
	/*CMooreStatement() = default;
	void AddState(SSymbols const &elementTable);
	mooreTable GetMachine() const;
	size_t Find(SMooreElement const &cell) const;*/
	//std::pair<SMooreElement, std::map<std::string, std::string>>& At(SMooreElement const &val);
private:
	mooreTable m_moore;
	bool m_notDetermined = false;
};

bool operator <(SMooreElement const &f, SMooreElement const &s);

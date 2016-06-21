// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <map>
#include <set>
#include <queue>


struct SSymbols
{
	SSymbols() = delete;
	SSymbols(std::string const &t, std::string const &f, std::string const &i, std::string const &o)
		: to(t)
		, from(f)
		, input(i)
		, output(o)
	{}
	std::string to;
	std::string from;
	std::string input;
	std::string output;
};


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы

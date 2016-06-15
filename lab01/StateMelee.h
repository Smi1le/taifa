#pragma once
#include "stdafx.h"


/*
	Структура SStateMelee хранит в себе все переходы из какого то узла в другие, т.е. из
	 |  q1 |  q2 |q3
	_|_____|_____|____
   x1|q2/y1|q0/y1|q0/y2
   __|_____|_____|____
   x2|q0/y1|q2/y2|q1/y1
   __|_____|_____|____

	в структуре будет храниться лишь один из этих столбов
	 | q1  |			 |  q2 |			|  q3 |
	_|_____|			_|_____|		   _|_____|
   x1|q2/y1|		   x1|q0/y1|		  x1|q0/y2|
   __|_____|		   __|_____|		  __|_____|
   x2|q0/y1|		   x2|q2/y2|		  x2|q1/y1|
   __|_____|		   __|_____|		  __|_____|

   в to будет храниться <Входной символ(x1, x2), <имя вершины куда(q0, q2), по какому символу(y1, y2)>
   в toNoDeterm будет храниться <Входной символ(x1, x2), <все вершины, в которые есть путь из узла по Входному символу>>
*/


struct SStateMelee
{
	SStateMelee(const std::string & name);
	bool noDeterm = false;
	std::string name = "";
	std::map<std::string, std::pair<std::string, std::string>> to; // map<Входной символ(x1, x2 ..), <имя куда, выходной символ(y1, y2 ..)>>
	void SetPath(std::string inpSym, std::string toName, std::string out); // inpSym = x1, x2..; toName = имя узла, куда идет путь; out = y1, y2 ..
	std::map<std::string, std::set<std::string>> toNoDeterm; // map<Входной символ(x1, x2 ..), <имя куда, выходной символ(y1, y2 ..)>>
};


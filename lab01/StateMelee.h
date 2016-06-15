#pragma once
#include "stdafx.h"


/*
	��������� SStateMelee ������ � ���� ��� �������� �� ������ �� ���� � ������, �.�. ��
	 |  q1 |  q2 |q3
	_|_____|_____|____
   x1|q2/y1|q0/y1|q0/y2
   __|_____|_____|____
   x2|q0/y1|q2/y2|q1/y1
   __|_____|_____|____

	� ��������� ����� ��������� ���� ���� �� ���� �������
	 | q1  |			 |  q2 |			|  q3 |
	_|_____|			_|_____|		   _|_____|
   x1|q2/y1|		   x1|q0/y1|		  x1|q0/y2|
   __|_____|		   __|_____|		  __|_____|
   x2|q0/y1|		   x2|q2/y2|		  x2|q1/y1|
   __|_____|		   __|_____|		  __|_____|

   � to ����� ��������� <������� ������(x1, x2), <��� ������� ����(q0, q2), �� ������ �������(y1, y2)>
   � toNoDeterm ����� ��������� <������� ������(x1, x2), <��� �������, � ������� ���� ���� �� ���� �� �������� �������>>
*/


struct SStateMelee
{
	SStateMelee(const std::string & name);
	bool noDeterm = false;
	std::string name = "";
	std::map<std::string, std::pair<std::string, std::string>> to; // map<������� ������(x1, x2 ..), <��� ����, �������� ������(y1, y2 ..)>>
	void SetPath(std::string inpSym, std::string toName, std::string out); // inpSym = x1, x2..; toName = ��� ����, ���� ���� ����; out = y1, y2 ..
	std::map<std::string, std::set<std::string>> toNoDeterm; // map<������� ������(x1, x2 ..), <��� ����, �������� ������(y1, y2 ..)>>
};


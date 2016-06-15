#pragma once
#include "stdafx.h"

/*
	������ ��������� SStateMoora ������ � ���� ��� �������� ���� ��� ������ ���� �������, �.�. ��
	����� �������
	 |q1|q2|q3
	_|__|__|__
   x1|q1|--|--
   __|__|__|__
   x2|q2|q1|--
   __|__|__|__
	
   � ��������� ����� ��������� ���� ���� �������, ��� ����, ��� �� ����
   |q1|			 |q2|			|q3|
  _|__|			_|__|		   _|__|
 x1|q1|		   x1|--|		  x1|--|
 __|__|		   __|__|		  __|__|
 x2|q2|		   x2|q2|		  x2|--|	
 __|__|		   __|__|		  __|__|
   */


struct SStateMoora
{
	SStateMoora(const std::string & name, const std::string & output); // name - q1 (��� ����), output - y1
	void SetPath(std::string inp, std::string toName);
	std::string m_name = "";
	std::string m_output = "";
	std::map<std::string, std::string> to; // ������ ������� ������� ������ (x1, x2, ...), ������ ��� ���� (q1, q2, ...) 
};
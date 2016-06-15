#include "TransferMelleeToNoDeterm.h"


STransferMelleeToNoDeterm::STransferMelleeToNoDeterm(SMelleeStatesment & notDeterData)
{
	//���� ���� �������� �� ���� ����� ��������
	for (auto &it : notDeterData.m_stateData)
	{
			//������� �� ����������������� ������� � ������ ����, ������� � ������ ������ ��������

			/*
				�.�. ������ ���� �������� �� ��� ���� ������
				  |x0|x1
				__|__|__
				S0|S1|S2  <-- � ���������� ��� �������� �� S0 �� x0 (�������� �� ����� ������ ��� 1)
				__|__|__
				S1|S2|S6
				__|__|__
				S2|S4|S5
				__|__|__
				S6|--|S8
				__|__|__
				S4|S9|S0
				� �.�.
				
				*/
			SStateNotDetermine notDeterm(it.second->name);
			for (auto &jd : it.second->to)
			{
				notDeterm.SetPath(jd.first, jd.second.first);
			}
			//���� �� ������� �� ������ ������� ���� ����� ��� ���� ����, �� ���� ����
			if (it.second->noDeterm)
			{
				//�������� ��� �� �� ���� ����� ��� ���� �� ���� ������� � ���������� �� � �������  ,�.�. ������� ��� ����� ������ � �������
				/*
				
					  |	  x0   |  x1  |
					__|________|______|__
					S1|S2,S4,S6|S5, s2|
					__|________|______|__
				
				*/
				for (auto &jd : it.second->toNoDeterm)
				{
					for (auto &gh : jd.second)
					{
						notDeterm.SetPath(jd.first, gh);
					}
				}
			}
			vectorNodes.push_back(notDeterm);
	}
	for (auto &jds : vectorNodes)
	{
		m_deterData.AddState(jds);
	}
}
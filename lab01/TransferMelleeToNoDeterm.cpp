#include "TransferMelleeToNoDeterm.h"


STransferMelleeToNoDeterm::STransferMelleeToNoDeterm(SMelleeStatesment & notDeterData)
{
	//Этот цикл проходит по всем узлам автомата
	for (auto &it : notDeterData.m_stateData)
	{
			//Создает не детерминированную вершину с именем узла, который в данный момент проходит

			/*
				т.е. первый цикл проходит по вот этой строке
				  |x0|x1
				__|__|__
				S0|S1|S2  <-- и записывает все переходы из S0 по x0 (возможно их будет больше чем 1)
				__|__|__
				S1|S2|S6
				__|__|__
				S2|S4|S5
				__|__|__
				S6|--|S8
				__|__|__
				S4|S9|S0
				и т.д.
				
				*/
			SStateNotDetermine notDeterm(it.second->name);
			for (auto &jd : it.second->to)
			{
				notDeterm.SetPath(jd.first, jd.second.first);
			}
			//Если из вершины по одному символу есть более чем один путь, то идет сюда
			if (it.second->noDeterm)
			{
				//Проходит так же по всем путям что есть из этой вершины и записывает их в таблицу  ,т.е. создает вот такую строку в таблице
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
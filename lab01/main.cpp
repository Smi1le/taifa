#include "stdafx.h"
#include "MelleeStatesment.h"
#include "MooraStatesment.h"
#include "Parser.h"
#include "TransferMelleToMoora.h"
#include "TransferMoorToMellee.h"
#include "TransferMelleeToNoDeterm.h"
#include "DeterminateAutomates.h"

int main(int argc, char* argv[])
{
	//<название ррограммы> <путь до файл команд> <путь до файла ввода> <путь до файла вывода>
	std::string commandFileName;
	std::string inputFileName;
	std::string outputFileName;
	std::cout << "<path to command file> <path to input file> <path to output file>" << std::endl;
	if (argc == 4)
	{
		commandFileName = argv[1];
		inputFileName = argv[2];
		outputFileName = argv[3];
	}
	else
	{
		std::cin >> commandFileName >> inputFileName >> outputFileName;
	}
	CParser(commandFileName, inputFileName, outputFileName);
	return 0;
}
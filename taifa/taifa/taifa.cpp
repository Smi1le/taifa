#include "stdafx.h"
#include "Parser.h"

//int main(int argc, char *argv[])
int main()
{
	/*if (argc != 4)
	{
		std::cout << "Error! Usage <path to command file> <path to input file> <path to output file>" << std::endl;
	}*/
	std::string command;
	std::string input;
	std::string output;
	command = "tests/commands3.json";//argv[1];
	input = "tests/input2.json";//argv[2];
	output = "tests/out.json";//argv[3];
	CParser(command, input, output);
    return 0;
}


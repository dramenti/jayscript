#include<map>
#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<cassert>
#include<exception>
#include "globals.h"
#include "jaycommand.h"

std::map<std::string, std::string> var_ints;
std::map<std::string, std::string> var_strings;
std::map<std::string, char> opMapping;
std::ifstream prog_file;

void init_globals()
{
    //init Integer Variables
    var_ints["TRUE"] = "1";
    var_ints["FALSE"] = "0";
    
    //init operator mapping for switch statement in jayparse
    opMapping["+"] = '+';
    opMapping["-"] = '-';
    opMapping["/"] = '/';
    opMapping["*"] = '*';
    opMapping["%"] = '%';
    opMapping["<"] = '<';
    opMapping[">"] = '>';
    opMapping["=="] = '=';
    opMapping["<="] = ']';
    opMapping[">="] = '[';
    opMapping["AND"] = '&';
    opMapping["OR"] = '|';
    opMapping["!="] = ',';
}

int main(int argc, char* argv[]) //command line arguments. argv is arguments
{
    init_globals();
    if (argc != 2)
    {
        std::cout << "Correct usage is: jayrun [filename]" << std::endl;
        return 0;
    }
    
    /*Open the source code*/
    prog_file.open(argv[1]);
    
    std::string each_line;
    std::istringstream full_line;
    while (std::getline(prog_file, each_line))
    {
        full_line.str(each_line);
        try
        {
            std::cout << "In main, will run line: "<< each_line << std::endl;
            run_line(full_line);
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            return 0;
        }
    }
    return 0;
}
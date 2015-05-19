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
std::vector<std::string> prog_file;
int gnest = 0;

void init_globals()
{
    gnest = 0;
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
    std::ifstream pf_stream (argv[1]);
    
    
    std::string each_line;
    
    while (std::getline(pf_stream, each_line))
    {
        prog_file.push_back(each_line);
    }
    
    
    std::istringstream full_line;
    
    
    /*Read from file, line by line*/
    for (int i = 0; i < prog_file.size(); i++)
    {
        each_line = prog_file.at(i);
        full_line.str(each_line);
        try
        {
            //std::cout << "In main, will run line: "<< each_line << std::endl;
            run_line(full_line); //execute the line
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            return 0;
        }
    }
    return 0;
}
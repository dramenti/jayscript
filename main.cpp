#include<map>
#include<fstream>
#include<iostream>
#include<cassert>
#include<exception>
#include<cstring>
#include "globals.h"
#include "jaycommand.h"
#include "operators.h"

#define DEFAULT_INITIAL_GLINE_VALUE 0
#define DEFAULT_INITIAL_NESTING_LEVEL 0

std::map<std::string, std::string> var_ints;
std::map<std::string, std::string> var_strings;
std::map<std::string, char> opMapping;
std::vector<std::string> prog_file;
unsigned gline;
int gnest = 0;

void init_globals()
{
    gnest = 0;
    //init Integer Variables
    var_ints["TRUE"] = "1";
    var_ints["FALSE"] = "0";
    
    //initialize the operator map
    initialize_operator_map();
}

int main(int argc, char* argv[]) //command line arguments. argv is arguments
{
    if (argc != 2)
    {
        std::cout << "Correct usage is: jayrun [filename]" << std::endl;
        return 0;
    }
    init_globals();
    
    /*Open the source code*/
    strcat(argv[1], ".jays");
    std::ifstream pf_stream (argv[1]);
    std::string each_line;
    while (std::getline(pf_stream, each_line))
    {
        prog_file.push_back(each_line);
    }
    
    pf_stream.close();
    std::istringstream full_line;
    
    
    gline = DEFAULT_INITIAL_GLINE_VALUE;
    CodeBlock main_program_block;
    main_program_block.begin_line = gline;
    main_program_block.end_line = prog_file.size();
    try
    {
        execute_block(main_program_block, DEFAULT_INITIAL_NESTING_LEVEL);
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 0;
    }
    
    /*Read from file, line by line*/
    /* OLD CODE
    for (gline = 0; gline < prog_file.size(); gline++)
    {
        each_line = prog_file.at(gline);
        full_line.str(each_line);
        try
        {
            //std::cout << "In main, will run line: "<< each_line << std::endl;
            run_line(full_line, 0); //execute the line, no nesting so 0
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            return 0;
        }
    } */
    return 0;
}
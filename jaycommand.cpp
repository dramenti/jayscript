#include<string>
#include<iostream>
#include<sstream>
#include<deque>
#include<cassert>
#include "globals.h"
#include "jaylexer.h"
#include "jayparse.h"
#include "jaycommand.h"
#include "jaytools.h"
#include "jayblocks.h"

void print(std::string& line)
{
    //std::cout << "in void print with string: " << line << std::endl;
    result to_print = do_eval(lex(line));
    if (to_print.type == 0)
    {
        std::cout << to_print.integer << std::endl;
    }
    else if (to_print.type == 1)
    {
        std::cout << to_print.str << std::endl;
    }
    else
    {
        std::cout << "result.type not 0 or 1!!!" << std::endl;
    }
}

void set(std::istringstream& line)
{
    std::string identifier;
    std::getline(line, identifier, '=');
    //trim trailing space
    trim_tail(identifier);
    assert(is_Valid_Identifier(identifier));
    //std::cout << "In set, attempting to set a value to the variable: " << identifier << std::endl;
    
    std::string rol; //rest of line
    std::getline(line, rol); //store rest of line 
    //std::cout << "In set, will set variable equal to: " << rol << std::endl;
    
    result to_set = do_eval(lex(rol));
    if (to_set.type == 0) //INTEGER
    {
        var_ints[identifier] = convert_int_to_string(to_set.integer);
        //std::cout << "In set, just set " << identifier << " to " << var_ints[identifier] << std::endl;
    }
    else if (to_set.type == 1) //STRING
    {
        var_strings[identifier] = to_set.str;
    }
}

void input(std::istringstream& line)
{
    std::string identifier;
    std::getline(line, identifier, ' ');
    assert(is_Valid_Identifier(identifier));
    
    std::string input_line;
    std::getline(std::cin, input_line);
    result to_input = do_eval(lex(input_line));
    if (to_input.type == 0) //INTEGER
    {
        var_ints[identifier] = convert_int_to_string(to_input.integer);
        //std::cout << "In set, just set " << identifier << " to " << var_ints[identifier] << std::endl;
    }
    else if (to_input.type == 1) //STRING
    {
        var_strings[identifier] = to_input.str;
    }
}


/*void flow_if(std::istringstream& line)
{
    //note: right now line contains everything after "IF" -- the expression
    If_Flow fl; //creates a new If_Flow, will consist of If Block plus optional Elsifs
    //and possibly an Else block
    //first, it stores the entire if block, and all elsifs, and the else, up to END
    //reads next line, until line no longer begins with 4 spaces or tab \t
    //while reading, lines are added to the block with the tab OR 4 spaces stripped off
    std::getline(f1.IB_exp); //rest of line is the IF expression
    
    //now, store into block while lines begin with 4 spaces or tabs
}*/

void find_command(std::string& command, std::istringstream& rest_of_line)
{
    if (command == "PRINT")
    {
        std::string line_to_eval;
        std::getline(rest_of_line, line_to_eval); //get the rest
        print(line_to_eval);
    }
    else if (command == "SET")
    {
        set(rest_of_line);
    }
    else if (command == "INPUT")
    {
        input(rest_of_line);
    }
    else
    {
        std::cout << "Command " << command << " not recognized!" << std::endl;
    }
}

//full_line is a full line, such as PRINT "Hello World!" 
//or SET x 56
void run_line(std::istringstream& full_line)
{
    //get rid of leading whitespace or tabspace
    while (full_line.peek() == ' ' || full_line.peek() == '\t')
    {
        full_line.ignore(1);
    }
    //std::cout << "In run_line with full_line.str: " << full_line.str() << std::endl;
    full_line.clear();
    full_line.seekg(0);
    //std::cout << "In run_line with full_line peek: " << (char)full_line.peek() << std::endl;
    //std::cout << "In run_line with full_line fail state: " << full_line.fail() << std::endl;
    std::string command = "";
    std::getline(full_line, command, ' '); //stop at space
    //std::cout << "In run_line with command: " << command << std::endl;
    //now command contains the command, like PRINT or SET
    //full_line is now left with the argument(s) of the command
    find_command(command, full_line);
}
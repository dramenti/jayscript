#include<string>
#include<iostream>
#include<sstream>
#include<deque>
#include<cassert>
#include<cstdlib>
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
    //std::cout << "in input just inputted: " << input_line << std::endl;
    result to_input = do_eval(lex(input_line));
    //std::cout << "in input computed result to_input of type: " << to_input.type << std::endl;
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

void flow_while(std::istringstream& line)
{
    //basically follow flow_if
    gnest++;
    While_Flow wf;
    wf.nestlevel = gnest;
    gline++;
    wf.While_Block.begin_line = gline;
    std::getline(line, wf.WB_exp);
    gline = look_for_end_of_block(gline, wf.nestlevel);
    wf.While_Block.end_line = gline;
    
    
    line.str(prog_file[gline]);
    
    //TODO: replace having to run the whole line with just checking for the command to avoid problems
    //ie have a get command from line function, maybe make run_line use that
    cmd_types cm = run_line(line, wf.nestlevel-1);
    
    if (cm != END)
    {
        std::cout << "ERROR: cm was not END, but: " << cm << std::endl;
        exit(1);
    }
    
    wf.line_of_END = gline;
    
    execute_flow_while(wf);
    
    gnest--;
}

void execute_flow_while(While_Flow wf)
{
    //continue working on this
    //the while loop
    while(do_eval(lex(wf.WB_exp)).integer)
    {
        execute_block(wf.While_Block, wf.nestlevel);
    }
    gline = wf.line_of_END;
}


void flow_if(std::istringstream& line)
{
    gnest++;
    //note: right now line contains everything after "IF" -- the expression
    //note: gline right now is the location of the IF line
    If_Flow f1; //creates a new If_Flow, will consist of If Block plus optional Elsifs
    f1.nestlevel = gnest;
    gline++;
    f1.If_Block.begin_line = gline;
    //std::cout << "In flow_if, set f1 begin line to gline, value of: " << gline << std::endl;
    std::getline(line, f1.IB_exp); //rest of line is the IF expression
    
    gline = look_for_end_of_block(gline, f1.nestlevel); //line number of first line past the IF that is not indented
    f1.If_Block.end_line = gline;
    //std::cout << "In flow_if, set f1 end line to gline, value of: " << gline << std::endl;
    
    //now let's see if there are ELSIFS
    //note: gline is a potential start of ELSIFs
    //use the enum return value ELSIF to check if there is an ELSIF
    line.str(prog_file[gline]);
    cmd_types cm = run_line(line, f1.nestlevel-1);
    while (cm == ELSIF) //there IS elsif
    {
        //since line is passed by reference it should save the current location, right before ELSIF's argument
        std::string nxt_EIBexp;
        std::getline(line, nxt_EIBexp);
        f1.EIB_exps.push_back(nxt_EIBexp);
        CodeBlock nxt_elsif; //new elsif block, will append to Elsif Blocks
        gline++; //line starts at next
        nxt_elsif.begin_line = gline; //begin line is the current line in the program
        gline = look_for_end_of_block(gline, f1.nestlevel); //line number of first line past the ELSIF that is not indented
        nxt_elsif.end_line = gline;
        f1.Elsif_Blocks.push_back(nxt_elsif);
        line.str(prog_file[gline]);
        cm = run_line(line, f1.nestlevel-1);
    }
    if (cm == ELSE)
    {
        //basically do everything that was done for the IF block
        //only this time there is no expression argument!! 
        //right now gline contains line of ELSE
        gline++;
        f1.Else_Block.begin_line = gline;
        gline = look_for_end_of_block(gline, f1.nestlevel);
        f1.Else_Block.end_line = gline;
        line.str(prog_file[gline]); //note: if nested, there will be an error...
        //fix: prog_file[gline] will give the full line, with all indentation
        //a nested if else will be of level 2 nesting, which means its if/elsif/else
        //is at a nest level of 1!!!
        //therefore when we do line.str(prog_file[gline]) we won't be able to execute it
        //because it won't parse the command properly
        //so when we do prog_file[gline] we have to skip f1.nestlevel minus 1
        //amount of tabspace
        cm = run_line(line, f1.nestlevel-1);
    }
    if (cm != END)
    {
        std::cout << "ERROR: cm was not END, but: " << cm << std::endl;
        exit(1);
    }
    f1.line_of_END = gline;
    //ok, f1 is now a finished block! now we execute it
    execute_flow_if(f1);
    //once done, go back nest
    gnest--;
}

void execute_flow_if(If_Flow IfL)
{
    //first: do eval of lex of IfL.IB_exp
    //if true, execute IfL.If_Block
    if (do_eval(lex(IfL.IB_exp)).integer)
    {
        execute_block(IfL.If_Block, IfL.nestlevel);
        gline = IfL.line_of_END;
        return;
    }
    else
    {
        //now try each ELSIF until one works
        for (unsigned e = 0; e < IfL.Elsif_Blocks.size(); e++)
        {
            if (do_eval(lex(IfL.EIB_exps.at(e))).integer)
            {
                execute_block(IfL.Elsif_Blocks.at(e), IfL.nestlevel);
                gline = IfL.line_of_END;
                return;
            }
        }
        
        //if we're here, no ELSIF worked...
        //so we're at ELSE.
        execute_block(IfL.Else_Block, IfL.nestlevel);
        gline = IfL.line_of_END;
        return;
    }
}

void execute_block(CodeBlock cb, int tabskip)
{
    std::istringstream full_line;
    std::string each_line;
    for (gline = cb.begin_line; gline < cb.end_line; gline++)
    {
        each_line = prog_file.at(gline);
        full_line.str(each_line);
        run_line(full_line, tabskip);
    }
}

//looks for the index beyond last line of the block, given a starting line number and nest level of the block
unsigned look_for_end_of_block(unsigned start_line, int nst_lvl)
{
    unsigned end_line = start_line; //this will contain the answer at the end
    //pseudocode:
    //while line begins with (nst_lvl) tabs or softabs, increment end_line;
    while (begins_with_tab(prog_file.at(end_line), nst_lvl))
    {
        //std::cout << "in look_for_end_of_block, line number " << end_line << " is part of block.\n";
        end_line++;
    }
    //end_line is now one past the end of the block
    return end_line;
}


cmd_types find_command(std::string& command, std::istringstream& rest_of_line)
{
    if (command == "PRINT")
    {
        std::string line_to_eval;
        std::getline(rest_of_line, line_to_eval); //get the rest
        print(line_to_eval);
        return PRINT;
    }
    else if (command == "SET")
    {
        set(rest_of_line);
        return SET;
    }
    else if (command == "INPUT")
    {
        input(rest_of_line);
        return INPUT;
    }
    else if (command == "IF")
    {
        flow_if(rest_of_line);
        return IF;
    }
    else if (command == "ELSIF")
    {
        return ELSIF;
    }
    else if (command == "ELSE")
    {
        return ELSE;
    }
    else if (command == "END")
    {
        return END;
    }
    else if (command == "WHILE")
    {
        flow_while(rest_of_line);
        return WHILE;
    }
    else
    {
        std::cout << "Command: " << command << " not recognized!" << std::endl;
    }
    return END;
}

//full_line is a full line, such as PRINT "Hello World!" 
//or SET x 56
cmd_types run_line(std::istringstream& full_line, int tabskip)
{
    //get rid of leading whitespace or tabspace
    /*while (full_line.peek() == ' ' || full_line.peek() == '\t')
    {
        full_line.ignore(1);
    }*/
    
    
    //std::cout << "In run_line with full_line.str: " << full_line.str() << std::endl;
    full_line.clear();
    full_line.seekg(0);
    
    for (int t = 0; t < tabskip; t++) //ignore \t or ' '
    {
        if (full_line.peek() == '\t')
        {
            full_line.ignore(1);
        }
        else if (full_line.peek() == ' ')
        {
            full_line.ignore(4); //soft tab
        }
        else
        {
            std::cout << "Not indented in agreement with tabskip!" << std::endl;
        }
    }
    
    //std::cout << "In run_line with full_line peek: " << (char)full_line.peek() << std::endl;
    //std::cout << "In run_line with full_line fail state: " << full_line.fail() << std::endl;
    std::string command = "";
    std::getline(full_line, command, ' '); //stop at space
    //std::cout << "In run_line with command: " << command << std::endl;
    //now command contains the command, like PRINT or SET
    //full_line is now left with the argument(s) of the command
    return find_command(command, full_line);
}
#include<string>
#include<sstream>
#include "jayblocks.h"
#ifndef JAYCOMMAND_H
#define JAYCOMMAND_H

enum cmd_types {PRINT, SET, INPUT, IF, ELSIF, ELSE, END, WHILE, NONE};


void print(std::string& line);

void set(std::istringstream& line);

void input(std::istringstream& line);

void flow_if(std::istringstream& line);

void flow_while(std::istringstream& line);

void execute_block(CodeBlock cb, int tabskip);

void execute_flow_if(If_Flow IfL);

void execute_flow_while(While_Flow wf);

cmd_types find_command(std::string& command, std::istringstream& rest_of_line);

cmd_types run_line(std::istringstream& full_line, int tabskip);

unsigned look_for_end_of_block(unsigned start_line, int nst_lvl);

#endif
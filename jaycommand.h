#include<string>
#include<sstream>
#include "jayblocks.h"
#ifndef JAYCOMMAND_H
#define JAYCOMMAND_H

enum cmd_types {PRINT, SET, INPUT, IF, ELSIF, ELSE, END};


void print(std::string& line);

void set(std::istringstream& line);

void input(std::istringstream& line);

void flow_if(std::istringstream& line);

void execute_block(CodeBlock cb, int tabskip);

void execute_flow_if(If_Flow IfL);

cmd_types find_command(std::string& command, std::istringstream& rest_of_line);

cmd_types run_line(std::istringstream& full_line, int tabskip);

int look_for_end_of_block(int start_line, int nst_lvl);

#endif
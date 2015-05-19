#include<string>
#include<sstream>
#ifndef JAYCOMMAND_H
#define JAYCOMMAND_H


void print(std::string& line);

void set(std::istringstream& line);

void input(std::istringstream& line);

void flow_if(std::istringstream& line);

void find_command(std::string& command, std::istringstream& rest_of_line);

void run_line(std::istringstream& full_line);

//reads from the source file, until no longer indented
//reads and stores into block, lines that begin with:
//4 spaces OR \t aka tabspace
//when storing, this space is deleted!
//but not ALL initial space to allow for nested control flow
/*void store_block(CodeBlock& cb);*/

#endif
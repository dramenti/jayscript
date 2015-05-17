#include<string>
#include<sstream>
#ifndef JAYCOMMAND_H
#define JAYCOMMAND_H


void print(std::string& line);

void set(std::istringstream& line);

void find_command(std::string& command, std::istringstream& rest_of_line);

void run_line(std::istringstream& full_line);

#endif
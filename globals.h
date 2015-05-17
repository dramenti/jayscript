#include<map>
#include<string>
#include<fstream>
#ifndef GLOBALS_H
#define GLOBALS_H

extern std::map<std::string, std::string> var_ints; //note: string is the string representation of integer
extern std::map<std::string, std::string> var_strings;

extern std::map<std::string, char> opMapping; //used for switch statement

extern std::ifstream prog_file; //the program code itself! Will use .open on the source code for the JayScript file

#endif
#include<map>
#include<string>
#include<fstream>
#include<vector>
#ifndef GLOBALS_H
#define GLOBALS_H


/*Maps that store variables*/
extern std::map<std::string, std::string> var_ints; //note: string is the string representation of integer
extern std::map<std::string, std::string> var_strings;

extern std::map<std::string, char> opMapping; //used for switch statement

extern std::vector<std::string> prog_file; //the contents of the source code

extern int gnest;

extern int gline;

#endif
#include<string>
#include<deque>
#include "globals.h"
#ifndef JAYLEXER_H
#define JAYLEXER_H

/*Returns a deque of tokens*/
std::deque<std::string> lex (std::string& line);


#endif
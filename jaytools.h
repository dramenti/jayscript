#include "globals.h"
#include<string>
#ifndef JAYTOOLS_H
#define JAYTOOLS_H

bool is_num(std::string s);

bool is_var_int(std::string s);

bool is_var_string(std::string s);

int convert_string_to_int(std::string s);

std::string convert_int_to_string(int num);

bool is_OpChar(char c);

bool in_int_range(int x);
bool in_upcase_range(int x);
bool in_lowcase_range(int x);

bool is_IdentifierChar(char c);

bool is_Valid_Identifier(std::string id);

#endif
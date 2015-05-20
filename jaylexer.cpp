#include<string>
#include<deque>
#include<iostream>
#include "globals.h"
#include "jaytools.h"
#include "jaylexer.h"
std::deque<std::string> lex (std::string& line)
{
    //strings are single token for now
    std::deque<std::string> expression;
    trim_tail(line);
    //for now, space after closing quote is not allowed
    if (line.at(0) == '"' && line.at(line.size()-1) == '"')
    {
        expression.push_back(line);
        return expression;
    }
    
    std::string next_token;
    bool hyphen_is_negative = true;
    int i = 0;
    //std::cout << "In lex, about to tokenize integer expression: " << line << std::endl;
    while(i < line.size())
    {
        if (line.at(i) == ' ' || line.at(i) == '\t')
        {
            i++;
            continue;
        }
        next_token = "";
        
        /*Deals with integer literal tokens*/
        if (is_num(line.substr(i, 1)) || (line.at(i) == '-' && hyphen_is_negative))
        {
            //std::cout << "In lex, in if statement to tokenize integer literal" << std::endl;
            next_token += line.at(i);
            //std::cout << "In lex, began tokenizing integer literal, next_token is: " << next_token << std::endl;
            i++;
            while (i < line.size() && is_num(line.substr(i,1)))
            {
                next_token += line.at(i);
                i++;
            }
            hyphen_is_negative = false;
        }
        
        /*Deals with parenthesis tokens*/
        else if (line.at(i) == '(')
        {
            next_token += line.at(i);
            i++;
            hyphen_is_negative = true;
        }
        else if (line.at(i) == ')')
        {
            next_token += line.at(i);
            i++;
            hyphen_is_negative = false;
        }
        /*Deals with symbolic operators, not AND/OR etc.*/
        else if (is_OpChar(line.at(i)))
        {
            next_token += line.at(i);
            i++;
            while (i < line.size() && is_OpChar(line.at(i)) && line.at(i) != '-')
            {
                next_token += line.at(i);
                i++;
            }
            hyphen_is_negative = true;
        }
        
        else if (is_IdentifierChar(line.at(i)))
        {
            next_token += line.at(i);
            i++;
            while (i < line.size() && is_IdentifierChar(line.at(i)))
            {
                next_token += line.at(i);
                i++;
            }
            if (next_token == "AND" || next_token == "OR")
            {
                hyphen_is_negative = true;
            }
            else
            {
                hyphen_is_negative = false;
            }
        }
        //std::cout << "In lex, next_token is: " << next_token << std::endl;
        expression.push_back(next_token);
    }
    return expression;
}
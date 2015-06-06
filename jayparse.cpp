#include<deque>
#include<iostream>
#include "globals.h"
#include "jaytools.h"
#include "jayparse.h"

/*struct result
{
    std::string str;
    int type; //1 for string, 0 for integer
    int integer;
};*/


/*Applies the infix operator op on a and b
For example if op is "+" then operate(a,b,op)
will return the quantity a+b
*/
int operate(int a, int b, std::string op)
{
    return function_map[op](a, b);
}

template<class T>
T eval_expression(std::deque<std::string> expression)
{
    /*
    Just some generic stuff
    */
}

/*
Evaluates a string
*/

template<>
std::string eval_expression<std::string>(std::deque<std::string> expression)
{
    std::string raw_str = expression.at(0);
    std::string processed_expression = "";
    std::string format_var;
    for (unsigned i = 1; i < raw_str.size()-1; i++)
    {
        if (raw_str[i] == '%')
        {
            format_var = "";
            i++;
            while(raw_str[i] != '%')
            {
                format_var += raw_str[i];
                i++;
            }
            if (var_ints.find(format_var) != var_ints.end())
            {
                 processed_expression += var_ints[format_var];
            }
            else if (var_strings.find(format_var) != var_strings.end())
            {
                 processed_expression += var_strings[format_var];
            }
            else
            {
                throw "Error! Variable not declared!";
            }
        }
        else
        {
            processed_expression += raw_str[i];
        }
    }
    return processed_expression;
}


//already know token1 is either a num OR a variable of type int
template<>
int eval_expression<int>(std::deque<std::string> expression)
{
    std::string op;
    std::string token1 = expression.at(expression.size()-1); //the last token in the expression
    expression.pop_back();
    if (token1 == ")")
    {
        //std::cout << "found paren\n";
        std::deque<std::string> unprocessed;
        int nest = 1;
        while (true) //until expression is ( and nest is 0
        {
            if (expression.at(expression.size()-1) == ")")
            {
                nest++;
            }
            else if (expression.at(expression.size()-1) == "(")
            {
                //std::cout << "found end\n";
                nest--;
                if (nest == 0)
                {
                    expression.pop_back(); //removes the (
                    break;
                }
            }
            unprocessed.push_front(expression.at(expression.size()-1));
            expression.pop_back();
        }
        //now unprocessed contains everything in parentheses
        //next token SHOULD be an operator OR nothing (reached end of parsing)
        if (expression.size() == 0) //nothing past the (
        {
            return eval_expression<int>(unprocessed);
        }
        //otherwise next MUST be an operator
        op = expression.at(expression.size()-1);
        expression.pop_back();
        return operate(eval_expression<int>(expression), eval_expression<int>(unprocessed), op);
    }
    
    int real_tk1;
    
    if (is_num(token1))
    {
        real_tk1 = convert_string_to_int(token1);
    }
    else if (is_var_int(token1))
    {
        real_tk1 = convert_string_to_int(var_ints[token1]);
    }
    
    if (expression.size() == 0) return real_tk1;
    //otherwise the next token must be an operator!
    op = expression.at(expression.size()-1);
    expression.pop_back();
    return operate(eval_expression<int>(expression), real_tk1, op);
}

result do_eval(std::deque<std::string> expression)
{
    result r;
    if (expression.at(0).at(0) == '"')
    {
        r.type = 1;
        r.str = eval_expression<std::string>(expression);
    }
    else
    {
        r.type = 0;
        r.integer = eval_expression<int>(expression);
    }
    return r;
}
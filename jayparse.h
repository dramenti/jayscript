#include<deque>
#include<string>
#ifndef JAYPARSE_H
#define JAYPARSE_H


struct result
{
    std::string str;
    int type;
    int integer;
};

/*returns a op b where op is an infix operator*/
int operate(int a, int b, char op);

/*Evaluates the expression, whether it is a string or an integer*/
template<class T>
T eval_expression(std::deque<std::string> expression);

template<>
std::string eval_expression<std::string>(std::deque<std::string> expression);

template<>
int eval_expression<int>(std::deque<std::string> expression);


/*Determines how to call eval_expression: T=int or T=string */
result do_eval(std::deque<std::string> expression);

#endif

#include "operators.h"
/*This contains all the operators as functions, as well as 
the operator map that maps strings to their corresponding
function, like '+' to the 'add' function*/

/*For now, all operators are binary and infix*/

int add (int a, int b)
{
    return a+b;
}
int subtract (int a, int b)
{
    return a-b;
}
int divide (int a, int b)
{
    return a/b;
}
int multiply (int a, int b)
{
    return a*b;
}
int modulo (int a, int b)
{
    return a%b;
}
int less_than (int a, int b)
{
    return a<b;
}
int less_than_or_equal_to (int a, int b)
{
    return a<=b;
}
int greater_than (int a, int b)
{
    return a>b;
}
int greater_than_or_equal_to (int a, int b)
{
    return a>=b;
}
int equal_to (int a, int b)
{
    return a==b;
}
int not_equal_to (int a, int b)
{
    return a!=b;
}
int and_op (int a, int b)
{
    return a&&b;
}
int or_op (int a, int b)
{
    return a||b;
}

void initialize_operator_map()
{
    function_map["+"] = add;
    function_map["-"] = subtract;
    function_map["*"] = multiply;
    function_map["/"] = divide;
    function_map["%"] = modulo;
    function_map["<"] = less_than;
    function_map["<="] = less_than_or_equal_to;
    function_map[">"] = greater_than;
    function_map[">="] = greater_than_or_equal_to;
    function_map["!="] = not_equal_to;
    function_map["=="] = equal_to;
    function_map["AND"] = and_op;
    function_map["OR"] = or_op;
}
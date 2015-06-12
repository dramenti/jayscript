#include<map>
#include<string>
#ifndef OPERATORS_H
#define OPERATORS_H
/*This contains all the operators as functions, as well as 
the operator map that maps strings to their corresponding
function, like '+' to the 'add' function*/

/*For now, all operators are binary and infix*/

typedef int binary_infix_function(int a, int b);
typedef std::map<std::string, binary_infix_function*> binary_fmap;
extern binary_fmap function_map;

int add (int a, int b);
int subtract (int a, int b);
int divide (int a, int b);
int multiply (int a, int b);
int modulo (int a, int b);
int less_than (int a, int b);
int less_than_or_equal_to (int a, int b);
int greater_than (int a, int b);
int greater_than_or_equal_to (int a, int b);
int equal_to (int a, int b);
int not_equal_to (int a, int b);
int and_op (int a, int b);
int or_op (int a, int b);

void initialize_operator_map();
#endif
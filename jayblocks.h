#include<vector>
#include<string>
#ifndef JAYBLOCKS_H
#define JAYBLOCKS_H

struct CodeBlock
{
    int begin_line;
    int end_line;
    bool exists;
};

struct If_Flow
{
    int nestlevel;
    CodeBlock If_Block;
    std::string IB_exp;
    
    std::vector<CodeBlock> Elsif_Blocks;
    std::vector<std::string> EIB_exps;
    
    CodeBlock Else_Block;
    
    int line_of_END;
};




#endif
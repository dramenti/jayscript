#include<vector>
#include<string>
#ifndef JAYBLOCKS_H
#define JAYBLOCKS_H

struct CodeBlock
{
    unsigned begin_line;
    unsigned end_line;
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
    
    unsigned line_of_END;
};

struct While_Flow
{
    int nestlevel;
    CodeBlock While_Block;
    std::string WB_exp;
    
    unsigned line_of_END;
};



#endif
So basically this is Jayscript, a scripting language I made.
It is in the very early stages, and cannot do much yet.

Note that this is a personal project, intended as a learning experience for myself, not for practical use!
Though perhaps someday in the future this will become more practical.

So far, it can: 
tokenize expressions (jaylexer.cpp)

parse basic strings and evaluate arithmetic expressions (jayparse.cpp)

understand a limited array of commands (jaycommand.cpp)


So far, only strings and integers are supported as data types.

Also, order of operations is not supported. You have to use parentheses for now.

For example, you can't do x < 3 AND y < 5, as of now, you have to do 

(x < 3) AND (y < 5)

Commands supported as of now, with syntax:

SET [variable_name] [value] where value can be either an integer or string

PRINT [string]

Example code:

SET x 50    

SET y x+(3*2)

PRINT "The value of y is %y%"


When run, the output is:

The value of y is 56

Note that there are still a bunch of std::cout lines for debug, 
so the output will include a bunch of debug stuff.


TO DO:

-Implement control flow, keywords: IF, ELSE IF, WHILE, END

-Implement comments

-Implement functions, keyword: FUNCTION

-Implement order of operations



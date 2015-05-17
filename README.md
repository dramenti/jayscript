So basically this is Jayscript, a scripting language I made.
It is in the very early stages, and cannot do much yet.

So far, it can: 
tokenize expressions (jaylexer.cpp)

parse basic strings and evaluate arithmetic expressions (jayparse.cpp)

understand a limited array of commands (jaycommand.cpp)


So far, only strings and integers are supported as data types.

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

-------------------------PROJECT JAYSCRIPT------------------------------

-------------------------Dramenti (Jayanth Sundaresan)------------------

So basically this is Jayscript, an interpreted scripting language I made. The interpreter is written in C++.

Note that this is a personal project, intended as a learning experience for myself, not for practical use!
Though perhaps someday in the future this will become more practical.

So far, it can: 
tokenize expressions (jaylexer.cpp)

parse basic strings and evaluate arithmetic expressions (jayparse.cpp)

understand a limited number of commands (jaycommand.cpp)


So far, only strings and integers are supported as data types.

Also, order of operations is not supported. You have to use parentheses for now.

For example, you can't do x < 3 AND y < 5, as of now, you have to do 

(x < 3) AND (y < 5)

Commands supported as of now, with syntax:

SET [variable_name] = [value] where value can be either an integer or string

PRINT [string]

INPUT [variable_name] NOTE: as of now, strings typed in need to be in quotes because INPUT evaluates the expression entered

IF [condition]

    do stuff (indentation dependent!)

optional:

ELSIF [condition]

    do stuff
    
...

ELSE

    do stuff
    
END

note: if-elsif-else blocks must end in END!

WHILE [condition]
    do stuff
END

Example code:

SET x = 50    

SET y = x+(3*2)

PRINT "The value of y is %y%"


When run, the output is:

The value of y is 56


TO DO:

-Implement comments

-Implement functions, keyword: FUNCTION

-Implement arrays

-Implement order of operations



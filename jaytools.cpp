#include "globals.h"
#include<string>
#include<exception>
#include "jaytools.h"
#define ASCII_SHIFT 48

//48 to 57 inclusive is the range of digits in ASCII
bool is_num(std::string s)
{
    int i = 0;
    if (s.at(i) == '-' && s.size() > 1) i++;
    int first_char = (int)s.at(i);
    if (first_char >= 48 && first_char <= 57) //check if is a digit
    {
        return true;
    }
    return false; //not a digit
}

bool is_var_int(std::string s)
{
    if (var_ints.count(s))
    {
        return true;
    }
    return false; //not in map
}

bool is_var_string(std::string s)
{
    if (var_strings.count(s))
    {
        return true;
    }
    return false;
}

int convert_string_to_int(std::string s)
{
    int converted = 0; //will contain the final integer representation of s
    int size = s.size();
    int multiplier = 1; //goes up by factor of 10 every time
    int dig; //stores each character, which is a digit
    int endpoint = 0;
    int negativizer = 1;
    if (s.at(0) == '-') //deals with negative numbers
    {
        endpoint = 1;
        negativizer = -1;
    }
    for (int i = size-1; i >= endpoint; i--)
    {
        dig = (int)s.at(i)-ASCII_SHIFT;
        converted += dig*multiplier;
        multiplier *= 10;
    }
    return (converted*negativizer);
}

std::string convert_int_to_string(int num)
{
    if (num == 0) return "0";
    std::string str_int;
    if (num < 0)
    {
        str_int = "-"; //dat negative sign tho
        num *= -1;
    }
    else
    {
        str_int = "";
    }
    //at this point, num contains a positive integer
    int divider = 1;
    while (num/divider > 0)
    {
        divider *= 10;
    }
    divider /= 10; //when while loop breaks, divider will be too big, go back to last "good run"
    int next_digit;
    //digit stripper
    while (divider >= 1)
    {
        next_digit = num/divider;
        str_int += (char)(next_digit+ASCII_SHIFT);
        num = num-divider*next_digit;
        divider /= 10;
    }
    return str_int;
}

bool is_OpChar(char c)
{
    switch(c)
    {
        case '+':
            return true;
            break;
        case '-':
            return true;
            break;
        case '*':
            return true;
            break;
        case '/':
            return true;
            break;
        case '%':
            return true;
            break;
        case '=':
            return true;
            break;
        case '<':
            return true;
            break;
        case '>':
            return true;
            break;
        case '!':
            return true;
            break;
        default:
            return false;
            break;
    }
}

bool in_int_range(int x)
{
    return (x >= 48 && x <= 57);
}

bool in_upcase_range(int x)
{
    return (x >= 65 && x <= 90);
}

bool in_lowcase_range(int x)
{
    return (x >= 97 && x <= 122);
}

//unicode [48, 57]U[65,90]U[97, 122]
bool is_IdentifierChar(char c)
{
    int ic = (int)c;
    if (in_int_range(ic) || in_upcase_range(ic) || in_lowcase_range(ic))
    {
        return true;
    }
    return false;
}

bool is_Valid_Identifier(std::string id)
{
    int ids = id.size(); //size of potential identifier
    int c1 = (int)(id.at(0)); //used to check if starts with digit
    //if c1 is a digit, return false: cannot start with a digit
    if (in_int_range(c1)) //if is int, return false
    {
        return false;
    }
    //else, check all of chars... if all chars are id chars, return true
    int index = 0;
    while (index < id.size())
    {
        if (!is_IdentifierChar(id.at(index)))
        {
            return false;
        }
        index++;
    }
    return true;
}

void trim_tail(std::string& s)
{
    int index = s.size()-1;
    while (index >= 0)
    {
        if (s.at(index) == ' ' || s.at(index) == '\t')
        {
            index--;
        }
        else
        {
            break;
        }
    }
    //loop has broken: index is now location of last nonspace character
    //the substring from 0 to index is our final result
    //substring argument is (0, length) 
    //length = index+1
    s = s.substr(0, index+1);
}

//returns whether the line begins with lvl number of tabs or soft tabs
bool begins_with_tab(const std::string& s, int lvl)
{
    const std::string SOFT = "    "; //FOUR SPACES AKA SOFT TAB
    const char HARD = '\t'; //TABSPACE
    try
    {
        bool yesbegin = false; 
        int k = 0;
        while (k < lvl)
        {
            yesbegin = true; //so far it looks ok...
            if (s.at(k) != HARD) //not a hard tab...
            {
                yesbegin = false;  //so false for now
                break; //exit
            }
            k++;
        }
        if (yesbegin) return yesbegin; //if we didn't break, return true
        
        //now do soft check
        k = 0;
        while (k < lvl)
        {
            yesbegin = true;
            if (s.substr(4*k, 4) != SOFT)
            {
                yesbegin = false;
                break;
            }
            k++;
        }
        return yesbegin;
    }
    catch (std::exception& e)
    {
        return false;
    }
}
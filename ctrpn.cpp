//convert string to reverse polish notation
//with logical operands
// renewal by Zorkin Andrey a.k.a @a1ndreay Added partial support for logical operators 21/03/2024
//перевод строкового выражения в ОПЗ, учитывая логические операторы

#include "lFunctions.h"

//конвертирует некоторые знаки из строки на эквивалентные выражения
std::string toNormalForm(std::string &sourceString)
{
    std::string tempString = "";
    for (auto x : sourceString) 
    {
        switch(x)
        {
            case '!':
            tempString += "not";
            break;
            case '+':
            tempString += "or";
            break;
            case '~':
            tempString += "impl";
            break;
            case '*':
            tempString += "and";
            break;
            default:
                tempString += x;
				break;
        }
    }
    return tempString;
}
 
// создаёт обратную польскую запись из строки
std::string RPN(std::string str)
{
    std::string srpn;
 
    std::string::size_type ind;
    while ((ind = str.find(' ')) != std::string::npos) // удаление пробелов из входной строки
    {
        str.erase(ind, 1);
    }
    /*
    for (int i = 0; i < str.size(); ++i) // учёт отрицательных чисел
    {
        if ((str[i] == '+' || str[i] == '-') && (0 == i || (!isalnum(str[i - 1]) && str[i - 1] != '.' && str[i - 1] != ')')))
        {
            auto it = std::find_if(str.begin() + i + 1, str.end(), [](char const c) {return !isalnum(c);});
            str.insert(it, ')');
            str.insert(i, "(0");
            int nnn = 0;
        }
    }
    */
 
    std::map<char, size_t> map; // карта весов символов
    map.insert(std::make_pair('!', 4)); // slash '¬'
    map.insert(std::make_pair('*', 3)); //*
    map.insert(std::make_pair('+', 2)); //+ 'v'
    map.insert(std::make_pair('~', 2)); //- '→'
    map.insert(std::make_pair('=', 2)); //= '↔'
    map.insert(std::make_pair('(', 1));
    std::stack<char> stack;
    for (auto c : str) // формировка результирующей строки в ОПЗ
    {
        if (!iswascii(c)) {
            throw "Log.RPN current symbol not supported!";
        }
            
        if (!isalnum(c) && ('.' != c))
        {
            if(srpn.length()!=0)
            srpn += ' ';
            if (')' == c)
            {
                while (stack.top() != '(')
                {
                    srpn += stack.top();
                    stack.pop();
                    srpn += ' ';
                }
                stack.pop();
            }
            else if ('(' == c)
            {
                stack.push(c);
            }
            else if (stack.empty() || (map[stack.top()] < map[c]))
            {
                stack.push(c);
            }
            else
            {
                do
                {
                    srpn += stack.top();
                    srpn += ' ';
                    stack.pop();
                } while (!(stack.empty() || (map[stack.top()] < map[c])));
                stack.push(c);
            }
        }
        else
        {
            srpn += c;
        }
    }
    while (!stack.empty())// остаток из стека добавляется в результ. строку
    {
        srpn += stack.top();
        srpn += ' ';
        stack.pop();
    }
    return srpn;
}
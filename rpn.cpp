// Reverse Polish notation demo
// Basic calulator for RPN expressions.
// Allows calulation of doubles
// includes many math functions
// Allows simple variables using single letters A-Z
// Allows easy printing of results using print and cr for newlines
// By Ben a.k.a DreamVB (dreamvb@outlook.com) 22:23 18/04/2021
// By Zorkin Andrey a.k.a @a1ndreay Added partial support for logical operators 21/03/2024
// P.S. Зорькин Андрей @a1ndreay добавлена частичная поддержка логических операторов 21/03/2024

#define MAX_STACK 2048
#define PI 3.14159265359
#define _CRT_SECURE_NO_WARNINGS

#include "lFunctions.h"

using namespace std;
using std::cout;
using std::endl;

enum Instructions
{
	_UNKNOWN = 0,
	_PRINT,
	_CR,
	_CB,
	_CBRT,
	_SIN,
	_COS,
	_SQRRT,
	_SQ,
	_TAN,
	_LOG,
	_ABS,
	_EXP,
	_MOD,
	_MAX,
	_MIN,
	_CEIL,
	_FLOOR,
	_ROUND,
	_SWAP,
	_DUP,
	_AND,
	_OR,
	_XOR,
	_PI,
	_NOT,
	_IMPL
};

double _stack[MAX_STACK];
double _vars[25] = { 0.0 };
int tos = 0;

bool Full(){
	return (tos >= MAX_STACK - 1);
}

bool Empty(){
	return (tos == 0);
}

void Push(double value){
	if (Full()){
		throw std::runtime_error("Stack Is Full.");
	}
	else{
		tos++;
		_stack[tos] = value;
	}
}

double Pop(){
	double t = _stack[tos];
	tos--;
	return t;
}

double Peek(){
	return _stack[tos];
}

void _free_stack(){
	memset(_stack, 0, sizeof _stack);
}

//Enf of stack code

bool IsOp(char c){
	//Check for operators.
	switch (c){
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '<':
		case '>':
		case '=':
			return true;
		default:
			return false;
	}
}

double _max(double a, double b){
	if (a > b){
		return a;
	}
	return b;
}

double _min(double a, double b){
	if (a < b){
		return a;
	}
	return b;
}

double _cube(double n){
	//Calc cube
	return (n *n * n);
}

bool _isNumber(char c){
	return isdigit(c) | c == '.';
}

void set_var(char index, double value){
	char ch = toupper(index);
	int id = (ch - 'A');

	//Check if within bounds of variable index.
	if (id < 0 || id > 65){
		throw std::runtime_error("Variable Index Out Of Range.");
		return;
	}
	else{
		//Set variable value.
		_vars[id] = value;
	}
}

double get_var(char index){
	char ch = toupper(index);
	int id = (ch - 'A');
	//Check if within bounds of variable index.
	if (id < 0 || id > 65){
		throw std::runtime_error("Variable Index Out Of Range.");
		return 0.0;
	}
	else{
		//Return variable data
		return _vars[id];
	}
}

Instructions _getInstructionsCode(std::string src){
	std::string tmp = src;
	Instructions t = _UNKNOWN;
	//Convert token to lowercase.
	std::transform(tmp.begin(), tmp.end(), tmp.begin(),
		[](unsigned char c){ return std::tolower(c); });
	//Check for Instruction

	if (tmp == "print"){
		t = _PRINT;
	}
	else if (tmp == "cr"){
		t = _CR;
	}
	else if (tmp == "cb"){
		t = _CB;
	}
	else if (tmp == "cbrt"){
		t = _CBRT;
	}
	else if (tmp == "sin"){
		t = _SIN;
	}
	else if (tmp == "cos"){
		t = _COS;
	}
	else if (tmp == "sqrt"){
		t = _SQRRT;
	}
	else if (tmp == "sq"){
		t = _SQ;
	}
	else if (tmp == "tan"){
		t = _TAN;
	}
	else if (tmp == "log"){
		t = _LOG;
	}
	else if (tmp == "abs"){
		t = _ABS;
	}
	else if (tmp == "exp"){
		t = _EXP;
	}
	else if (tmp == "mod"){
		t = _MOD;
	}
	else if (tmp == "max"){
		t = _MAX;
	}
	else if (tmp == "min"){
		t = _MIN;
	}
	else if (tmp == "ceil"){
		t = _CEIL;
	}
	else if (tmp == "floor"){
		t = _FLOOR;
	}
	else if (tmp == "round"){
		t = _ROUND;
	}
	else if (tmp == "pi"){
		t = _PI;
	}
	else if (tmp == "dup"){
		t = _DUP;
	}
	else if (tmp == "and"){
		t = _AND;
	}
	else if (tmp == "or"){
		t = _OR;
	}
	else if (tmp == "xor"){
		t = _XOR;
	}
	else if (tmp == "swap"){
		t = _SWAP;
	}
	else if (tmp == "not"){
		t = _NOT;
	}
	else if (tmp == "impl"){
		t = _IMPL;
	}
	else{
		t = _UNKNOWN;
	}
	return t;
}

void _free_vars(){
	memset(_vars, 0, sizeof _vars);
}

bool RpnCalc(std::string expression){
	bool answer = 0;
	size_t i = 0;
	double v1 = 0.0;
	double v2 = 0.0;
	double ret = 0.0;
	double tmp = 0.0;
	std::string tok;
	char op = '\0';

	while (i < expression.length()-1){
		//Skip white space
		while (isspace(expression[i])){
			i++;
		}
		//Check for digits and .
		if (_isNumber(expression[i])){
			while (_isNumber(expression[i])){
				tok += expression[i];
				i++;
			}
			//Push on stack number.
			Push(atof(tok.c_str()));
			//Clear token
			tok.clear();
		}//Check for alpha
		else if (isalpha(expression[i]))
		{
			while (isalpha(expression[i])){
				//Build the token
				tok += expression[i];
				i++;
			}
			//
			switch (_getInstructionsCode(tok))
			{
				case _UNKNOWN:
					if (tok.length() == 1 && isalpha(tok[0])){
						//Get variable data.
						Push(get_var(tok[0]));
					}
					else{
						throw ("Unknown Token Found.");
						return false;
					}
					break;
				case _PRINT:
					//Output the top of the stack to the console.
					answer = Pop();
					break;
				case _CR:
					//Add carrige return.
					std::cout << std::endl;
					break;
				case _CB:
					Push(_cube(Pop()));
					break;
				case _CBRT:
					Push(std::cbrt(Pop()));
					break;
				case _SIN:
					Push(sin(Pop()));
					break;
				case _COS:
					Push(cos(Pop()));
					break;
				case _SQRRT:
					Push(sqrt(Pop()));
					break;
				case _SQ:
					Push(pow(Pop(), 2.0));
					break;
				case _TAN:
					Push(tan(Pop()));
					break;
				case _LOG:
					Push(log10(Pop()));
					break;
				case _ABS:
					Push(fabs(Pop()));
					break;
				case _EXP:
					Push(exp(Pop()));
					break;
				case _MOD:
					v1 = Pop();
					v2 = Pop();
					ret = (int)((int)v2 % (int)v1);
					//Push the result.
					Push(ret);
					break;
				case _MAX:
					v1 = Pop();
					v2 = Pop();
					ret = _max(v2, v1);
					//Push result
					Push(ret);
					break;
				case _MIN:
					v1 = Pop();
					v2 = Pop();
					ret = _min(v2, v1);
					//Push result
					Push(ret);
					break;
				case _CEIL:
					Push(ceil(Pop()));
					break;
				case _FLOOR:
					Push(floor(Pop()));
					break;
				case _ROUND:
					Push(round(Pop() + 0.5));
					break;
				case _PI:
					Push(PI);
					break;
				case _DUP:
					Push(Peek());
					break;
				case _AND:
					v1 = Pop();
					v2 = Pop();
					ret = (int)((int)v1 & (int)v2);
					Push(ret);
					break;
				case _OR:
					v1 = Pop();
					v2 = Pop();
					ret = (int)((int)v1 | (int)v2);
					Push(ret);
					break;
				case _XOR:
					v1 = Pop();
					v2 = Pop();
					ret = (int)((int)v1 ^ (int)v2);
					Push(ret);
					break;
				case _SWAP:
					v1 = Pop();
					v2 = Pop();
					tmp = v2;
					v2 = v1;
					v1 = tmp;
					//Push values on stack.
					Push(v2);
					Push(v1);
					break;
				case _NOT:
					v1 = Pop();
					if(v1)Push(v1*0);
					else Push(1);
					break;
				case _IMPL:
					v1 = Pop();
					v2 = Pop();
					if((int)v2 == 1 && (int)v1 == 0) Push(0);
					else Push(1);
					break;
				default:
					throw std::runtime_error("Unknown Token Found.");
					break;
			}
			//Clear token.
			tok.clear();
		}
		//Check for operator
		else if (IsOp(expression[i])){
			//Set operator
			op = expression[i];
			//Execure operators
			switch (op)
			{
			case '+':
				v1 = Pop();
				v2 = Pop();
				ret = (v2 + v1);
				//Push result on stack.
				Push(ret);
				break;
			case '-':
				v1 = Pop();
				v2 = Pop();
				ret = (v2 - v1);
				//Push result on stack.
				Push(ret);
				break;
			case '*':
				v1 = Pop();
				v2 = Pop();
				ret = (v2 * v1);
				//Push result on stack.
				Push(ret);
				break;
			case '/':
				v1 = Pop();
				v2 = Pop();
				//Check for division by zero.
				if (v1 == 0){

					throw std::runtime_error("Division By Zero.");
					break;
				}
				ret = (v2 / v1);
				//Push result on stack.
				Push(ret);
				break;
			case '%':
				v1 = Pop();
				v2 = Pop();
				ret = fmod(v2, v1);
				Push(ret);
				break;
			case '<':
				v1 = Pop();
				v2 = Pop();
				ret = (v2 < v1);
				//Push result on stack.
				Push(ret);
				break;
			case '>':
				v1 = Pop();
				v2 = Pop();
				ret = (v2 > v1);
				//Push result on stack.
				Push(ret);
				break;
			case '=':
				v1 = Pop();
				v2 = Pop();
				ret = (v2 == v1);
				//Push result on stack.
				Push(ret);
				break;
			default:
				break;
			}
			//INC Counter
			i++;
			//Push result onto stack
		}
		else{
			throw ("Unknown Token Found.");
			break;
		}
	}
	//Free stack
	answer = Pop();
	_free_stack();
	
	return answer;
}

/*
int main(int argc, char *argv[]){
	//Set variables
	set_var('E', 2.71828182845905);
	set_var('A', 4);
	set_var('B', 12);
	std::cout.precision(12);
	//Examples
	RpnCalc("pi print cr");
	RpnCalc("A B 3 + * 2 / 5 5 + * 100 2 * - 2 / print cr");
	RpnCalc("pi 10 dup  * * print cr");
	RpnCalc("a b + print cr");
	RpnCalc("5 1 2 + 4 * + 3 - print cr");
	RpnCalc("10 20 swap - print cr");
	RpnCalc("10 12 xor print cr");
	RpnCalc("100 150 min print cr");
	RpnCalc("100 log print cr");
	RpnCalc("e dup + print cr");
	RpnCalc("3.3 sqrt pi * print cr");
	RpnCalc("2.5 2 % print cr");
	RpnCalc("3 sq print cr");
	RpnCalc("2 exp round print cr");
	RpnCalc("2 cbrt print cr");
	RpnCalc("2 cb print cr");
	//Free eveything.
	_free_vars();

	system("pause");
	return EXIT_SUCCESS;
}
*/
#pragma once
#include <iostream>
#include <stack>
#include <cctype>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <conio.h>

//ctrpn namespace functions
std::string toNormalForm(std::string& sourceString);
std::string RPN(std::string str);

//rpn namespace functions
std::string RPN(std::string str);
bool Full();
bool Empty();
void Push(double value);

double Pop();

double Peek();

void _free_stack();

bool IsOp(char c);

double _max(double a, double b);

double _min(double a, double b);

double _cube(double n);

bool _isNumber(char c);

void set_var(char index, double value);

double get_var(char index);

void _free_vars();

bool RpnCalc(std::string expression);

//lFunctions namespace functions
std::string btos(bool x);

std::string makeSKNF(std::map<char, std::vector<bool>> sourcePropositionalChar, std::vector<char> PropositionalCharCollection);

std::string makeSDNF(std::map<char, std::vector<bool>> sourcePropositionalChar, std::vector<char> PropositionalCharCollection);

std::string variableReplace(std::string convertedToReversePilishString, std::map<char, std::vector<bool>> sourcePropositionalChar, int iteration);

void fillTable(std::string convertedToReversePilishString, std::map<char, std::vector<bool>>& sourcePropositionalChar, const int PropositionalCharRank);

bool unpack(std::string const sourceString, std::map<char, std::vector<bool>>& sourcePropositionalChar, std::vector<char>& PropositionalCharCollection, int& sourceTableRank);

void forceUnpack(std::vector<int> _functionValues, std::map<char, std::vector<bool>>& sourcePropositionalChar);

void helpAnnotation();
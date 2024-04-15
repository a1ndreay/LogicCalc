// perfect conjunctive normal form demo
// Basic calulator for logic expressions.
// includes many logical and math functions
// Allows simple variables using single letters A-Z
// By Andrey Zorkin a.k.a @a1ndreay (a1handreay@gmail.com) 17:29 21/03/2024

#include "lFunctions.h"

using namespace std;

//convert boolean value to string
//перевод булевой переменной в строковую
string btos(bool x)
{
    if (x)
        return "1";
    return "0";
}

//generation PCNF string via prepared truth table
//по заполненной таблице истинности генерируем СКНФ
string makeSKNF(map<char, vector<bool>> sourcePropositionalChar, vector<char> PropositionalCharCollection)
{
    int PropositionalCharRank = pow(2, PropositionalCharCollection.size());
    string currentAnswer;
    for (int i = 0; i < PropositionalCharRank; i++)
    {
        if (sourcePropositionalChar['~'][i] == NULL)
        {
            if (i > 0 && currentAnswer.length() > 0) currentAnswer += "&";
            string tempResult = "(";
            for (int j = 0; j < PropositionalCharCollection.size(); j++)
            {
                if (sourcePropositionalChar[(char)(PropositionalCharCollection[j])][i] == NULL)
                {
                    tempResult += PropositionalCharCollection[j];
                }
                else
                {
                    tempResult += "!"; tempResult += PropositionalCharCollection[j];
                }
                if (j < PropositionalCharCollection.size() - 1)
                    tempResult += "v";
            }
            tempResult += ")";
            currentAnswer += tempResult;
        }
    }
    if (currentAnswer.size() == 0) { throw "FORM NOT EXIST!"; }
    return currentAnswer;
}
string makeSDNF(map<char, vector<bool>> sourcePropositionalChar, vector<char> PropositionalCharCollection)
{
    int PropositionalCharRank = pow(2, PropositionalCharCollection.size());
    string currentAnswer;
    for (int i = 0; i < PropositionalCharRank; i++)
    {
        if (sourcePropositionalChar['~'][i] != NULL)
        {
            if (i > 0 && currentAnswer.length() > 0) currentAnswer += "v";
            string tempResult = "(";
            for (int j = 0; j < PropositionalCharCollection.size(); j++)
            {
                if (sourcePropositionalChar[(char)(PropositionalCharCollection[j])][i] != NULL)
                {
                    tempResult += PropositionalCharCollection[j];
                }
                else
                {
                    tempResult += "!"; tempResult += PropositionalCharCollection[j];
                }
                if (j < PropositionalCharCollection.size() - 1)
                    tempResult += "&";
            }
            tempResult += ")";
            currentAnswer += tempResult;
        }
    }
    if (currentAnswer.size() == 0) { throw "FORM NOT EXIST!"; }
    return currentAnswer;
}

//Replace string variable onto current boolean value
//для конкретной строки таблицы истинности меняем пропозиционные символы на соответствующее значение из ьаблицы истинности
string variableReplace(string convertedToReversePilishString,const map<char, vector<bool>> sourcePropositionalChar, int iteration)
{
    for (string::const_iterator iter = convertedToReversePilishString.begin(); iter != convertedToReversePilishString.end(); ++iter)
    {
        if (sourcePropositionalChar.find(*iter) != sourcePropositionalChar.end()) { convertedToReversePilishString.replace(iter, iter + 1, btos(sourcePropositionalChar.at(*iter)[iteration])); }
    }
    return convertedToReversePilishString;
}

//Fill answer column
//заполняем столбец ответов таблицы истинности
//На вход поступает нормализованная форма обратной польской нотации
void fillTable(string convertedToReversePilishString, map<char, vector<bool>>& sourcePropositionalChar, const int SourceTableRank)
{
    cout << "Log.FillTable Заполняем таблицу..." << endl;
    for (int i = 0; i < SourceTableRank; i++)
    {
        //заменяем в выражении все пропозициональные буквы на их соответствующие значения из таблицы истинности для данной строки
        string tempStr = variableReplace(convertedToReversePilishString, sourcePropositionalChar, i);
        //значение полученной строки вычилим в модуле калькулятора, вкключающего парсинг
        sourcePropositionalChar['~'].push_back(RpnCalc(tempStr)); //RpnCalc может работать некорректно с парметром PRINT т.к.я поменял механизм восвобождения стека, крч ничего кроме строки туда не засовывать
        cout << "Expression${" << tempStr << "} Equal to " << RpnCalc(tempStr) << endl;
    }
    cout << "Log.FillTable Заполнение таблицы успешно" << endl;
}

//Generate truth table taking into account the source string
//упаковывает таблицу истинности варьируя булевыми функциями
bool unpack(string const sourceString, map<char, vector<bool>>& sourcePropositionalChar, vector<char>& PropositionalCharCollection, int& sourceTableRank)
{
    PropositionalCharCollection.clear();
    map<char, int> ALPHABET = { {'A',1},{'B',1},{'C',1},{'D',1},{'E',1},{'F',1},{'G',1}, {'a',1}, {'b',1}, {'c',1}, {'d',1}, {'e',1}, {'f',1}, {'g',1} };
    queue<char> currentPropQueue;
    for (string::const_iterator iter = sourceString.begin(); iter != sourceString.end(); iter++)
    {
        if (ALPHABET[*iter] == 1) {ALPHABET[*iter]--; PropositionalCharCollection.push_back(*iter); }
    }
    std::sort(PropositionalCharCollection.begin(), PropositionalCharCollection.end());
    for (int i = 0; i < PropositionalCharCollection.size(); i++) { currentPropQueue.push(PropositionalCharCollection[i]); }
    if (PropositionalCharCollection.size() == 0) { throw "there are no available propositional characters in the source string!"; return false; }
    int numRows = pow(2, currentPropQueue.size());
    int const CurrentPropQueueSize = currentPropQueue.size();
    sourceTableRank = numRows;
    int step = numRows / 2;
    for (int i = 0; i < CurrentPropQueueSize; i++)
    {
        char currentSymbol = currentPropQueue.front();
        for (int k = 0; k < numRows / (step * 2); k++)
        {
            for (int j = 0; j < (step); j++)
            {
                sourcePropositionalChar[currentSymbol].push_back(NULL);
            }
            for (int j = 0; j < (step); j++)
            {
                sourcePropositionalChar[currentSymbol].push_back(true);
            }
        }
        step /= 2;
        currentPropQueue.pop();
    }
    if (currentPropQueue.size() == 0)  return true;
    else { throw "not all characters were processed correctly"; return false; }
};

//составим таблицу истинности по вектору ответов функции
void forceUnpack(vector<int> _functionValues, map<char, vector<bool>>& sourcePropositionalChar)
{
    char dictionary[] = { 'a','b','c','d','x','y','z'};
    int PropositionalCharRank = _functionValues.size();
    int sourcePropositionalCharSize = log2((double)PropositionalCharRank);
    int step = PropositionalCharRank / 2;
    for (int i = 0; i < sourcePropositionalCharSize; i++)
    {
        char currentSymbol = dictionary[i];
        for (int k = 0; k < PropositionalCharRank / (step * 2); k++)
        {
            for (int j = 0; j < (step); j++)
            {
                sourcePropositionalChar[currentSymbol].push_back(NULL);
            }
            for (int j = 0; j < (step); j++)
            {
                sourcePropositionalChar[currentSymbol].push_back(true);
            }
        }
        step /= 2;
    }
    for (int i = 0; i < PropositionalCharRank; i++)
    {
        sourcePropositionalChar['~'].push_back(_functionValues[i]);
        //cout << tempStr << " | " << sourcePropositionalChar['#'][i]; //дополнительный вектор на ответы
    }
}

void helpAnnotation()
{
    cout << "Построение таблицы истинности и совершенных форм по формуле алгебры логики!" << endl;
    cout << "Разрешено использовать следующие знаки: ! (отрицание), * (логическое и), + (логическое или), ~ (логическое следование),  = (эквивалентность)" << endl;
    cout << "Записывать без пробелов! Использовать Заглавные пропозициональные буквы" << endl;
    cout << "Пример ввода: (C+B=A)+(C+!B=!A)" << endl;
    cout << "> ";
}
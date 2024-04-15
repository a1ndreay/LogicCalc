// Basic calculator for logic expressions.
// includes many logical and math functions
// Allows simple variables using single letters A-Z
// By Andrey Zorkin a.k.a @a1ndreay (a1handreay@gmail.com) 17:29 21/03/2024

#include "lFunctions.h"

using namespace std;

int main()
{
    map<char, vector<bool>> PropositionalChar; //таблица истинности 
    vector<char> PropositionalCharCollection; //таблица пропозициональных букв, используется как словарь для универсальной makeSKNF, и makeSDNF
    int TableRank = 0; //Количество строк таблицы истинности
    helpAnnotation();
    try
    {
        string Buf; //в качестве пропозициональных букв лучше использовать ПРОПИСНЫЕ буквы
        std::cout << "Введите выражение>"; cin >> Buf; //"(C+B=A)+(C+!B=!A)" "((A*B=A)~(A+B=B))=((C+B=A)+(C+!B=!A))"
        std::cout << "Введённое выражение: "; std::cout << Buf << endl;
        string Eval = RPN(Buf); //транслируем запись в обратную польскую нотацию, функция снабжена собственным словарём пропозициональных букв

        //далее "распакуем" выражение: проанализируем строку, определим какие пропозициональные буквы она содержит,
        //создадим первоначальную таблицу истинности, заполним нулями и единицами
        //колонки для пропозициональных букв, выделим столбец по ответы, вычислим сколько строк будет содержать таблица
        if(unpack(Eval, PropositionalChar, PropositionalCharCollection, TableRank)); 
        {
            vector<char> NotOnlyPropSymbols; //вектор предназначенный для отладочной информации и вывода

            //Заполним таблицу истинности: транслируем выражение из обратной польской нотации, заменяя неоднозначные пропозициональные символы на однозначные инструкции
            fillTable(toNormalForm(Eval), PropositionalChar, TableRank); 
            for (auto elem : PropositionalChar)
            {
                std::cout << elem.first << " ";
                NotOnlyPropSymbols.push_back(elem.first);
            }std::cout << endl;
            for (int i = 0; i < TableRank; i++)
            {
                for (int j = 0; j < PropositionalChar.size(); j++)
                {
                    std::cout << PropositionalChar[NotOnlyPropSymbols[j]].at(i) << " ";
                }std::cout << endl;
            }
            std::cout<<"СКНФ: "<<makeSKNF(PropositionalChar, PropositionalCharCollection) << endl;
            std::cout <<"СДНФ: " << makeSDNF(PropositionalChar, PropositionalCharCollection) << endl;
        }
    }
    catch(const char* error_message)
    {
        std::cout <<'\n' << error_message << '\n';
    }
    //try
    //{
    //    TableRank = 8;
    //    cout << "Введённый вектор значений функции: {0,1,1,0,0,0,0,1}" << endl;
    //    forceUnpack(vector<int> {0, 1, 1, 0, 0, 0, 0, 1}, PropositionalChar);//алгоритм упаковки, включающий только инициализацию таблицы истинности по вектору ответов
    //    {
    //        cout << "Сгенерированная таблица истинности:" << endl;
    //        vector<char> NotOnlyPropSymbols; //вектор предназначенный для отладочной информации и вывода
    //        for (auto elem : PropositionalChar)
    //        {
    //            cout << elem.first << " ";
    //            NotOnlyPropSymbols.push_back(elem.first);
    //        }cout << endl;
    //        for (int i = 0; i < TableRank; i++)
    //        {
    //            for (int j = 0; j < PropositionalChar.size(); j++)
    //            {
    //                cout << PropositionalChar[NotOnlyPropSymbols[j]].at(i) << " ";
    //            }cout << endl;
    //        }
    //        PropositionalCharCollection = { 'a','b','c'};
    //        cout <<"СКНФ: " << makeSKNF(PropositionalChar, PropositionalCharCollection) << endl;
    //        cout <<"СДНФ: " << makeSDNF(PropositionalChar, PropositionalCharCollection) << endl;
    //    }
    //}
    //catch (const char* error_message)
    //{
    //    cout << '\n' << error_message << '\n';
    //}
    getch();
    
    return 0;
}
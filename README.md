# Калькулятор формул алгебры логики

Данная программа служит для построения таблицы истинности формулы алгебры логики, а так же строит её совершенные формы, если они существуют.
Разрешено использовать следующие знаки: ! (отрицание), * (логическое и), + (логическое или), ~ (логическое следование),  = (эквивалентность)
Записывать **без пробелов**. Использовать **Заглавные** пропозициональные буквы
Пример ввода: `(C+B=A)+(C+!B=!A)`

## Пример работы программы
![image](https://github.com/a1ndreay/LogicCalc/assets/104272612/85d0bc95-10b6-4c60-b585-94c536489b57)


## Функции
`std::string RPN(std::string sourcrString);` Возвращает строку, содержащую логическое выражение вида (C+B=A)+(C+!B=!A) в обратную польскую запись

`bool unpack(std::string const sourceString, std::map<char, std::vector<bool>>& sourcePropositionalChar, std::vector<char>& PropositionalCharCollection, int& sourceTableRank);` анализирует строку , содержащую запись в обратной польской форме, заполняет столбцы пропозициональных букв в таблице истинности, результатом функции является подготовленная таблица истинности, словарь пропозициональных букв, количество строк в таблице истинности.

`std::string toNormalForm(std::string& sourceString);` нормализует строку содержащую обратную польскую запись, это необходимо, чтобы все математические знаки в строке были заменены на их явные инструкции

`void fillTable(std::string convertedToReversePilishString, std::map<char, std::vector<bool>>& sourcePropositionalChar, const int PropositionalCharRank);` принимает на вход строку, содержащую нормализованную форму обратной польской нотации, подготовленную таблицу истинности, количество строк таблицы истинности. Заполняет таблицу истинности.

`std::string makeSKNF(std::map<char, std::vector<bool>> sourcePropositionalChar, std::vector<char> PropositionalCharCollection);` Возвращает строку, содержащую соответствующую совершенную конъюктивную нормальную форму, на основе заполненной таблицы истинности и словаря пропозицональных букв. Если такой формы не существует, пробрасывает ошибку.

`std::string makeSDNF(std::map<char, std::vector<bool>> sourcePropositionalChar, std::vector<char> PropositionalCharCollection);` Возвращает строку, содержащую соответствующую совершенную дизъюктивную нормальную форму, на основе заполненной таблицы истинности и словаря пропозицональных букв. Если такой формы не существует, пробрасывает ошибку.



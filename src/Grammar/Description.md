Вернуться к [**описанию**](../Description.md)

# Grammar
**Grammar** - это раздел математики изучаюющие формальные языки.
Компиляторы строятся на них.
[Больше про грамматики](https://neerc.ifmo.ru/wiki/index.php?title=%D0%A2%D0%B5%D0%BE%D1%80%D0%B8%D1%8F_%D1%84%D0%BE%D1%80%D0%BC%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D1%85_%D1%8F%D0%B7%D1%8B%D0%BA%D0%BE%D0%B2#.D0.9C.D0.B8.D0.BD.D0.B8.D0.BC.D0.B8.D0.B7.D0.B0.D1.86.D0.B8.D1.8F_.D0.94.D0.9A.D0.90)

В данной библеотеке находятся алгоритмы и классы связанные с грамматиками:

1) В папке **Classes** находятся классы.
2) В папке **Algorithms** находятся алгоритмы.
3) Файл **Grammar.hpp** подключает все актуальные классы, связанные с грамматиками.

## Classes

В папке **Classes** находятся:

1) Папка **Traits** - в ней находятся метаклассы для удобства работы с классами грамматик. 
(Похожи на *type_treits* из *std*).
2) Папка **Requirements** - в ней лежат **concept**ы, которые проверяют класс на требования.
3) Остальные папки содержат реализации классов.

Описания и требования к классам:

1) [**Конечный автомат** (*FA* - Finite Automation)](Description/FA.md)
2) [**Обратная польская запись** (*RPN* - Reverse Polish notation)](Description/RPN.md)
3) [**Контекстно свободная грамматика** (CFG - Context-free grammar)](Description/CFG.md)

## Algorithms

#### Алгоритмы для конечных автоматов:
1) **Удаление eps переходов**. Реализация в 
    [RemoveEpsNFA.hpp](Algorithms/RemoveEpsNFA.hpp).
    Подробнее 
    [здесь](https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%B2%D1%82%D0%BE%D0%BC%D0%B0%D1%82%D1%8B_%D1%81_eps-%D0%BF%D0%B5%D1%80%D0%B5%D1%85%D0%BE%D0%B4%D0%B0%D0%BC%D0%B8._Eps-%D0%B7%D0%B0%D0%BC%D1%8B%D0%BA%D0%B0%D0%BD%D0%B8%D0%B5).

2) **Удаление бесполезных вершин**. Реализация в 
    [RemoveUselessNFA.hpp](Algorithms/RemoveUselessNFA.hpp).
    К сожалению, источники не найдены.

3) **Детермизация**. Превращает НКА в ДКА. Реализация в
    [DetermineNFA.hpp](Algorithms/DetermineNFA.hpp).
    Подробнее 
    [здесь](https://neerc.ifmo.ru/wiki/index.php?title=%D0%9F%D0%BE%D1%81%D1%82%D1%80%D0%BE%D0%B5%D0%BD%D0%B8%D0%B5_%D0%BF%D0%BE_%D0%9D%D0%9A%D0%90_%D1%8D%D0%BA%D0%B2%D0%B8%D0%B2%D0%B0%D0%BB%D0%B5%D0%BD%D1%82%D0%BD%D0%BE%D0%B3%D0%BE_%D0%94%D0%9A%D0%90,_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%A2%D0%BE%D0%BC%D0%BF%D1%81%D0%BE%D0%BD%D0%B0).

4) **Минимизация**.
    Минимизирует ДКА.
    Используется алгоритм Хопфорда.
    Реализация в 
    [MinimizeDFA.hpp](Algorithms/MinimizeDFA.hpp).
    Подробнее
    [здесь](https://neerc.ifmo.ru/wiki/index.php?title=%D0%9C%D0%B8%D0%BD%D0%B8%D0%BC%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F_%D0%94%D0%9A%D0%90,_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%A5%D0%BE%D0%BF%D0%BA%D1%80%D0%BE%D1%84%D1%82%D0%B0_(%D1%81%D0%BB%D0%BE%D0%B6%D0%BD%D0%BE%D1%81%D1%82%D1%8C_O(n_log_n))&mobileaction=toggle_view_desktop).

5) **Превращение НКА в ДКА**.
    Объединяет в себе предыдущие алгоритмы.
    Порядок исполнения такой:
    1) Удаление eps переходов.
    2) Удаление бесполезных вершин.
    3) Детермизация.
    4) Минимизация.
    
    Реализация в 
    [NFA2DFA.hpp](Algorithms/NFA2DFA.hpp).

6) **Функции над НКА**.
    Содержит такие функции:
    1) Конкатенация (***concat***) `(RS)`.
    2) Объединение (***alter***)  `(R|S)`.
    3) Звезда Клини (***kleene***) `(R*)`.
    4) Знак плюса (***plus***) `(R+)` эквивалентно `(RR*)`.
    5) Знак вопроса (***question***) `(R?)` эквивалентно `(R|\e)` где `\e` это пустой автомат.

    Реализация в 
    [FunctionsNFA.hpp](Algorithms/FunctionsNFA.hpp).
    Подробнее 
    [здесь](https://neerc.ifmo.ru/wiki/index.php?title=%D0%97%D0%B0%D0%BC%D0%BA%D0%BD%D1%83%D1%82%D0%BE%D1%81%D1%82%D1%8C_%D1%80%D0%B5%D0%B3%D1%83%D0%BB%D1%8F%D1%80%D0%BD%D1%8B%D1%85_%D1%8F%D0%B7%D1%8B%D0%BA%D0%BE%D0%B2_%D0%BE%D1%82%D0%BD%D0%BE%D1%81%D0%B8%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE_%D1%80%D0%B0%D0%B7%D0%BB%D0%B8%D1%87%D0%BD%D1%8B%D1%85_%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%86%D0%B8%D0%B9) и
    [здесь](https://en.wikipedia.org/wiki/Regular_expression)

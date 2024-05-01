Вернуться к [**описанию**](Description.md)

# Targets

Требования к коду:

1) Локальные концепты, классы начинаются с **`l`**
1) `concept` начинаютися с **`C_`**
1) `traits` начинаютися с **`T_`**
1) `generator` начинаются с **`G_`**
1) приватные переменные, 
функции, class и using 
в классе начинаются с **`_`**
1) как выглядит класс:
    ```c++
    template<
        class A,
        ...
    > class Name {
      // classes
        class _Private;
      // usings
        using _One = A;
      // _Private
        class _Private {};
      // metods
        void _example() {}
      // members
        _Private _value;
    public:
      // usings
        using Public = _Private;
      // metods
        void example() {}
    };
    ```
1) Название классов с большой буквы, а переменных с маленькой.
2) Если название состоит из нескольких слов, то слова начинаются с большой буквы.
Пример `FocusClass`, но не ~~`Focus_class`~~.
Вернуться к [**Grammar**](../Description.md)

# FA
## Description 
**FA** - Конечный автомат (Finite automation) делится на детерминированный **DFA** и недетерминированный **NFA**.

**FA** состоит из состояний **State** и переходов **Transition**.

**State** имеет **Type**.

**Transition** сотоит из **Letter** и указателя на следущее состояние. Обычно это пара.

**Type** обычно обозначеает завешающее состояние.

**Letter** обычно это буква (char).

У **DFA** в любом состоянии не может быть два перехода с одной буквой.
У **NFA** может.

Больше о [DFA](https://en.wikipedia.org/wiki/Deterministic_finite_automaton) и [NFA](https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton).

## Designations
Обозначения:
```c++
FA fa;
const FA c_fa;

State state;
const State c_state;

Transition trans;
const Transition c_trans;

State* ptr_state; // or ptr like type
const State* ptr_c_state; // or ptr like type

const Letter letter;

Type type;
const Type c_type;

```

## struct FA

### Requirements
Требования к **FA**:

1) **FA** должен иметь методы:
    ```c++
    // not need, but it better
    fa.start();    // return ptr_state
    c_fa.cstart(); // return c_ptr_state
    c_fa.start();  // return c_ptr_state

    fa.emplace();  // return ptr_state
    fa.emplate(args...); // return ptr_state
    // and args... need for constructor Type

    fa.erase(ptr_c_state);

    fa.size();   // return count state
    c_fa.size(); // return count state

    // for iteration all state
    fa.begin(); // return start ptr state
    fa.end();

    c_fa.begin(); // return start ptr const state
    c_fa.end();

    c_fa.cbegin(); // return start ptr const state
    c_fa.cend();
    ```

Для проверки требований используйте **concept**.
Они лежат в [**здесь**](../Classes/Requirements/FA.hpp).
Их названия:
```c++
// C_ is prefix for concept
sb::C_FA<FA>    // for FA
sb::C_cFA<FA>   // for const FA
sb::C_DFA<DFA>  // for DFA
sb::C_cDFA<DFA> // for const DFA
sb::C_NFA<NFA>  // for NFA
sb::C_cNFA<NFA> // for const NFA
```
### Possibilities
Вы можете по **FA** узнать типы State, Letter и остальные используя **Traits**.
Они лежат [**здесь**](../Classes/Traits/FA.hpp).
```c++
// T_ is prefix for traits
sb::T_FA<FA>::Letter
sb::T_FA<FA>::Type
sb::T_FA<FA>::State
sb::T_FA<FA>::PtrState
sb::T_FA<FA>::PtrConstState
sb::T_FA<FA>::Transition
// or better
sb::T_FALe<FA> // Letter
sb::T_FASt<FA> // State
sb::T_FATr<FA> // Transition
sb::T_FATy<FA> // Type
sb::T_FAPtrSt<FA> // PtrState
sb::T_FAPtrCSt<FA> // PtrConstState
```

## struct State

### Requirements
Требования к **State**:

1) **State** должно поддерживать такой синтаксис:
    ```c++
    state.trans(); // Container with trans
    state.type();  // return Type&
    
    c_state.trans(); // const Container with trans
    c_state.type(); // return const Type&
    
    for (auto& trans: state.trans()) {
        // your code
    }
    ```
2) Если **FA** является **DFA**, то:
    ```c++
    state.next(letter); // return ptr_state
    c_state.next(letter); // return ptr_c_state
    ```
3) Если **FA** является **NFA**, то:
    ```c++
    state.next(letter); // return subrange trans
    c_state.next(letter); // return const subrange trans
    ```
### Possibilities
Вы можете по **State** узнать типы Letter, Trans и остальные используя **Traits**.
Они лежат [**здесь**](../Classes/Traits/FA.hpp).
```c++
// T_ is prefix for traits
sb::T_StateFA<State>::Letter
sb::T_StateFA<State>::Type
sb::T_StateFA<State>::PtrState
sb::T_StateFA<State>::PtrConstState
sb::T_StateFA<State>::Transition
// or better
sb::T_StateFAPtrSt<State> // PtrState
sb::T_StateFAPtrCSt<State> // PtrConstState
sb::T_StateFALe<State> // Letter
sb::T_StateFATr<State> // Transition
sb::T_StateFATy<State> // Type
```

## struct Transition
### Requirements
Требования к **Transition**:

1) **Transition** должен поддерживать синтаксис:
    ```c++
    trans.first; // return Letter
    trans.second;  // return type implicitly convert to ptr_c_state
    trans.second->func(); // func from State

    c_trans.first; // return Letter
    c_trans.second;   // return type implicitly convert to ptr_c_state
    c_trans.second->func(); // func from const State
    ```
### Possibilities
Вы можете по **Transition** узнать типы Letter, Trans и остальные используя **Traits**.
Они лежат [**здесь**](../Classes/Traits/FA.hpp).
```c++
// T_ is prefix for traits
sb::T_TransitionFA<Transition>::Letter
sb::T_TransitionFA<Transition>::PtrState
sb::T_TransitionFA<Transition>::PtrConstState
// or better
sb::T_TransitionFAPtrSt<Transition> // PtrState
sb::T_TransitionFAPtrCSt<Transition> // PtrConstState
sb::T_TransitionFALe<Transition> // Letter
```

## struct Type
### Requirements
Требования к **Type**:

1) **Type** должен иметь операторы:
    ```c++
    type |= c_type;
    type = c_type | c_type;
    ```

## struct Letter
### Requirements
Требования к **Letter**:

1) **Letter** желательно должен быть сравниваемым, копируемым и хешироваемым типом.

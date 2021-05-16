#include "TemplateTypeDeduction.h"
#include <iostream>
#include <array>
/*
    Examples of the form:

    template<typename T>
    void f(ParamType param);

    f(expr)
*/

namespace TemplateTypeDeduction
{
    void SomeFunc(int a)
    {
    }

    void Example()
    {
        int x = 5;
        const int x2 = 5;
        const int& cx = x;

        //Case 1: ParamType is a reference/pointer
        //If expr is a reference/pointer ignore the reference/pointer part, then pattern match expr큦 type against ParamType to determine T.
        //The constness of an object is preserved and becomes part of the type deduced for T, so passing it to the function is safe.
        ByRefOrPointerFunction(x); //T = int, ParamType = int&
        ByRefOrPointerFunction(x2); //T = const int, ParamType = const int&
        ByRefOrPointerFunction(cx); //T = const int, ParamType = const int&

        ByConstRefOrPointerFunction(x); //T = int, ParamType = const int&
        ByConstRefOrPointerFunction(x2); //T = int, ParamType = const int&
        ByConstRefOrPointerFunction(cx); //T = int, ParamType = const int&

        //Case 2: ParamType is a universal reference (template type deduction distinguishes between lvalues and revalues arguments)
        //If expr is an lvalue, both T and ParamType are deduced to be lvalue refs. It is the only case in template type deduction where T is deduced to be a ref.
        //Although ParamType is declared as an rvalue ref, it큦 deduced type is an lvalue ref.
        ByUniversalRefFunction(x); //T = int&, ParamType = int&
        ByUniversalRefFunction(x2); //T = cosnt int&, ParamType = const int&
        ByUniversalRefFunction(cx); //T = const int&, ParamType = const int&
        ByUniversalRefFunction(10); //T = int, ParamType = int&&

        //Case 3: ParamType is a copy of the object
        ByValueFunction(x); //T = int, ParamType = int
        ByValueFunction(x2); //T = int, ParamType = int
        ByValueFunction(cx); //T = int, ParamType = int

        //Special case: Array Arguments
        const char name[] = "Hello"; //name큦 type is const char[5]
        ByValueFunction(name); //T is const char* (array to pointer decay)
        ByRefOrPointerFunction(name); //T = const char[5], ParamType = const char(&)[5]

        const int n[3] = { 1,2,3 };
        std::array<int, arraySize(n)> m;
        std::cout << "Array size: " << m.size() << std::endl;

        //Special case: Function Arguments (function to pointer decay)
        //SomeFunc큦 type is void(int)
        ByValueFunction(SomeFunc); //ParamType = void*(int) (function to pointer decay)
        ByRefOrPointerFunction(SomeFunc); //ParamType = void(&)(int)
    }
}
#pragma once
#include <iostream>

namespace TemplateTypeDeduction
{
    template<typename T>
    void ByValueFunction(T param) {}

    template<typename T>
    void ByRefOrPointerFunction(T& param) {}

    template<typename T>
    void ByConstRefOrPointerFunction(const T& param) {}

    template<typename T>
    void ByUniversalRefFunction(T&& param) {}

    //Return the size of an array as a comile time constant
    template<typename T, std::size_t N>
    constexpr std::size_t arraySize(T(&)[N]) noexcept
    {
        return N;
    }

    void SomeFunc(int a);

    void Example();
}


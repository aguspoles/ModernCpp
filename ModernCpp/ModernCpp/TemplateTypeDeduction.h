#pragma once
#include <iostream>
#include <boost/type_index.hpp>

#define LOG_TYPE(T, name) std::cout << name << " = " << boost::typeindex::type_id_with_cvr<T>().pretty_name() << '\n';

namespace TemplateTypeDeduction
{
    template<typename T>
    void ByValueFunction(T param) 
    {
        std::cout << "ByValueFunction" << std::endl;
        LOG_TYPE(T, "T");
        LOG_TYPE(decltype(param), "ParamType");
    }

    template<typename T>
    void ByRefOrPointerFunction(T& param) 
    { 
        std::cout << "ByRefOrPointerFunction" << std::endl;
        LOG_TYPE(T, "T"); 
        LOG_TYPE(decltype(param), "ParamType");
    }

    template<typename T>
    void ByConstRefOrPointerFunction(const T& param) 
    {
        std::cout << "ByConstRefOrPointerFunction" << std::endl;
        LOG_TYPE(T, "T");
        LOG_TYPE(decltype(param), "ParamType");
    }

    template<typename T>
    void ByUniversalRefFunction(T&& param) 
    {
        std::cout << "ByUniversalRefFunction" << std::endl;
        LOG_TYPE(T, "T");
        LOG_TYPE(decltype(param), "ParamType");
    }

    //Return the size of an array as a comile time constant
    template<typename T, std::size_t N>
    constexpr std::size_t arraySize(T(&)[N]) noexcept
    {
        return N;
    }

    void SomeFunc(int a);

    void Example();
}


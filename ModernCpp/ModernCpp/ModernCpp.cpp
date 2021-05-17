#include "TemplateTypeDeduction.h"
#include <vector>

template<typename Container, typename Index>
decltype(auto) accessElement(Container&& c, Index i)
{
    return std::forward<Container>(c)[i];
}

int main()
{
    TemplateTypeDeduction::Example();

    //auto type deduction is esentially the same as template type deduction except for the cases of initializer lists
    auto c{ 1 }; //c = std::initializer_lis<int>
    //TemplateTypeDeduction::ByValueFunction({ 1 }); //Won't compile can't deduce type for T
    //auto f = []() { return { 3 }; } //Won't compile can't deduce type for T

    //During template type deduction the referenc-ness of an initializing expresion is ignore. Wich is what auto do.
    //decltype gives you the type you would expect
    const int& number = 10;
    auto number1 = number; // number1 = int
    decltype(auto) number2 = number; // number2 = const int&

    //operator [] of a container tipically returns a T&
    std::vector<int> v{1,2,3};
    accessElement(v, 0) = 8; //decltype saves this, otherwise we would be attempting to assign a value to an rvalue
    auto value = accessElement(std::vector<int>{4}, 0); //The universal ref allow us to pass an rvalue to the function
}
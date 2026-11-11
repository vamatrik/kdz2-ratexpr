#include <iostream>
#include <memory>

#include "ratexpr/expression.hpp"

using namespace ratexpr;

int main() {
    auto e = std::make_unique<Mul>(
        std::make_unique<Add>(std::make_unique<Const>(Fraction(1, 2)),
                              std::make_unique<Const>(Fraction(1, 3))),
        std::make_unique<Sub>(std::make_unique<Const>(Fraction(3)),
                              std::make_unique<Const>(Fraction(1, 4))));

    std::cout << *e << " = " << e->evaluate() << '\n';

    auto ee = std::make_unique<Negative>(
        std::make_unique<Div>(std::make_unique<Const>(Fraction(2)),
                              std::make_unique<Const>(Fraction(3))));

    std::cout << *ee << " = " << ee->evaluate() << '\n';
    return 0;
}
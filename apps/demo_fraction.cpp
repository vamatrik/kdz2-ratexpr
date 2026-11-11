#include <iostream>
#include <stdexcept>

#include "ratexpr/fraction.hpp"

using ratexpr::Fraction;

int main() {
    const Fraction frac12(1, 2);
    const Fraction frac13(1, 3);

    std::cout << "Fraction(6, -8) - " << Fraction(6, -8) << std::endl;
    std::cout << "Fraction(10, 4) - " << Fraction(10, 4) << std::endl;
    std::cout << "1/2 + 1/3 - " << frac12 + frac13 << std::endl;
    std::cout << "1/2 - 1/3 - " << frac12 - frac13 << std::endl;
    std::cout << "1/2 * 1/3 - " << frac12 * frac13 << std::endl;
    std::cout << "1/2 / 1/3 - " << frac12 / frac13 << std::endl;
    std::cout << "1/2 + 2u - " << frac12 + 2u << " - должно быть равно 2u + 1/2 - " << 2u + frac12 << std::endl;
    std::cout << "1/2 - 2u - " << frac12 - 2u << " - должно быть равно минус (2u - 1/2) - " << 2u - frac12 << std::endl;
    std::cout << "1/2 / 2u - " << frac12 / 2u << " - должно быть обратно 2u / (1/2) - " << 2u / frac12 << std::endl;

    Fraction acc;
    acc += frac12;
    acc += frac13;
    acc *= 6u;
    std::cout << "acc = 0; acc += 1/2; acc += 1/3; acc *= 6u; - " << acc << std::endl;

    try {
        Fraction zov(1, 0);
        std::cout << "Fraction(1, 0) - " << zov << " у меня сломан код я не должен этого видеть надо идти переделывать" << std::endl;
    } catch (const std::invalid_argument&) {
        std::cout << "Fraction(1, 0) - std::invalid_argument верно все" << std::endl;
    }
    try {
        Fraction idk = frac12 / 0u;
        std::cout << "1/2 / 0u = " << idk << " у меня сломан код я не должен этого видеть надо идти переделывать" << std::endl;
    } catch (const std::invalid_argument&) {
        std::cout << "1/2 / 0u - std::invalid_argument верно все" << std::endl;
    }
    std::cout << Fraction(1, 2) * -1;
    return 0;
}

#include <chrono>
#include <iostream>
#include <memory>

#include "ratexpr/expression.hpp"

using namespace ratexpr;

std::unique_ptr<Expression> drevo_build(int levels) {
    if (levels == 0) return std::make_unique<Const>(Fraction(1, 2));
    return std::make_unique<Add>(drevo_build(levels - 1), drevo_build(levels - 1));
}

int main() {
    // Вот тут как раз я проверяю пример для моего дерева из отчета (задание Д.1). Еще ниже будет для Д2 сложное дерево.
    auto small_drevo = std::make_unique<Mul>(
        std::make_unique<Mul>(std::make_unique<Const>(Fraction(1, 2)), std::make_unique<Const>(Fraction(1))),
        std::make_unique<Negative>(std::make_unique<Negative>(std::make_unique<Const>(Fraction(5)))));
    auto small_drevo_simplified = small_drevo->simplify();

    std::cout << "Д.1" << std::endl;
    std::cout << "Без сммплификации" << *small_drevo << " = " << small_drevo->evaluate() << ", как я и говорил, операций " << small_drevo->operation_count() << std::endl;
    std::cout << "С симплификацией " << *small_drevo_simplified << " = " << small_drevo_simplified->evaluate() << " - значение то же самое, а операций уже  " << small_drevo_simplified->operation_count() << std::endl;

    // Таймеры снова, жаль без них нельзя обойтись (((
    const int levels = 21;

    std::unique_ptr<Expression> neokyp = std::make_unique<Add>(drevo_build(levels - 1), std::make_unique<Mul>(drevo_build(levels - 1), std::make_unique<Const>(Fraction(0))));
    std::unique_ptr<Expression> okyp = std::make_unique<Add>(std::make_unique<Const>(Fraction(1, 2)), std::make_unique<Mul>(drevo_build(levels), std::make_unique<Const>(Fraction(0))));

    {
        std::cout << "Ситуация так скажем не окуп" << std::endl;
        double eval_ms = 0, simplify_ms = 0, eval_simplified_ms = 0;

        for (int i = 0; i < 5; ++i) {
            auto t0 = std::chrono::steady_clock::now();
            Fraction z1 = neokyp->evaluate();
            auto t1 = std::chrono::steady_clock::now();

            auto s = neokyp->simplify();
            auto t2 = std::chrono::steady_clock::now();
            Fraction z2 = s->evaluate();
            auto t3 = std::chrono::steady_clock::now();

            eval_ms += std::chrono::duration<double, std::milli>(t1 - t0).count();
            simplify_ms += std::chrono::duration<double, std::milli>(t2 - t1).count();
            eval_simplified_ms += std::chrono::duration<double, std::milli>(t3 - t2).count();

            std::cout << "Операций было: " << neokyp->operation_count() << " стало: " << s->operation_count() << std::endl;
            std::cout << "Значения: " << z1 << " и " << z2 << " должны быть равны, иначе анлак" << std::endl;
            std::cout << "Совпадают? " << (z1 == z2 ? "да" : "нет") << std::endl;
        }

        eval_ms /= 5;
        simplify_ms /= 5;
        eval_simplified_ms /= 5;

        std::cout << "Время на простой счет " << eval_ms << std::endl;
        std::cout << "Время на симплификацию " << simplify_ms << std::endl;
        std::cout << "Время на счет симплифицированного выражения " << eval_simplified_ms << std::endl;
        std::cout << "Итого на симплификацию и подсчет вместе " << simplify_ms + eval_simplified_ms << std::endl;
    }

    {
        std::cout << "Додеп и окуп" << std::endl;

        double eval_ms = 0, simplify_ms = 0, eval_simplified_ms = 0;

        for (int i = 0; i < 5; ++i) {
            auto t0 = std::chrono::steady_clock::now();
            Fraction z1 = okyp->evaluate();
            auto t1 = std::chrono::steady_clock::now();

            auto s = okyp->simplify();
            auto t2 = std::chrono::steady_clock::now();
            Fraction z2 = s->evaluate();
            auto t3 = std::chrono::steady_clock::now();

            eval_ms += std::chrono::duration<double, std::milli>(t1 - t0).count();
            simplify_ms += std::chrono::duration<double, std::milli>(t2 - t1).count();
            eval_simplified_ms += std::chrono::duration<double, std::milli>(t3 - t2).count();

            std::cout << "Операций было: " << okyp->operation_count() << " стало: " << s->operation_count() << std::endl;
            std::cout << "Значения: " << z1 << " и " << z2 << " должны быть равны, иначе печалька (по идее 1/2)" << std::endl;
            std::cout << "Совпадают? " << (z1 == z2 ? "да" : "нет") << std::endl;
        }

        eval_ms /= 5;
        simplify_ms /= 5;
        eval_simplified_ms /= 5;

        std::cout << "Время на простой счет " << eval_ms << std::endl;
        std::cout << "Время на симплификацию " << simplify_ms << std::endl;
        std::cout << "Время на счет симплифицированного выражения " << eval_simplified_ms << std::endl;
        std::cout << "Итого на симплификацию и подсчет вместе " << simplify_ms + eval_simplified_ms << std::endl;
    }

    return 0;
}

#pragma once

#include <cstdint>
#include <iosfwd>

namespace ratexpr {

class Fraction {
public:
    Fraction();
    Fraction(std::int64_t numerator, std::int64_t denominator = 1);

    std::int64_t Numerator() const { return num_; }
    std::int64_t Denominator() const { return den_; }

    Fraction& operator+=(const Fraction& o);
    Fraction& operator-=(const Fraction& o);
    Fraction& operator*=(const Fraction& o);
    Fraction& operator/=(const Fraction& o);

    Fraction& operator+=(std::uint32_t k);
    Fraction& operator-=(std::uint32_t k);
    Fraction& operator*=(std::uint32_t k);
    Fraction& operator/=(std::uint32_t k);

    Fraction operator-() const;

    friend Fraction operator+(const Fraction& a, const Fraction& b);
    friend Fraction operator+(const Fraction& a, std::uint32_t k);
    friend Fraction operator+(std::uint32_t k, const Fraction& b);

    friend Fraction operator-(const Fraction& a, const Fraction& b);
    friend Fraction operator-(const Fraction& a, std::uint32_t k);
    friend Fraction operator-(std::uint32_t k, const Fraction& b);

    friend Fraction operator*(const Fraction& a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, std::uint32_t k);
    friend Fraction operator*(std::uint32_t k, const Fraction& b);

    friend Fraction operator/(const Fraction& a, const Fraction& b);
    friend Fraction operator/(const Fraction& a, std::uint32_t k);
    friend Fraction operator/(std::uint32_t k, const Fraction& b);

    friend bool operator==(const Fraction& a, const Fraction& b);
    friend bool operator!=(const Fraction& a, const Fraction& b);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);

private:
    void normalize();

    std::int64_t num_;
    std::int64_t den_;
};

}

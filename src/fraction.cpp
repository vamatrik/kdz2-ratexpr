#include "ratexpr/fraction.hpp"

#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <numeric>

namespace ratexpr {
    void Fraction::normalize(){
        std::int64_t nod = std::gcd(num_, den_);
        num_ /= nod;
        den_ /= nod;
        if (den_ < 0){
            num_ = -num_;
            den_ = -den_;
        }
    }

    Fraction::Fraction(): num_(0), den_(1) {}
    Fraction::Fraction(std::int64_t n, std::int64_t d): num_(n), den_(d) {
        if (d == 0) {
            throw std::invalid_argument("Division by Zero");
        }
        normalize();
    }

    Fraction& Fraction::operator+=(const Fraction& x){
        num_ = num_ * x.den_ + x.num_ * den_;
        den_ = den_ * x.den_;
        normalize();
        return *this;
    }
    Fraction& Fraction::operator-=(const Fraction& x){
        num_ = num_ * x.den_ - x.num_ * den_;
        den_ = den_ * x.den_;
        normalize();
        return *this;
    }
    Fraction& Fraction::operator*=(const Fraction& x){
        num_ = num_ * x.num_;
        den_ = den_ * x.den_;
        normalize();
        return *this;
    }
    Fraction& Fraction::operator/=(const Fraction& x){
        if (x.num_ == 0) {
            throw std::invalid_argument("Division by Zero");
        }
        num_ = num_ * x.den_;
        den_ = den_ * x.num_;
        normalize();
        return *this;
    }
    Fraction& Fraction::operator+=(std::uint32_t x){
        num_ += x * den_;
        normalize();
        return *this;
    }
    Fraction& Fraction::operator-=(std::uint32_t x){
        num_ -= x * den_;
        normalize();
        return *this;
    }
    Fraction& Fraction::operator*=(std::uint32_t x){
        num_ = num_ * x;
        normalize();
        return *this;
    }
    Fraction& Fraction::operator/=(std::uint32_t x){
        if (x == 0) {
            throw std::invalid_argument("Division by Zero");
        }
        den_ = den_ * x;
        normalize();
        return *this;
    }
    Fraction Fraction::operator-() const {return Fraction(-num_, den_);}

    Fraction operator+(const Fraction& a, const Fraction& b){
        Fraction result = a;
        result += b;
        return result;
    }
    Fraction operator+(const Fraction& a, std::uint32_t k){
        Fraction result = a;
        result += k;
        return result;
    }
    Fraction operator+(std::uint32_t k, const Fraction& b){
        Fraction result = b;
        result += k;
        return result;
    }

    Fraction operator-(const Fraction& a, const Fraction& b){
        Fraction result = a;
        result -= b;
        return result;
    }
    Fraction operator-(const Fraction& a, std::uint32_t k){
        Fraction result = a;
        result -= k;
        return result;
    }
    Fraction operator-(std::uint32_t k, const Fraction& b){
        Fraction result(k);
        result -= b;
        return result;
    }

    Fraction operator*(const Fraction& a, const Fraction& b){
        Fraction result = a;
        result *= b;
        return result;
    }
    Fraction operator*(const Fraction& a, std::uint32_t k){
        Fraction result = a;
        result *= k;
        return result;
    }
    Fraction operator*(std::uint32_t k, const Fraction& b){
        Fraction result = b;
        result *= k;
        return result;
    }

    Fraction operator/(const Fraction& a, const Fraction& b){
        Fraction result = a;
        result /= b;
        return result;
    }
    Fraction operator/(const Fraction& a, std::uint32_t k){
        Fraction result = a;
        result /= k;
        return result;
    }
    Fraction operator/(std::uint32_t k, const Fraction& b){
        Fraction result(k);
        result /= b;
        return result;
    }
    
    bool operator==(const Fraction& a, const Fraction& b){
        return a.num_ == b.num_ && a.den_ == b.den_;
    }
    bool operator!=(const Fraction& a, const Fraction& b){
        return !(a == b);
    }

    std::ostream& operator<<(std::ostream& os, const Fraction& f){
        if (f.den_ == 1) {
            os << f.num_;
        }
        else {
            os << f.num_ << "/" << f.den_;
        }
        return os;
    }
}

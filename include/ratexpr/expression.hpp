#pragma once

#include <cstddef>
#include <iosfwd>
#include <memory>

#include "ratexpr/fraction.hpp"

namespace ratexpr {

class Expression {
public:
    virtual ~Expression() = default;
    virtual Fraction evaluate() const = 0;
    virtual void print(std::ostream& os) const = 0;

    virtual std::unique_ptr<Expression> simplify() const = 0;
    virtual std::size_t operation_count() const = 0;
};

std::ostream& operator<<(std::ostream& os, const Expression& e);

class Const : public Expression {
public:
    explicit Const(const Fraction& value);

    const Fraction& value() const { return value_; }

    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
    std::unique_ptr<Expression> simplify() const override;
    std::size_t operation_count() const override;

private:
    Fraction value_;
};

class Negative : public Expression {
public:
    explicit Negative(std::unique_ptr<Expression> operand);
    Fraction evaluate() const override;
    void print(std::ostream& os) const override;
    std::unique_ptr<Expression> simplify() const override;
    std::size_t operation_count() const override;

private:
    std::unique_ptr<Expression> operand_;
};

class BinaryExpression : public Expression {
public:
    BinaryExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs);
    void print(std::ostream& os) const override;
    std::size_t operation_count() const override;
protected:
    virtual char symbol() const = 0;
    std::unique_ptr<Expression> lhs_;
    std::unique_ptr<Expression> rhs_;
};

class Add : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;
    Fraction evaluate() const override;
    std::unique_ptr<Expression> simplify() const override;
protected:
    char symbol() const override;
};

class Sub : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;
    Fraction evaluate() const override;
    std::unique_ptr<Expression> simplify() const override;
protected:
    char symbol() const override;
};

class Mul : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;
    Fraction evaluate() const override;
    std::unique_ptr<Expression> simplify() const override;
protected:
    char symbol() const override;
};

class Div : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;
    Fraction evaluate() const override;
    std::unique_ptr<Expression> simplify() const override;
protected:
    char symbol() const override;
};

}

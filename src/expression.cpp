#include "ratexpr/expression.hpp"

#include <ostream>
#include <utility>

namespace ratexpr {

std::ostream& operator<<(std::ostream& os, const Expression& e) {
    e.print(os);
    return os;
}

Const::Const(const Fraction& value) : value_(value) {}

Fraction Const::evaluate() const {
    return value_;
}

void Const::print(std::ostream& os) const {
    os << value_;
}

Negative::Negative(std::unique_ptr<Expression> operand): operand_(std::move(operand)) {}

Fraction Negative::evaluate() const {
    return -operand_->evaluate();
}

void Negative::print(std::ostream& os) const {
    os << "(-" << *operand_ << ")";
}

BinaryExpression::BinaryExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs): lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

void BinaryExpression::print(std::ostream& os) const {
    os << "(" << *lhs_ << " " << symbol() << " " << *rhs_ << ")";
}

Fraction Add::evaluate() const { return lhs_->evaluate() + rhs_->evaluate(); }
char Add::symbol() const { return '+'; }

Fraction Sub::evaluate() const { return lhs_->evaluate() - rhs_->evaluate(); }
char Sub::symbol() const { return '-'; }

Fraction Mul::evaluate() const { return lhs_->evaluate() * rhs_->evaluate(); }
char Mul::symbol() const { return '*'; }

Fraction Div::evaluate() const { return lhs_->evaluate() / rhs_->evaluate(); }
char Div::symbol() const { return '/'; }

// допка

namespace {
bool is_const_equal(const Expression& e, const Fraction& v) {
    const Const* c = dynamic_cast<const Const*>(&e);
    return c != nullptr && c->value() == v;
}

bool is_zero(const Expression& e) { return is_const_equal(e, Fraction(0)); }
bool is_one(const Expression& e) { return is_const_equal(e, Fraction(1)); }

}

std::size_t Const::operation_count() const { return 0; }
std::size_t Negative::operation_count() const { return 1 + operand_->operation_count(); }
std::size_t BinaryExpression::operation_count() const { return 1 + lhs_->operation_count() + rhs_->operation_count(); }

std::unique_ptr<Expression> Const::simplify() const { return std::make_unique<Const>(value_); }

std::unique_ptr<Expression> Negative::simplify() const {
    std::unique_ptr<Expression> x = operand_->simplify();
    if (is_zero(*x)) return x;
    if (Negative* inner = dynamic_cast<Negative*>(x.get())) {
        return std::move(inner->operand_);
    }
    return std::make_unique<Negative>(std::move(x));
}

std::unique_ptr<Expression> Add::simplify() const {
    std::unique_ptr<Expression> l = lhs_->simplify();
    std::unique_ptr<Expression> r = rhs_->simplify();
    if (is_zero(*l)) return r;
    if (is_zero(*r)) return l;
    return std::make_unique<Add>(std::move(l), std::move(r));
}

std::unique_ptr<Expression> Sub::simplify() const {
    std::unique_ptr<Expression> l = lhs_->simplify();
    std::unique_ptr<Expression> r = rhs_->simplify();
    if (is_zero(*r)) return l;
    return std::make_unique<Sub>(std::move(l), std::move(r));
}

std::unique_ptr<Expression> Mul::simplify() const {
    std::unique_ptr<Expression> r = rhs_->simplify();
    if (is_zero(*r)) return std::make_unique<Const>(Fraction(0));
    std::unique_ptr<Expression> l = lhs_->simplify();
    if (is_zero(*l)) return std::make_unique<Const>(Fraction(0));
    if (is_one(*r)) return l;
    if (is_one(*l)) return r;
    return std::make_unique<Mul>(std::move(l), std::move(r));
}

std::unique_ptr<Expression> Div::simplify() const {
    std::unique_ptr<Expression> l = lhs_->simplify();
    std::unique_ptr<Expression> r = rhs_->simplify();
    if (is_one(*r)) return l;
    return std::make_unique<Div>(std::move(l), std::move(r));
}
}
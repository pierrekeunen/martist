#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

const double PI = 3.141592653589793238462643;


class Expression {
public:
    virtual double computePixel(double x, double y) = 0;
    virtual std::string asString() = 0;
    Expression();
};


class X: public Expression {
public:
    X();
    double computePixel(double x, double y) override;
    std::string asString() override;
};


class Y: public Expression {
public:
    Y();
    double computePixel(double x, double y) override;
    std::string asString() override;
};


class SinusExpression: public Expression {
public:
    explicit SinusExpression(Expression operand);
    double computePixel(double x, double y) override;
    std::string asString() override;

private:
    Expression m_operand;

};


class CosinusExpression: public Expression {
public:
    explicit CosinusExpression(Expression operand);
    double computePixel(double x, double y) override;
    std::string asString() override;

private:
    Expression m_operand;

};



class TimesExpression: public Expression {
public:
    TimesExpression(Expression left_operand, Expression right_operand);
    double computePixel(double x, double y) override;
    std::string asString() override;

private:
    Expression m_left_operand;
    Expression m_right_operand;

};


class AverageExpression: public Expression {
public:
    AverageExpression(Expression left_operand, Expression right_operand);
    double computePixel(double x, double y) override;
    std::string asString() override;

private:
    Expression m_left_operand;
    Expression m_right_operand;

};

#endif //EXPRESSION_HPP_INCLUDED

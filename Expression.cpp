#include<cstddef> // Afin d'utiliser nullptr
#include<string>
#include<stdexcept> // Afin d'utiliser les throw et exceptions
#include<ctime> // Afin d'utiliser time
#include<cstdlib> // Afin d'utiliser srand
#include<vector> // front
#include <cmath> // Afin d'utiliser le sin, et le cos
#include "martist.hpp"
#include "Expression.hpp"
//#include "parser.hpp"

using namespace std;

Expression::Expression() = default;

X::X() = default;
Y::Y() = default;

SinusExpression::SinusExpression(Expression operand) {
    m_operand = operand;
}

CosinusExpression::CosinusExpression(Expression operand) {
    m_operand = operand;
}

TimesExpression::TimesExpression(Expression left_operand, Expression right_operand) {
    m_left_operand = left_operand;
    m_right_operand = right_operand;
}

AverageExpression::AverageExpression(Expression left_operand, Expression right_operand) {
    m_left_operand = left_operand;
    m_right_operand = right_operand;
}

double X::computePixel(double x, double y) {
    return x;
}

double Y::computePixel(double x, double y) {
    return y;
}

double SinusExpression::computePixel(double x, double y) {
    return std::sin(PI * m_operand.computePixel(x, y));
}

double CosinusExpression::computePixel(double x, double y) {
    return std::cos(PI * m_operand.computePixel(x, y));
}

double TimesExpression::computePixel(double x, double y) {
    return x;
}

double AverageExpression::computePixel(double x, double y) {
    return x;
}

std::string X::asString() {
    return "x";
}

std::string Y::asString() {
    return "y";
}

std::string SinusExpression::asString() {
    return "sin(pi * " + m_operand + ")";
}

std::string CosinusExpression::asString() {
    return "cos(pi * " + m_operand + ")";
}


std::string TimesExpression::asString() {
    return "(" + m_left_operand + " * " + m_right_operand + ")";
}


std::string AverageExpression::asString() {
    return "avg(" + m_left_operand + ", " + m_right_operand + ")";
}

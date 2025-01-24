#include "evaluator.h"
#include <stack> // std::stack
#include <algorithm>
#include <iostream>

const char OPEN = '(';
const char CLOSE = ')';
const std::string OPERATORS = "+-*/%";

int calculate(int operand1, int operand2, char op) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return (operand2 == 0) ? throw bad_expression() : operand1 / operand2;
        case '%':
            return (operand2 == 0) ? throw bad_expression() : operand1 % operand2;
        default:
            throw std::invalid_argument("param op is not a viable operator");
    }
}

void isBadExpression(const std::string &expression) {
    // test if there are brackets at the beginning and the end of the expression
    if (*expression.begin() != OPEN or *(expression.end() - 1) != CLOSE) {
        throw bad_expression();
    }
    // test if there is the same number of opening and closing brackets
    if (std::count(expression.begin(), expression.end(), OPEN) != std::count
            (expression.begin(), expression.end(), CLOSE)) {
        throw bad_expression();
    }
    // test if there is a unary operator
    auto current_caracter = *expression.begin();
    while (std::isblank(current_caracter) or current_caracter == OPEN) {

    }
    // test if there are two following operators

}

bool isOperator(char c) {
    return OPERATORS.find(c) != std::string::npos;
}
bool isValid(char c) {
    return isdigit(c) or isOperator(c) or c == OPEN or c == CLOSE or std::isblank(c);
}

int evalue(std::string const &expression) {
    // isBadExpression(expression);
    std::stack<int> operands;
    std::stack<char> operators;
    std::string value;
    for (char c: expression) {
        if(!isValid(c)) throw bad_expression();

        if (isdigit(c)) {

            value.append(1, c);


        } else {
            if (!value.empty()) {
                operands.push(std::stoi(value));
                value.clear();
            }
        }


        if (isOperator(c)) {
            operators.push(c);
        } else if (c == CLOSE) {
            if (operands.size() < 2) throw bad_expression();
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();
            char op = operators.top();
            operators.pop();
            operands.push(calculate(operand1, operand2, op));

        }

    }
    if(operands.size() != 1 or !operators.empty()) throw bad_expression();
    return operands.top();
}

// a compléter avec une définition de la fonction evalue qui met en
// oeuvre l'algorithme à 2 piles
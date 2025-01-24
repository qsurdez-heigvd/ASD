#include "evaluator.h"

const char OPEN = '(';
const char CLOSE = ')';
const std::string OPERATORS = "+-*/%";

int calculate(int operand1, int operand2, char op){
	switch(op){
		case '+': return operand1 + operand2;
		case '-': return operand1 - operand2;
		case '*': return operand1 * operand2;
		case '/':
			return (operand2==0) ? throw bad_expression() : operand1 / operand2;
		case '%':
			return (operand2==0) ? throw bad_expression() : operand1 % operand2;
			default:
				throw bad_expression();
	}
}


void nextOperator(std::string::iterator& actualPosition) {
	size_t numberOfOpenBrackets = 0;
   size_t numberOfClosedBrackets = 0;

   actualPosition++;

   do {
      if (*actualPosition == CLOSE)
         ++numberOfClosedBrackets;
      else if (*actualPosition == OPEN)
         ++numberOfOpenBrackets;
      ++actualPosition;
   } while (numberOfOpenBrackets != numberOfClosedBrackets);
}

int readNumber(std::string::iterator& it) {
   int result;
   std::string stringNumber;
   while(isdigit(*it)) {
      stringNumber.append(1,*it);
      ++it;
   }
   result = std::stoi(stringNumber);
   return result;
}

bool isOperator(char c) {
   return OPERATORS.find(c) != std::string::npos;
}

int evalue(std::string const& expression) {
   int result = 0;
   std::string expr = expression;

   expr.erase(remove_if(expr.begin(), expr.end(), std::isspace), expr.end());
   if(*(expr.begin()) == OPEN) {
      auto actualPosition = expr.begin();
      auto left = std::string(actualPosition + 1, expr.end());
      int leftNumber = evalue(left);
      nextOperator(actualPosition);
      actualPosition = find_if(actualPosition, expr.end(), isOperator);
      char actualOperator = *(actualPosition);
      int rightNumber = evalue(std::string(actualPosition + 1, expr.end()));
      result = calculate(leftNumber, rightNumber, actualOperator);
   } else if (std::isdigit(*(expr.begin()))) {
      auto actualPosition = expr.begin();
      result = readNumber(actualPosition);
   } else {
      throw bad_expression();
   }
	return result;
}




// a compléter avec une définition récursive de la fonction evalue
// qui n'utilise pas de pile
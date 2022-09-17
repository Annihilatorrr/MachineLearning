#include <iostream>
#include <string>

#include "shuntingyard.h"

int main() {
	std::cout << "Hello, Shunting Yard!" << std::endl;

	std::cout << "Input equation: ";

	std::string eqn("3+3*2");
	//std::getline(std::cin, eqn);


	std::vector<std::string> rpn = ShuntingYard::reversePolishNotation(eqn.c_str());
	ShuntingYard::Node* tree = ShuntingYard::parse(rpn);
	std::cout << "= " << ShuntingYard::eval(tree) << std::endl;

	return 0;
}
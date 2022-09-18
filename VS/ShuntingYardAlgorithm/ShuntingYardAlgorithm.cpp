#include <iostream>
#include <string>
#include <vector>

#include "shuntingyard.h"
#include "shuntingyardalgo.h"

int main() {
	std::cout << "Hello, Shunting Yard!" << std::endl;

	//std::cout << "Input equation: ";

	std::string eqn("3+3*2");
	//std::getline(std::cin, eqn);

	ShuntingYard sy;
	std::vector<std::string> rpn = sy.reversePolishNotation(eqn.c_str());
	Node* tree = sy.parse(rpn);
	std::cout << "= " << sy.eval(tree) << std::endl;

	return 0;
}

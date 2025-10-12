/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:03:52 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/12 21:04:51 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <string>
#include <cctype> // for std::isdigit

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& copy) :
	_rev_notation(copy._rev_notation) 
	{}

RPN& RPN::operator=(const RPN& assign) {
	if (this != &assign) {
		_rev_notation = assign._rev_notation;
	}
	return *this;
}

bool	RPN::isValidInput(const std::string & input) {
	if (input.empty()) {
		std::cerr << "Error" << std::endl;
		return false;
	}
	if (input.find_first_not_of("0123456789 +-*/") != std::string::npos) {
		std::cerr << "Error" << std::endl;
		return false;
	}
	int j = 0;
	for (size_t i = 0; i < input.length(); i++) {
		char c = input[i];
		if (std::isdigit(c))
			j++;
	}
	if (j < 2) {
		std::cerr << "Error: less than 2 operands" << std::endl;
		return false;
	}
	return true;
}

void	RPN::Calculate(const std::string & input) {

	if (!isValidInput(input)) {
		return ;
	}
	for (size_t i = 0; i < input.length(); i++) {
		char c = input[i];
		if (std::isdigit(c)) {
			int number = c - '0'; 
			this->_rev_notation.push(number);
		}
		else if (c == ' ')
			continue ;
		else if (c == '*' || c == '-' || c == '+' || c == '/' ) {
			if (!Operation(c))
				return ;
		}
	}
	if (_rev_notation.size() != 1) {
		std::cerr << "Error: Stack contains more than one number.\n";
		std::cerr << "Wrong format of reversed polish notation" << std::endl;
		return ;
	}
	std::cout << _rev_notation.top() << std::endl;
}

bool	RPN::Operation(char c) {
	if (_rev_notation.size() < 2) {
		std::cerr << "Error: Wrong input. Not enough numbers for operation" << std::endl;
		return false;
	}
	int b = _rev_notation.top();
		_rev_notation.pop();
	int a = _rev_notation.top();
	_rev_notation.pop();
	int res = 0;
	if (c == '*')
		res = a * b;
	else if (c == '-')
		res = a - b;
	else if (c == '+')
		res = a + b;
	else if (c == '/') {
		if (b == 0) {
			std::cerr << "Error: Division by zero" << std::endl;
			return false;
		}
		res = a / b;
	}
	_rev_notation.push(res);
	return true;
}

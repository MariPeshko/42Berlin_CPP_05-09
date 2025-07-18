/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:58:57 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/18 14:36:56 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

/** take as a parameter a string representation of a C++ literal in its most common
form and output its value in the following series of scalar types */
// Takes the input from the command line.
void ScalarConverter::convert(std::string const &literal) {
    
    char c = '0';
    int	i = 0;
	float f = 0.0f;
	double d = 0.0;
	
    if (literal.empty()) {
        std::cerr << "Error: Empty input." << std::endl;
        return ;
    }
	// int or ascii
    if (literal.length() == 1) {
		if (isspace(static_cast<unsigned char>(literal[0]))) {
			std::cout << std::fixed << std::setprecision(2);
			std::cout << "char: " << std::setw(4) << "" << "it's a whitespace character\n";
			i = static_cast<int>(literal[0]);
			f = static_cast<float>(literal[0]);
			d = static_cast<double>(literal[0]);
			std::cout << "int: " << std::setw(7) << std::right << i << std::endl;
			std::cout << "float: " << std::setw(8) << std::right << f << "f" << std::endl; 
			std::cout << "double: " << std::setw(7) << std::right << d << std::endl;
			return;
		}
		else if (isprint(static_cast<unsigned char>(literal[0]))) {
			c = literal[0];
			i = static_cast<int>(literal[0]);
			f = static_cast<float>(literal[0]);
			d = static_cast<double>(literal[0]);
		} else {
			std::cout << "It's something else" << std::endl; // ???
			return ;
		}
	} else if (literal.length() > 1)
	{
		if (literal == "nan" || literal == "+inf" || literal == "-inf") {
			std::cout << "nan inf -inf" << std::endl;
			// ? what for char, int, float, double?
			return ;
		}
		else if (literal == "nanf" || literal == "+inff" || literal == "-inff") {
			std::cout << "nanf inff -inff" << std::endl;
			// ? what for char, int, float, double?
			return ;
		}
		else {
			std::cout << "It's not a char" << std::endl;
			// integer, float, double checkers
			return ;
		}

	}

    // double b = 42.0;
    // int b = static_cast<int>(b);
    std::cout << "char: " << c << std::endl;  // Example char output
    std::cout << "int: " << i << std::endl;   // Example int output
    std::cout << "float: " << f << std::endl; // Example float output
    std::cout << "double: " << d << std::endl; // Example double output
    
    //  -inff, +inff, and nanf
    //  -inf, +inf, nan  (special float/double values)

    // "non displayable"
}
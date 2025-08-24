/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:53:43 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/24 11:55:38 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
#include <cmath>

ScalarConverter::ScalarConverter() { }

ScalarConverter::~ScalarConverter() { }

/* The (void)parameter cast is the standard C++98 way to explicitly 
mark a parameter as intentionally unused. */
ScalarConverter::ScalarConverter(const ScalarConverter& copy) {
	(void)copy;  // Suppress unused parameter warning
 }

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& assign) {
	(void)assign;  // Suppress unused parameter warning
	return *this;
}

struct Values
{
	char c;
	bool char_displayable;
	int i;
	bool int_displayable;
	float f;
	double d;

	/* C++98 constructor
	In C++, members must be initialized in the same order 
	they are declared in the class. */
    Values() : c(0), char_displayable(true), i(0), int_displayable(true), f(0.0f), d(0.0) {}

};

// The back() method was introduced in C++11. if (literal.back() == 'f')
static bool	isValidInt(std::string const &literal) {
	if (literal[literal.length() - 1] == 'f')
		return false;
	if ((literal[0] == '-' && !std::isdigit(static_cast<unsigned char>(literal[1]))))
		return false;
	size_t	start = 0;
	if (literal[0] == '-')
		start = 1;
	for (size_t i = start; i < literal.length(); i++)
	{
		if (literal[i] == '.' || !std::isdigit(static_cast<unsigned char>(literal[i])))
			return false;
	}
	return true;
}

/**
 * Checks if a string ends with 'f' (indicating it might be a float literal).
 * 
 * It's used to distinguish between float literals (3.14f) 
 * and double literals (3.14).
 */
static bool	mightBeFloat(std::string const &literal) {
	if (literal[literal.length() - 1] != 'f')
		return false;
	else
		return true;
}

// Output the results
static void display(Values & values) {
	std::cout << std::fixed << std::setprecision(2);
	if (values.char_displayable) {
		if (values.c == ' ')
    		std::cout << "char:   ' '" << std::endl;
		else
			std::cout << "char:   " << values.c << std::endl;
	}
	else {
		std::cout << "char:   " << "non displayable" << std::endl;
	}
	if (values.int_displayable) {
		std::cout << "int:    " << values.i << std::endl;
	}
	else {
		std::cout << "int:    " << "non displayable" << std::endl;
	}
	std::cout << "float:  " << std::right << values.f << "f" << std::endl; 
	std::cout << "double: " << std::right << values.d << std::endl;
}

static void	NaNInf(Values &values, const std::string &literal) {
	
	if (literal == "nanf" || literal == "+inff" || literal == "-inff") {
        if (literal == "nanf") {
            values.f = std::numeric_limits<float>::quiet_NaN();
        } else if (literal == "+inff") {
            values.f = std::numeric_limits<float>::infinity();
        } else if (literal == "-inff") {
            values.f = -std::numeric_limits<float>::infinity();
        }
        values.d = static_cast<double>(values.f);
    } else if (literal == "nan" || literal == "+inf" || literal == "-inf") {
        if (literal == "nan") {
            values.d = std::numeric_limits<double>::quiet_NaN();
        } else if (literal == "+inf") {
            values.d = std::numeric_limits<double>::infinity();
        } else if (literal == "-inf") {
            values.d = -std::numeric_limits<double>::infinity();
        }
        values.f = static_cast<float>(values.d);
    }
    
    if (std::isnan(values.f) || std::isnan(values.d) ||
        std::isinf(values.f) || std::isinf(values.d)) {
            std::cout << "char:   impossible" << std::endl;
            std::cout << "int:    impossible" << std::endl;
            std::cout << "float:  " << values.f << "f" << std::endl;
            std::cout << "double: " << values.d << std::endl;
    }
	
}

static int	isValidChar(std::string const &literal, Values & values) {
	
	if (isdigit(static_cast<unsigned char>(literal[0]))) {
		// C++98 alternative to std::stoi
		std::istringstream iss(literal);
		if (!(iss >> values.i) || !iss.eof()) {
			return 1;
		}
		values.char_displayable = false;
		values.f = static_cast<float>(values.i);
		values.d = static_cast<double>(values.i);
		return 0;
	} else if (isprint(static_cast<unsigned char>(literal[0]))) {
		values.c = literal[0];
		values.i = static_cast<int>(values.c);
		values.f = static_cast<float>(values.c);
		values.d = static_cast<double>(values.c);
		return 0;
	} 
	return 1;
}

/** take as a parameter a string representation of a C++ literal in its most common
form and output its value in the following series of scalar types */
// Takes the input from the command line.
int ScalarConverter::convert(std::string const &literal) {
	
	Values	values;
	if (literal.empty()) {
		std::cerr << "Error: Empty input." << std::endl;
		return 1;
	}
	else if (literal.length() == 1) {
		if (isValidChar(literal, values) == 1)
		{
			std::cout << "Invalid input" << std::endl;
			return 1;
		}
	}
	else if (literal.length() >= 1)
	{
		if (literal == "nan" || literal == "nanf" || literal == "+inf" || 
			literal == "+inff" || literal == "-inf" || literal == "-inff") {
				NaNInf(values, literal);
				return 0;
		} if (isValidInt(literal)) {
			// values.i = std::stoi(literal);
			// With C++98 alternative to stoi
			std::istringstream iss(literal);
			try {
				if (!(iss >> values.i) || !iss.eof()) {
					std::cerr << "Error: Invalid integer conversion." << std::endl;
					return 1;
				}
				values.f = static_cast<float>(values.i);
				values.d = static_cast<double>(values.i);
				// Check for precision loss in float conversion
				if (static_cast<int>(values.f) != values.i) {
					// Float lost precision, but this is standard C++ behavior
					std::cerr << "Warning: Float lost precision, but this is standard C++ behavior." << std::endl;
				}
				if (values.i >= 33 && values.i <= 126) {
					values.c = static_cast<char>(values.i);
				} else {
					values.char_displayable = false;
				}
			} catch (const std::out_of_range &e) {
				std::cerr << "Error: " << literal << " is out of range. what(): " << e.what() << std::endl;
				return 1;
			}
		}
		else if (mightBeFloat(literal)) // Checks if a string ends with 'f'
		{
			// C++98 alternative to std::stof //values.f = std::stof(literal, &pos);
			// The literal.length() - 1 is to remove the 'f' suffix from float literals
			std::istringstream iss(literal.substr(0, literal.length() - 1));
			try {
				if (!(iss >> values.f) || !iss.eof())	// !iss.eof() is true if 
														// there's leftover text after conversion
				{
					std::cerr << "Error: Invalid float conversion." << std::endl;
					return 1;
				}
				values.d = static_cast<double>(values.f);
				if (values.f > static_cast<float>(std::numeric_limits<int>::max()) || 
					values.f < static_cast<float>(std::numeric_limits<int>::min())) {
						values.int_displayable = false;
					} else {
						values.i = static_cast<int>(values.f);
					}
					if (values.i >= 33 && values.i <= 126) {
						values.c = static_cast<char>(values.i);
					} else {
						values.char_displayable = false;
					}
				} catch (...) {
					std::cerr << "Error: Invalid float conversion." << std::endl;
					return 1;
				}
			} else { // trying a double
				// C++98 alternative to std::stod // values.d = std::stod(literal, &pos);
				std::istringstream iss(literal);
				try {
					if (!(iss >> values.d) || !iss.eof()) {
						std::cerr << "Error: Invalid double conversion." << std::endl;
						return 1;
					}
					values.f = static_cast<float>(values.d);
					if (values.d > static_cast<double>(std::numeric_limits<int>::max()) || 
						values.d < static_cast<double>(std::numeric_limits<int>::min())) {
							values.int_displayable = false;
						} else {
							values.i = static_cast<int>(values.d);
						}
						if (values.i >= 33 && values.i <= 126) {
							values.c = static_cast<char>(values.i);
						} else {
							values.char_displayable = false;
						}
					} catch (...) {
						std::cerr << "Error: Invalid double conversion." << std::endl;
						return 1;
					}
				}
			}
			display(values);
			return 0;
}

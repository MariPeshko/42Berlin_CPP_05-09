/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:53:43 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/21 14:48:31 by mpeshko          ###   ########.fr       */
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

ScalarConverter::ScalarConverter(const ScalarConverter& copy) { }

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& assign) {
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

	// C++98 constructor
    Values() : c(0), char_displayable(true), int_displayable(true), i(0), f(0.0f), d(0.0) {}

};

static bool	isValidInt(std::string const &literal) {
	if (literal.back() == 'f')
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

static bool	mightBeFloat(std::string const &literal) {
	if (literal.back() != 'f')
		return false;
	else
		return true;
}

// Output the results
static void display(Values & values) {
	std::cout << std::fixed << std::setprecision(1);
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
	try {
		if (literal == "nanf" || literal == "+inff" || literal == "-inff") {
			values.f = std::stof(literal);
			values.d = static_cast<double>(values.f);
		} else if (literal == "nan" || literal == "+inf" || literal == "-inf") {
			values.d = std::stod(literal);
			values.f = static_cast<float>(values.d);
		} if (std::isnan(values.f) || std::isnan(values.d) ||
			std::isinf(values.f) || std::isinf(values.d)) {
				std::cout << "char:   impossible" << std::endl;
				std::cout << "int:    impossible" << std::endl;
				std::cout << "float:  " << values.f << "f" << std::endl;
				std::cout << "double: " << values.d << std::endl;
		}
	} catch (const std::exception& e) {
		// Conversion failed, continue to next validation check
	}
}

static int	isValidChar(std::string const &literal, Values & values) {
	
	if (isdigit(static_cast<unsigned char>(literal[0]))) {
		values.i = std::stoi(literal);
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
    
	Values values;
	
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
			try {
				values.i = std::stoi(literal);
				values.f = static_cast<float>(values.i);
				values.d = static_cast<double>(values.i);
			}
			catch (const std::out_of_range &e) {
				std::cerr << "Error: " << literal << " is out of range. what(): " << e.what() << std::endl;
				return 1;
			}
			if (values.i >= 33 && values.i <= 126) {
				values.c = static_cast<char>(values.i);
			} else
				values.char_displayable = false;
		} else if (mightBeFloat(literal)) {
			
			size_t pos = 0;
			try {
                values.f = std::stof(literal, &pos);
                values.d = static_cast<double>(values.f);
				if (values.f > static_cast<float>(std::numeric_limits<int>::max()) || 
					values.f < static_cast<float>(std::numeric_limits<int>::min())) {
						values.int_displayable = false;
				} else
					values.i = static_cast<int>(values.f);
				if (values.i >= 33 && values.i <= 126) {
					values.c = static_cast<char>(values.i);
				} else
					values.char_displayable = false;
    		} catch (...) {
				// invalid_argument or out_of_range
                std::cerr << "Error: Invalid float conversion." << std::endl;
                return 1;
        	}
			if (pos != (literal.size() - 1))
			{
				std::cout << "Invalid float input" << std::endl;
				return 1;
			}
			
		} else { // trying a double
			
			size_t pos = 0;
			try {
                values.d = std::stod(literal, &pos);
                values.f = static_cast<float>(values.d);
				if (values.d > static_cast<double>(std::numeric_limits<int>::max()) || 
					values.d < static_cast<double>(std::numeric_limits<int>::min())) {
						values.int_displayable = false;
				} else
					values.i = static_cast<int>(values.d);

				if (values.i >= 33 && values.i <= 126) {
					values.c = static_cast<char>(values.i);
				} else
					values.char_displayable = false;
            } catch (...) {
				// invalid_argument or out_of_range
				std::cerr << "Error: Invalid double conversion." << std::endl;
				return 1;
            }
			if (pos != (literal.size()))
			{
				std::cout << "Invalid input" << std::endl;
				return 1;
			}
			
		}
	}
	display(values);
	return 0;
}

/**
 * 
 * isdigit()
 * https://en.cppreference.com/w/cpp/string/byte/isdigit.html
 * 
 */

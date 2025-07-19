/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
#include <cmath>

struct Values
{
	char c;
	bool char_displayable;
	int i;
	float f;
	double d;

	// C++98 constructor
    Values() : c(0), char_displayable(true), i(0), f(0.0f), d(0.0) {}

};



static bool	isValidInt(std::string const &literal) {
	if (literal.back() == 'f')
		return false;
	if ((literal[0] == '-' && !std::isdigit(literal[1])))
		return false;
	size_t	start = 0;
	if (literal[0] == '-')
		start = 1;
	for (size_t i = start; i < literal.length(); i++)
	{
		if (literal[i] == '.' || !std::isdigit(literal[i]))
			return false;
	}
	return true;
}

static bool isValidNumDec(std::string const &numPart) {
	bool	dot = false;
	if ((numPart[0] == '-' && !std::isdigit(numPart[1])))
		return false;
	size_t	start = 0;
	if (numPart[0] == '-')
		start = 1;
	for (size_t i = start; i < numPart.length(); i++)
	{
		if (numPart[i] == '.' ) {
			if (dot == true)
				return false;
			dot = true;
		} else if (!std::isdigit(numPart[i]))
			return false;
	}
	return true;
}

static bool	isValidFloat(std::string const &literal) {
	if (literal.back() != 'f')
		return false;
	std::string numPart = literal.substr(0, literal.length() - 1);

	return isValidNumDec(numPart);
	
}

static bool	isValidDouble(std::string const &literal) {
	if (literal.back() == 'f')
		return false;

	return isValidNumDec(literal);

}

static void display(Values & values) {
	// Output the results
	std::cout << std::fixed << std::setprecision(1);
	if (values.char_displayable) {
		std::cout << "char:   " << values.c << std::endl;
	}
	else {
		std::cout << "char:   " << "non displayable" << std::endl;
	}
	std::cout << "int:    " << std::right << values.i << std::endl;
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

static int	one_char(std::string const &literal, Values & values) {
	
	if(isdigit(static_cast<unsigned char>(literal[0])))
	{
		try {
			values.i = std::stoi(literal);
			values.f = static_cast<float>(values.i);
			values.d = static_cast<double>(values.i);
		}
		catch (const std::out_of_range &e) {
			std::cerr << "Error: " << literal << " is out of range. what(): " << e.what() << std::endl;
			return 1;
		}
		values.char_displayable = false;
		return 0;
	} else {
		values.c = literal[0];
		if (isspace(static_cast<unsigned char>(literal[0]))) {
			values.char_displayable = false;
		}
		/* if (isprint(static_cast<unsigned char>(literal[0]))) {
			values.c = literal[0];
		} */
		values.i = static_cast<int>(values.c);
		values.f = static_cast<float>(values.c);
		values.d = static_cast<double>(values.c);
	}
	return 0;
}

/** take as a parameter a string representation of a C++ literal in its most common
form and output its value in the following series of scalar types */
// Takes the input from the command line.
int ScalarConverter::convert(std::string const &literal) {
    
	Values values;
	
	if (literal.empty()) {
        std::cerr << "Error: Empty input." << std::endl;
        return 1;
    } if (literal.length() == 1) {
		if (one_char(literal, values) == 1)
			return 1;		
	}
	else if (literal.length() > 1)
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
		} else if (isValidFloat(literal)) {
			try {
                values.f = std::stof(literal);
                values.d = static_cast<double>(values.f);
                values.i = static_cast<int>(values.f);
                values.char_displayable = false;
    		} catch (const std::exception& e) {
                std::cerr << "Error: Invalid float conversion." << std::endl;
                return 1;
        	}
		} else if (isValidDouble(literal)) {
			try {
                values.d = std::stod(literal);
                values.f = static_cast<float>(values.d);
                values.i = static_cast<int>(values.d);
                values.char_displayable = false;
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid double conversion." << std::endl;
                return 1;
            }
		}
		else {
			std::cout << "Invalid input" << std::endl; // Do I need it?
			return 1;
		}
	}
	display(values);
	return 0;		
}

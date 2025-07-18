/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

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

static void NaNInf(Values &values, const std::string &literal) {
	if (literal == "nanf" || literal == "nan") {
				values.f = std::numeric_limits<float>::quiet_NaN();
				values.d = std::numeric_limits<double>::quiet_NaN();
			} else if (literal == "-inff" || literal == "-inf") {
				values.f = -std::numeric_limits<float>::infinity();
				values.d = -std::numeric_limits<double>::infinity();
			} else if (literal == "+inff" || literal == "+inf") {
				values.f = std::numeric_limits<float>::infinity();
				values.d = std::numeric_limits<double>::infinity();
			}
			std::cout << "char:   impossible" << std::endl;
			std::cout << "int:    impossible" << std::endl;
			std::cout << "float:  " << values.f << "f" << std::endl;
			std::cout << "double: " << values.d << std::endl;
}

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

static bool	isValidFloat(std::string const &literal) {
	if (literal.back() != 'f')
		return false;
	return true;
}

static bool	isValidDouble(std::string const &literal) {
	if (literal.back() == 'f')
		return false;
	return true;
}

static void display(Values & values) {
	// Output the results
	std::cout << std::fixed << std::setprecision(2);
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

/** take as a parameter a string representation of a C++ literal in its most common
form and output its value in the following series of scalar types */
// Takes the input from the command line.
int ScalarConverter::convert(std::string const &literal) {
    
	Values values;
	
    if (literal.empty()) {
        std::cerr << "Error: Empty input." << std::endl;
        return 1;
    }
	// int or ascii
    if (literal.length() == 1) {
		if (isspace(static_cast<unsigned char>(literal[0]))) {
			values.char_displayable = false;
		}
		if (isprint(static_cast<unsigned char>(literal[0]))) {
			values.c = literal[0];
		}
		values.i = static_cast<int>(literal[0]);
		values.f = static_cast<float>(literal[0]);
		values.d = static_cast<double>(literal[0]);
	} else if (literal.length() > 1)
	{
		if (isValidInt(literal)) {
			try {
				values.i = std::stoi(literal);
				values.f = static_cast<float>(values.i);
				values.d = static_cast<double>(values.i);
			}
			catch (const std::out_of_range &e) {
				std::cerr << "Error: " << literal << " is out of range. what(): " << e.what() << std::endl;
				return 1;
			}
			if (values.i >= 0 && values.i <= 127) {
				values.c = static_cast<char>(values.i);
			} else {
				values.char_displayable = false;
			}
		}
		else if (literal == "nan" || literal == "+inf" || literal == "-inf" || 
         literal == "nanf" || literal == "+inff" || literal == "-inff") {
			NaNInf(values, literal);
			return 0;
		}
		/* else if (isValidFloat(literal)) {
			std::cout << "It's a float\n";
			try {
                values.f = std::stof(literal);
                values.d = static_cast<double>(values.f);
                values.i = static_cast<int>(values.f);
                values.char_displayable = false;
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid float conversion." << std::endl;
                return 1;
            }
		}
		else if (isValidDouble(literal)) {
			std::cout << "It's a double\n";
			return 0;
		} */
		}
		else {
			std::cout << "Invalid input" << std::endl;
			return 1;
		}
		display(values);						
		return 0;								
}
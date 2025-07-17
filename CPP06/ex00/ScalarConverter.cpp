/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:58:57 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/17 20:26:03 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>

/** take as a parameter a string representation of a C++ literal in its most common
form and output its value in the following series of scalar types */
// Takes the input from the command line.
void ScalarConverter::convert(std::string const &literal) {
    
    std::cout << "char: 'c'" << std::endl;  // Example char output
    std::cout << "int: 42" << std::endl;   // Example int output
    std::cout << "float: 42.0f" << std::endl; // Example float output
    std::cout << "double: 42.0" << std::endl; // Example double output
    
    //  -inff, +inff, and nanf
    //  "nan", "inf", "-inf" (special float/double values)

    // "non displayable"
}
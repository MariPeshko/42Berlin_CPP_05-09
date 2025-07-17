/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:17:13 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/12 14:38:07 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "AForm.hpp"
#include <iostream>
#include <fstream>
#include <string>

// Default
ShrubberyCreationForm::ShrubberyCreationForm( void ) : 
	AForm("ShrubberyCreationForm", 145, 137),
	_target("DefaultTarget")
{ 
	std::cout << "Default constructor of ShrubberyCreationForm class type\n";
	std::cout << this->_target << " is created" << std::endl;
}

// Parametrized
ShrubberyCreationForm::ShrubberyCreationForm( std::string target ) :
	AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
	std::cout << "Constructor of ShrubberyCreationForm class type\n";
	std::cout << this->_target << " is instantiated" << std::endl;
}

// Copy Constructor
ShrubberyCreationForm::ShrubberyCreationForm ( ShrubberyCreationForm const & src )
	: AForm(src), _target(src._target)
{		
	std::cout << "Copy Constructor of ShrubberyCreationForm class type" << std::endl;
	std::cout << this->_target << " is instantiated as a copy of " << src.getTarget();
	std::cout << std::endl;
}

// Assignment operator 
ShrubberyCreationForm &	ShrubberyCreationForm::operator=( ShrubberyCreationForm const &assign ) {
	
	std::cout << "Assignment operator of ShrubberyCreationForm class type" << std::endl;
	if (this != &assign) {
		AForm::operator=(assign); // Call base class assignment
		this->_target = assign.getTarget();
	}
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << "Destructor of class type ShrubberyCreationForm" << std::endl;
};

/**
 * std::string::c_str [ cplusplus.com ]
 * Get C string equivalent
 * Returns a pointer to an array that contains a null-terminated sequence 
 * of characters (i.e., a C-string) representing the current value of the string object.
*/
void			ShrubberyCreationForm::action() const {

	std::string		filename = this->_target + "_shrubbery";
	std::ofstream	f(filename.c_str());

	if (!f || !f.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}
	
	f << "_ _ _ _ _ _ _ SHRUBBERY TREE _ _ _ _ _ _ _\n" << std::endl;
	f << "              ,@@@@@@@," << std::endl;
	f << "      ,,,.   ,@@@@@@/@@,  .oo8888o." << std::endl;
	f << "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o" << std::endl;
	f << "   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'" << std::endl;
	f << "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'" << std::endl;
	f << "   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'" << std::endl;
	f << "   `&%\\ ` /%&'    |.|        \\ '|8'" << std::endl;
	f << "       |o|        | |         | |" << std::endl;
	f << "       |.|        | |         | |" << std::endl;
	f << "    \\/ ._\\//_/__/  ,\\_//__\\/.  \\_//__/_" << std::endl;
				  
	
	f.close();
}

const std::string&	ShrubberyCreationForm::getTarget() const {
	return this->_target;
}

std::ostream &operator<<(std::ostream &o, const ShrubberyCreationForm &form) {
	o << "< < < ";
	// Reuse base class operator<<
	o << static_cast<const AForm &>(form);
	o << "Target: " << form.getTarget();
	o << " > > >" << std::endl;
	return o;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:56:17 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/12 18:41:38 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include "AForm.hpp"
#include <iostream>
#include <string>

// Default
PresidentialPardonForm::PresidentialPardonForm( void ) : 
	AForm("PresidentialPardonForm", 25, 5),
	_target("DefaultTarget")
{ 
	std::cout << "Default constructor of PresidentialPardonForm class type\n";
	std::cout << this->_target << " is created" << std::endl;
}

// Parametrized
PresidentialPardonForm::PresidentialPardonForm( std::string target ) :
	AForm("PresidentialPardonForm", 25, 5), _target(target)
{
	std::cout << "Constructor of PresidentialPardonForm class type\n";
	std::cout << this->_target << " is instantiated" << std::endl;
}

// Copy Constructor
PresidentialPardonForm::PresidentialPardonForm ( PresidentialPardonForm const & src )
	: AForm(src), _target(src._target)
{		
	std::cout << "Copy Constructor of PresidentialPardonForm class type";
	std::cout << std::endl;
	std::cout << this->_target << " is instantiated as a copy of ";
	std::cout << src.getTarget() << std::endl;
}

// Assignment operator 
PresidentialPardonForm &	PresidentialPardonForm::operator=( PresidentialPardonForm const &assign ) {
	
	std::cout << "Assignment operator of PresidentialPardonForm class type";
	std::cout << std::endl;
	if (this != &assign) {
		AForm::operator=(assign); // Call base class assignment
		this->_target = assign.getTarget();
	}
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << "Destructor of class type PresidentialPardonForm" << std::endl;
};

/**
 * std::string::c_str [ cplusplus.com ]
 * Get C string equivalent
 * Returns a pointer to an array that contains a null-terminated sequence 
 * of characters (i.e., a C-string) representing the current value 
 * of the string object.
*/
void			PresidentialPardonForm::action() const {
	std::cout << this->getTarget() << " has been pardoned by Zaphod Beeblebrox.\n";
	std::cout << std::endl;
}

const std::string&	PresidentialPardonForm::getTarget() const {
	return this->_target;
}

std::ostream &operator<<(std::ostream &o, const PresidentialPardonForm &form) {
	o << "< < < ";
	// Reuse base class operator<<
	o << static_cast<const AForm &>(form);
	o << "Target: " << form.getTarget();
	o << " > > >" << std::endl;
	return o;
}


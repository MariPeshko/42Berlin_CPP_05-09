/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:49:58 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/12 18:41:08 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "AForm.hpp"
#include <iostream>
#include <string>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

// Default
RobotomyRequestForm::RobotomyRequestForm( void ) : 
	AForm("RobotomyRequestForm", 72, 45),
	_target("DefaultTarget")
{ 
	std::cout << "Default constructor of RobotomyRequestForm class type\n";
	std::cout << this->_target << " is created" << std::endl;
}

// Parametrized
RobotomyRequestForm::RobotomyRequestForm( std::string target ) :
	AForm("RobotomyRequestForm", 72, 45), _target(target)
{
	std::cout << "Constructor of RobotomyRequestForm class type\n";
	std::cout << this->_target << " is instantiated" << std::endl;
}

// Copy Constructor
RobotomyRequestForm::RobotomyRequestForm ( RobotomyRequestForm const & src )
	: AForm(src), _target(src._target)
{		
	std::cout << "Copy Constructor of RobotomyRequestForm class type" << std::endl;
	std::cout << this->_target << " is instantiated as a copy of ";
	std::cout << src.getTarget() << std::endl;
}

// Assignment operator 
RobotomyRequestForm &	RobotomyRequestForm::operator=( RobotomyRequestForm const &assign ) {
	
	std::cout << "Assignment operator of RobotomyRequestForm class type" << std::endl;
	if (this != &assign) {
		AForm::operator=(assign); // Call base class assignment
		this->_target = assign.getTarget();
	}
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << "Destructor of class type RobotomyRequestForm" << std::endl;
};

/**
 * std::string::c_str [ cplusplus.com ]
 * Get C string equivalent
 * Returns a pointer to an array that contains a null-terminated sequence 
 * of characters (i.e., a C-string) representing the current value 
 * of the string object.
 * 
 * @p srand() Seeds the pseudo-random number generator used by std::rand() 
 * with the value seed.
 * @p rand() Returns a pseudo-random integral value from 
 * the range [​0​, RAND_MAX].
*/
void			RobotomyRequestForm::action() const {

	std::cout << "Bzzzz... drrrrr... burrrr... (drilling noises)" << std::endl;
	std::srand(std::time(0));  // use current time as seed for random generator
	
	if ((std::rand() % 2) == 0) {
		std::cout << this->getTarget() << " has been robotomized successfully.\n";
		std::cout << std::endl;
	}	else {
		std::cout << "The robotomy failed.\n" << std::endl;
	}
}

const std::string&	RobotomyRequestForm::getTarget() const {
	return this->_target;
}

std::ostream &operator<<(std::ostream &o, const RobotomyRequestForm &form) {
	o << "< < < ";
	// Reuse base class operator<<
	o << static_cast<const AForm &>(form);
	o << "Target: " << form.getTarget();
	o << " > > >" << std::endl;
	return o;
}


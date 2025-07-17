/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:37:04 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/12 21:35:15 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::Intern( void )
{
	std::cout << "Constructor of Intern class type" << std::endl;
}

// Copy Constructor
Intern::Intern ( Intern const & src )
{ 
	std::cout << "Copy Constructor of Intern class type" << std::endl;
}

// Assignment operator 
Intern &	Intern::operator=( Intern const &assign ) {
	std::cout << "Assignment Operator of Intern class type" << std::endl;
	return *this;
}

Intern::~Intern() {
	std::cout << "Destructor of class type Intern" << std::endl;
}

AForm*	Intern::ShrubCreation(std::string formTarget) {
	std::cout << "Intern creates ShrubberyCreationForm" << std::endl;
	return new ShrubberyCreationForm(formTarget);
}

AForm*	Intern::RobotomyCreation(std::string formTarget) {
	std::cout << "Intern creates RobotomyRequestForm" << std::endl;
    return new RobotomyRequestForm(formTarget);
}

AForm*	Intern::PresidentialCreation(std::string formTarget) {
	std::cout << "Intern creates PresidentialPardonForm" << std::endl;
    return new PresidentialPardonForm(formTarget);
}

AForm*	Intern::makeForm(std::string formName, std::string formTarget) {
	
	static AForm*	(Intern::*f[3])(std::string) = { 
		&Intern::ShrubCreation, 
		&Intern::RobotomyCreation,
		&Intern::PresidentialCreation
	};
	static const std::string	AvailableForms[3] = {
		"shrubbery form",
		"robotomy request",
		"presidential pardon"
	};

	for (int i = 0; i < 3; i++)	{
		if (formName == AvailableForms[i]) {
			return (this->*f[i])(formTarget);
		}
	}
	std::cerr << "There is no " << formName << " form in our bureau.";
	std::cerr << std::endl;
	return nullptr;
}

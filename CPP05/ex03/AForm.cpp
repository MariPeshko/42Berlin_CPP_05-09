/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:22:19 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/12 21:20:55 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <iostream>
#include <exception>
#include <string>


AForm::AForm( void ) :
	_name("DefaultForm"), _signed(false), _formGrade(1), _formGradeExe(10)
{ }


AForm::AForm( std::string name, int grade, int exgrade ) :
	_name(name), _signed(false), _formGrade(grade), _formGradeExe(exgrade)
{
	std::cout << "Constructor of AForm  abstract class type" << std::endl;
	if (this->_formGrade > 150 || this->_formGradeExe > 150) {
		std::cerr << "On attempt to construct a form object... \n";
		throw AForm::GradeTooLowException();
	}
	else if (this->_formGrade < 1 || this->_formGradeExe < 1) {
		std::cerr << "On attempt to construct a form object... \n";
		throw AForm::GradeTooHighException();
	}
}

// Copy Constructor
AForm::AForm ( AForm const & src ) :
	_formGrade(src.getGrade()), _name(src.getName()), 
	_formGradeExe(src.getExGrade()), _signed(src.getBoolSigned())	{
		
	std::cout << "Copy Constructor of AForm class type" << std::endl;
}

// Assignment operator 
AForm &	AForm::operator=( AForm const &assign ) {
	
	std::cout << "Assignment operator of AForm class type" << std::endl;
	if (this != &assign) {
		this->_signed = assign.getBoolSigned();
	}
    return *this;
}

AForm::~AForm() {
	std::cout << "Destructor of class type AForm" << std::endl;
}

unsigned int AForm::getGrade() const {
	return this->_formGrade;
}

unsigned int AForm::getExGrade() const {
	return this->_formGradeExe;
}

const std::string& AForm::getName() const {
	return this->_name;
}

const std::string AForm::getSigned() const {
	if (this->_signed == false)
		return "False.";
	return "True.";
}

bool	AForm::getBoolSigned() const {
	return this->_signed;
}

void	AForm::beSigned(Bureaucrat &b) {
	if (b.getGrade() <= this->_formGrade)
		this->_signed = true;
	else
		throw AForm::GradeTooLowException();
}

void	AForm::execute(Bureaucrat const & executor) const {
	std::cout << "An attempt to execute " << this->getName() << "..." << std:: endl;
	std::cout << "Validating signature on the form...\n";
	if(this->_signed == false) {
		throw	AForm::NotSignedException();
	}
	std::cout << "Validating grade of the Buraucrat " << executor.getName() << "...\n";
	if(executor.getGrade() > this->getExGrade()) {
		throw	AForm::GradeTooLowException();
	}
	std::cout << executor.getName() << " executes " << this->getName();
	std::cout << " for a target " << getTarget() << std::endl;
	action();
}


std::ostream &	operator<<(std::ostream &o, AForm const &i) {

    o << "AForm's name " << i.getName() << "\n";
	o << "Grade required to sign " << i.getGrade();
    o << ", grade to execute " << i.getExGrade() << ".\n";
	o << "Signed: " << i.getSigned() << std::endl;
    return o;

}

const char* AForm::GradeTooHighException::what() const throw() {
	return "| | Form Exception | | Grade is too high!";
}

const char* AForm::GradeTooLowException::what() const throw () {
	return "| | Form Exception | | Grade is too low!";
}

const char* AForm::NotSignedException::what() const throw () {
	return "| | Form Exception | | The form isn't signed.";
}

/**
 * Notes
 * 
 * Modern C++ (C++11 and later)
 * Instead of throw(), you should use noexcept:
 * 
 * 'const char* what() const noexcept;'
 * 
 */

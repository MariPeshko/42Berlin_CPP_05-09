/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:14:42 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/24 12:50:30 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <exception>
#include <string>

Form::Form( void ) :
	_name("DefaultForm"), _signed(false), _formGrade(1), _formGradeExe(10)
{ };


Form::Form( std::string name, int grade, int exgrade ) :
	_name(name), _signed(false), _formGrade(grade), _formGradeExe(exgrade)
{
	if (this->_formGrade > 150 || this->_formGradeExe > 150) {
		std::cerr << "On attempt to construct a form object... \n";
		throw Form::GradeTooLowException();
	}
	else if (this->_formGrade < 1 || this->_formGradeExe < 1) {
		std::cerr << "On attempt to construct a form object... \n";
		throw Form::GradeTooHighException();
	}
};

// Copy Constructor
Form::Form ( Form const & src ) :
	_name(src.getName()),
	 _signed(src.getBoolSigned()),
	_formGrade(src.getGrade()),
	_formGradeExe(src.getExGrade())	{
		
		std::cout << "Copy Constructor of Form class type" << std::endl;
}

// Assignment operator 
Form &	Form::operator=( Form const &assign ) {
	
	std::cout << "Assignment operator of Form class type" << std::endl;
	if (this != &assign) {
		this->_signed = assign.getBoolSigned();
	}
    return *this;
}

Form::~Form() {
	std::cout << "Destructor of class type Form" << std::endl;
};

int Form::getGrade() const {
	return this->_formGrade;
}

int Form::getExGrade() const {
	return this->_formGradeExe;
}

const std::string& Form::getName() const {
	return this->_name;
}

const std::string Form::getSigned() const {
	if (this->_signed == false)
		return "False.";
	return "True.";
}

bool	Form::getBoolSigned() const {
	return this->_signed;
}

void	Form::beSigned(Bureaucrat &b) {
	if (b.getGrade() <= this->_formGrade)
		this->_signed = true;
	else
		throw Form::GradeTooLowException();
}

std::ostream &	operator<<(std::ostream &o, Form const &i) {

    o << "Form's name " << i.getName() << "\n";
	o << "Grade required to sign " << i.getGrade();
    o << ", grade to execute " << i.getExGrade() << ".\n";
	o << "Signed: " << i.getSigned() << std::endl;
    return o;

}

const char* Form::GradeTooHighException::what() const throw() {
	return "_ _ _Form Exception_ _ _ Grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw () {
	return "_ _ _Form Exception_ _ _ Grade is too low!";
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

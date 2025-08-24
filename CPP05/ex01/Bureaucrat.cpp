/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:14:34 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/24 12:51:55 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <exception>

Bureaucrat::Bureaucrat( void ) :
	_grade(75), _name("Default")
{ };


Bureaucrat::Bureaucrat( int grade, std::string name ) :
	_grade(grade), _name(name)
{ 
	if (this->_grade > 150)
	{
		std::cerr << "On attempt to construct an object with a grade ";
		std::cerr << grade << std::endl;
		throw Bureaucrat::GradeTooLowException();
	}
	else if (this->_grade < 1) {
		std::cerr << "On attempt to construct an object with a grade ";
		std::cerr << grade << std::endl;
		throw Bureaucrat::GradeTooHighException();
	}
};

// Copy Constructor
Bureaucrat::Bureaucrat ( Bureaucrat const & src ) :
	_grade(src.getGrade()), _name(src.getName())	{ }

// Assignment operator 
Bureaucrat &	Bureaucrat::operator=( Bureaucrat const &assign ) {
	
	if (this != &assign) {
		this->_grade = assign._grade;
	}
    return *this;
}

Bureaucrat::~Bureaucrat() {
	std::cout << "Destructor of class type Bureaucrat" << std::endl;
};

int	Bureaucrat::getGrade() const {
	return this->_grade;
}

const std::string& Bureaucrat::getName() const {
	return this->_name;
}

std::ostream &	operator<<(std::ostream &o, Bureaucrat const &i) {

    o << i.getName() << ", bureaucrat grade " << i.getGrade();
	o << "." << std::endl;
    return o;

}

void	Bureaucrat::upgrade() {
	if (this->_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
}

void	Bureaucrat::downgrade() {
	if (this->_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
}

void	Bureaucrat::signForm(Form &f) {
	if (this->_grade <= f.getGrade()) {
		std::cout << this->getName() << " signed " << f.getName();
		std::cout << std::endl;
	} else {
		std::cout << this->getName() << " couldn't signed " << f.getName();
		std::cout << " because " << this->getName() << "\'s grade ";
		std::cout << "is not high enough." << std::endl;
	}
		
	f.beSigned(*this);
}


// override the what() method
// throw() - This is an exception specification (old C++ syntax).
// It means that this function is guaranteed not to throw any exceptions.
const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "_ _ _Bur Exception_ _ _ Grade too high!";
}

// override the what() method
// throw() - This is an exception specification (old C++ syntax).
// It means that this function is guaranteed not to throw any exceptions.
const char* Bureaucrat::GradeTooLowException::what() const throw () {
	return "_ _ _Bur Exception_ _ _ Grade too low!";
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

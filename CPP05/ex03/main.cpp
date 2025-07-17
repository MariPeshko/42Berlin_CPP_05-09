/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:14:39 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/12 21:38:55 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"
#include <iostream>
#include <exception>

/**
 * function makeForm() has valid parameters:
 * "shrubbery form",
 * "robotomy request",
 * "presidential pardon"
 */

int	main(void) {
	
	std::cout << "TEST 01" << std::endl;
	std::cout << std::endl;
	Intern	Newbie;
	AForm *FormInvalid = Newbie.makeForm("BlaBlaCar", "Home");
	if (FormInvalid)
		std::cout << FormInvalid->getExGrade() << std::endl;
	else
		std::cout << "Form creation failed. *FormInvalid is nullptr" << std::endl;
	delete FormInvalid;
	std::cout << std::endl;
	
	std::cout << "TEST 02" << std::endl;
	std::cout << std::endl;
	AForm *Form1 = Newbie.makeForm("shrubbery form", "Home");
	delete Form1;
	std::cout << std::endl;

	std::cout << "TEST 03" << std::endl;
	std::cout << std::endl;
	AForm *Form2 = Newbie.makeForm("robotomy request", "Douglas Adams");
	delete Form2;
	std::cout << std::endl;

	std::cout << "TEST 04" << std::endl;
	std::cout << std::endl;
	AForm *Form3 = Newbie.makeForm("presidential pardon", "Arthur Dent");
	delete Form3;
	std::cout << std::endl;

	return 0;

}

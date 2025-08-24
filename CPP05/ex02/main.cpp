/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:14:39 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/24 20:07:31 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <exception>
#include <unistd.h> // for usleep()

static void	test_Buraucrat_executes_sh() {
		
	{
		std::cout << "_ _ Valid executeForm - Buraucrat class attribute_ _" << std::endl;
		ShrubberyCreationForm	garden("Yard");
		std::cout << garden << std::endl;
		Bureaucrat	gardener(1, "Gardener");
		try {
			gardener.signForm(garden);
			gardener.executeForm(garden);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	{
		std::cout << "_ _ Invalid executeForm - Buraucrat class attribute_ _" << std::endl;
		ShrubberyCreationForm	garden("Yard");
		Bureaucrat	gardener(1, "Gardener");
		try {
			//gardener.signForm(garden);
			gardener.executeForm(garden);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	{
		std::cout << "_ _ Invalid executeForm - Buraucrat class attribute_ _" << std::endl;
		ShrubberyCreationForm	garden("Yard");
		Bureaucrat	gardener(138, "Gardener");
		try {
			gardener.signForm(garden);
			gardener.executeForm(garden);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
}

static void	test_form_is_executed_sh() {
	{
		std::cout << "_ _ Valid execute() - Form class attribute_ _" << std::endl;
		ShrubberyCreationForm	garden("Garden");
		std::cout << garden << std::endl;
		Bureaucrat	gardener(100, "Gardener");
		try {
			gardener.signForm(garden);
			garden.execute(gardener);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	{
		std::cout << "_ _ Not signed _ _" << std::endl;
		try {
			ShrubberyCreationForm	garden("Garden");
			Bureaucrat	gardener(146, "Gardener");
			//gardener.signForm(garden);
			garden.execute(gardener);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	{
		std::cout << "_ _ Grade too low to execute _ _" << std::endl;
		try {
			ShrubberyCreationForm	garden("Garden");
			Bureaucrat	gardener(138, "Gardener");
			gardener.signForm(garden);
			garden.execute(gardener);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
}

int	main(void) {
	
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	test_form_is_executed_sh();
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	test_Buraucrat_executes_sh();
	
	Bureaucrat	TheGreatest(1, "TheGreatest");
	Bureaucrat	Six(6, "Six");

	RobotomyRequestForm	buddy("buddy");
	std::cout << buddy;
	TheGreatest.signForm(buddy);
	TheGreatest.executeForm(buddy);
	usleep(1100000); // 1100 milliseconds = 1,100,000 microseconds
	TheGreatest.executeForm(buddy);
	usleep(1100000);
	TheGreatest.executeForm(buddy);
	usleep(1100000);
	TheGreatest.executeForm(buddy);
	
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	PresidentialPardonForm	Volodymyr("Volodymyr");
	std::cout << Volodymyr;
	TheGreatest.signForm(Volodymyr);
	TheGreatest.executeForm(Volodymyr);
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	Six.executeForm(Volodymyr);

	return 0;

}
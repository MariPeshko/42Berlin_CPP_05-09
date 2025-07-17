/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:14:39 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/10 21:58:37 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>
#include <exception>

static void	test_basic() {
	{
	std::cout << "OCF tests" << std::endl;
	Form Doc1("Doc1", 2, 20);
	std::cout << Doc1 << std::endl;

	Form Doc2(Doc1);
	std::cout << Doc2 << std::endl;

	Form Doc3;
	std::cout << Doc3 << std::endl;

	Doc3 = Doc1;
	std::cout << Doc3 << std::endl;
	}
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	try {
		Form	TooLowGrade("TooLowGrade", 152, 15);	
	} catch ( const std::exception &e) {
		std::cerr << e.what() << std:: endl;
	}
	try {
		Form	TooLowExGrade("TooLowExGrade", 15, 151);	
	} catch ( const std::exception &e) {
		std::cerr << e.what() << std:: endl;
	}  
	try {
		Form	TooHighGrade("TooHighGrade", -1, 15);	
	} catch ( const std::exception &e) {
		std::cerr << e.what() << std:: endl;
	}
	try {
		Form	TooHighExGrade("TooHighExGrade", 15, -1);	
	} catch ( const std::exception &e) {
		std::cerr << e.what() << std:: endl;
	}
}

static void test_Form_beSigned() {
	try {
		Bureaucrat	Bob(1, "Bob");
		Form		Anmeldung("Anmeldung", 1, 10);
		std::cout << Anmeldung << std::endl;
		Anmeldung.beSigned(Bob);
		std::cout << Anmeldung << std::endl;	
	} catch ( std::exception &e ) {
		std::cerr << e.what() << std:: endl;
	}
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	try {
		Bureaucrat	Nicolaus(15, "Nicolaus");
		Form		Meld("Meldebescheinigung", 14, 10);
		std::cout << Meld << std::endl;
		Meld.beSigned(Nicolaus);
		std::cout << Meld << std::endl;
	} catch ( std::exception &e ) {
		std::cerr << e.what() << std:: endl;
	}
}

void	test_Bur_signForm() {
	{
		Bureaucrat	Bob(1, "Bob");
		Form		Anmeldung("Anmeldung", 1, 10);
		Bob.signForm(Anmeldung);
	}
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	{
		try {
			Bureaucrat	Bob(2, "Bob");
			Form		Anmeldung("Anmeldung", 1, 10);
			Bob.signForm(Anmeldung);
		} catch (std::exception &e) {
			std::cerr << e.what() << std:: endl;
		}
		
	}
}


int	main(void) {
	
	//test_basic();
	//test_Form_beSigned();
	test_Bur_signForm();
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	return 0;

}
#include "Bureaucrat.hpp"
#include <iostream>
#include <exception>

static void	testGrade( void ) {

	Bureaucrat	Andrew(150, "Andrew");
	std::cout << Andrew ;

	try {
		std::cout << "Invalid downgrade" << std::endl;
		Andrew.downgrade();
	} catch (const std::exception& e) {
		std::cerr << "\n" << e.what() << "\n" << std::endl;
	}
	std::cout << Andrew << std::endl;

	std::cout << "Valid upgrade" << std::endl;
	Andrew.upgrade();
	std::cout << Andrew ;

	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;

	Bureaucrat	Patrick(1, "Patrick");
	std::cout << Patrick ;

	try {
		std::cout << "Invalid upgrade" << std::endl;
		Patrick.upgrade();
	} catch (const std::exception& e) {
		std::cerr << "\n" << e.what() << "\n" << std::endl;
	}
	std::cout << Patrick << std::endl;

	std::cout << "Valid downgrade" << std::endl;
	Patrick.downgrade();
	std::cout << Patrick ;

}

void	testConstructor( void ) {

	try {
		Bureaucrat Scarlett(151, "Scarlett");
	} catch (const std::exception& e) {
		std::cerr << "\n" << e.what() << "\n" << std::endl;
	}
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	try {
		Bureaucrat Elsa(0, "Elsa");
	} catch (const std::exception& e) {
		std::cerr << "\n" << e.what() << "\n" << std::endl;
	}


}

int	main(void) {

	testGrade();
	std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ " << std:: endl << std:: endl;
	testConstructor();

	return 0;

}
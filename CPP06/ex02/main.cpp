/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:30:40 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/21 14:59:49 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>    // for time()
#include <cstdlib>  // for rand() and srand()

class Base
{

	public:
    	virtual ~Base( void ) {};

};

class A : public Base {};
class B : public Base {};
class C : public Base {};

class T : public Base {};

/**
 * It randomly instantiates A, B, or C and returns the instance as a Base
 * pointer. Feel free to use anything you like for the random choice 
 * implementation.
 */
static Base *	generate(void) {
	
	std::srand(std::time(0));
	int random = rand() % 3;
	
	switch (random) {
		case 0: {
			std::cout << "Generation of new A" << std::endl;
			std::cout << "Returns a base type pointer..." << std::endl;
			return new A();
		}
		case 1: {
			std::cout << "Generation of new B" << std::endl;
			std::cout << "Returns a base type pointer..." << std::endl;
			return new B();
		}
		case 2: {
			std::cout << "Generation of new C" << std::endl;
			std::cout << "Returns a base type pointer..." << std::endl;
			return new C();
		}
		default:
			return new A(); // Fallback (should never be reached)
    }
	
}

/** 
 * It prints the actual type of the object pointed to by p: "A", "B", or "C".
 */
static void		identify(Base* p) {
	
	if (A *a = dynamic_cast<A *>(p)) {
		std::cout << "The adress of a downcasted pointer: " << a << std::endl;
		std::cout << "Actual type is A" << std::endl;
		return ;
	}
	if (B *b = dynamic_cast<B *>(p)) {
		std::cout << "The adress of a downcasted pointer: " << b << std::endl;
		std::cout << "Actual type is B" << std::endl;
		return ;
	}
	if (C *c = dynamic_cast<C *>(p)) {
		std::cout << "The adress of a downcasted pointer: " << c << std::endl;
		std::cout << "Actual type is C" << std::endl;
		return ;
	}
	std::cout << "Unknown pointer type" << std::endl;
}

/**
 * It prints the actual type of the object referenced by p: "A", "B", or "C". 
 * Using a pointer inside this function is forbidden.
 */
static void	identify(Base& p) {
	try {
		A & a = dynamic_cast<A &>(p);
		std::cout << "Indentified a reference of a type A" << std::endl;
		return ;
	}
	catch ( std::bad_cast &bc ) { }
	try {
		B & b = dynamic_cast<B &>(p);
		std::cout << "Indentified a reference of a type B" << std::endl;
		return ;
	}
	catch ( std::bad_cast &bc ) { }
	try {
		C & b = dynamic_cast<C &>(p);
		std::cout << "Indentified a reference of a type C" << std::endl;
		return ;
	}
	catch ( std::bad_cast &bc ) { }
	std::cout << "Unknown reference type" << std::endl;
}

int	main ( void ) {
	
	Base *a = generate();
	std::cout << "The adress of a base type pointer:  " << a << std::endl;
	identify(a);
	identify(*a);
	delete a;
	
/* 	std::cout << "_ _ _ _ TEST CLASS _ _ _ _" << std:: endl;
	T *t = new T;
	identify(t);
	identify(*t);
	delete t;
	return 0; */
}

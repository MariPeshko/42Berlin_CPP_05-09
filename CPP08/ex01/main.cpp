/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:22:42 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/31 19:56:35 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <vector>
#include <exception>
#include <climits>
#include <cstdlib> // srand
#include <ctime> // time

// test OCF and addNumber()
static void	test_OCF_addNumber( ) {
	// Test 1. Default Constructor
	std::cout << "Test 1. Default Constructor" << std::endl;
	
	Span def;
	std::cout << def;
	def.addNumber(10);
	try {
		def.addNumber(20);
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	def.print();

	// Test 2. Parametric COnstructor
	std::cout << "\nTest 2. Default COnstructor" << std::endl;

	Span test(5);
	std::cout << test;
	test.addNumber(1);
	test.addNumber(2);
	test.addNumber(3);
	test.addNumber(4);
	test.addNumber(5);
	try {
		test.addNumber(6);
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	test.print();

	// Test 3. Assignment operator
	std::cout << "\nTest 3. Assignment operator" << std::endl;
	try {
		def = test;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	try {
		test = def;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	test.print();
	def.print();

	// Additional test. Span size is 0
	/* {
		Span sp = Span(0);
		try {
			sp.addNumber(6);
		} catch (std::exception & e) {
			std::cout << e.what() << std::endl;
		}
	} */

	// Additional test. Negative argument. Span capacity too large
	/* try {
		Span sp = Span(-1);
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	} */
}

static void	test_longestSpan() {
	{
		// Test 4. longestSpan. less than 2 numbers stored
		std::cout << "\nTest 4. longestSpan. less than 2 numbers stored" << std::endl;
		Span def;
		std::cout << def;
		def.addNumber(10);
		
		try {
			unsigned int shortSpan = def.longestSpan();
			std::cout << "longest span is " << shortSpan << std::endl;
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
	}

	{
		// Test 5. longestSpan. more than 2 numbers stored
		std::cout << "\nTest 5. longestSpan. enough numbers stored" << std::endl;
		Span test(5);
		std::cout << test;
		test.addNumber(1);
		test.addNumber(11);
		test.addNumber(21);
		test.addNumber(13);
		test.addNumber(31);
		try {
			unsigned long shortSpan = test.longestSpan();
			std::cout << "longest span is " << shortSpan << std::endl;
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
		}

	}
	{
		// Test 6. longestSpan. numbers are equal
		std::cout << "\nTest 6. longestSpan. numbers are equal" << std::endl;
		Span test(5);
		std::cout << test;
		test.addNumber(6);
		test.addNumber(6);
		test.addNumber(6);
		test.addNumber(6);
		test.addNumber(6);
		try {
			unsigned long shortSpan = test.longestSpan();
			std::cout << "longest span is " << shortSpan << std::endl;
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
	}

	{
		// Test 6A. longestSpan.
		std::cout << "\nTest 6A. longestSpan. huge span" << std::endl;
		Span test(2);
		std::cout << test;
		test.addNumber(2147483647);
		test.addNumber(-2147483648);
		try {
			unsigned long shortSpan = test.longestSpan();
			std::cout << "longest span is " << shortSpan << std::endl;
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

static void	test_shortestSpan() {
	{
		// Test 7. shortestSpan. less than 2 numbers stored
		std::cout << "\nTest 7. shortestSpan. less than 2 numbers stored" << std::endl;
		Span def;
		std::cout << def;
		def.addNumber(10);
		
		try {
			unsigned int shortSpan = def.shortestSpan();
			std::cout << "shortest span is " << shortSpan << std::endl;
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
	}
	{
		// Test 8. shortestSpan. more than 2 numbers stored
		std::cout << "\nTest 8. shortestSpan. enough numbers stored" << std::endl;
		Span test(5);
		std::cout << test;
		test.addNumber(1);
		test.addNumber(11);
		test.addNumber(21);
		test.addNumber(13);
		test.addNumber(31);
		try {
			unsigned int shortSpan = test.shortestSpan();
			std::cout << "shortest span is " << shortSpan << std::endl;
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
	}

	{
		// Test 9. shortestSpan. int max and int min
		std::cout << "\nTest 9. shortestSpan. int max and int min" << std::endl;
		Span test(5);
		std::cout << test;
		test.addNumber(INT_MAX);
		test.addNumber(INT_MIN);
		try {
			unsigned int shortSpan = test.shortestSpan();
			std::cout << "shortest span is " << shortSpan << std::endl;
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

/**
 * % 15001 explained.
 * 
 * The reason for 15001 is because of how the modulo operator works with ranges.
 * When you use rand() % N, you get values from 0 to N-1 (inclusive).
 * 
 * rand() % 5;     // Possible values: 0, 1, 2, 3, 4        (5 values total)
 * 
 */
static void	testMultiNUmbers() {
	// Test 10. test multiple numbers
	std::cout << "\nTest 10. test multiple numbers\n";
	std::cout << "To test exception: make a toFill vector bigger" << std::endl;

	Span sp = Span(15000);
	std::cout << sp;

	std::vector<int> toFill(15000); // 15000 elements, each initialized to 0
	srand(time(NULL));
	for(std::vector<int>::iterator it = toFill.begin(); it != toFill.end(); ++it) {
		
		int value = rand() % 15001; // Range: 0 to 15000 (inclusive)
		if (rand() % 2 == 0) {		// 50% chance
			value = -value;			// Make it negative
		}
		*it = value;
	}
	
	try {
		sp.addManyNumbers(toFill);
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		std::cout << "shortest : " << sp.shortestSpan() << std::endl;
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	
	try {
		std::cout << "longest : "<< sp.longestSpan() << std::endl;
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
}

int	main( void )
{

	// Test 10. From a subject
	{
		std::cout << "\nTest. From a subject\n";
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << "\n" << std::endl;
	}
	
	test_OCF_addNumber();
	test_longestSpan();
	test_shortestSpan();
	testMultiNUmbers();

	
	
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:08:12 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/08 15:42:52 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"
#include <iostream>


int main( void ) {
	
	//Test 1
	int a = 2;
	int b = 3;

	/* //Test 2 - Floats
	float a = 1.5f;
	float b = 2.6f; */
	/* //Test 3 - Equal values
	int a = 4;
	int b = 4; */
	
	::swap( a, b );
	std::cout << "After swap: a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;

	 // Test 4 - Strings
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "After swap: c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	
	return 0;
	
}

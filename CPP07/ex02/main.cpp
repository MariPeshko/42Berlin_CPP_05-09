/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:22:10 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/03 14:20:33 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>

int main( void ) {
	
	// new int() allocates single int, initializes to 0
	int * a = new int();
	delete a;

	int * b = new int[5];
	for (unsigned int i = 0; i < 5; i++) {
		b[i] = 12;
	}
	std::cout << "*b: " << *b << std::endl; 
	delete[] b;


	// to specify the template type
	Array< int > emptyArr;
	//std::cout << emptyArr ...

	Array< int > arrSize(5);

	/* // You can also use other types:
    Array<std::string> stringArr;
    Array<double> doubleArr; */

	return 0;
	
}


/*
int * b = new int[5]; // default-initialized, not zeroed for built-in types
std::cout << "*b: " << *b << std::endl; 

Output: *b: -622876016 */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_my.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:22:10 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/07 18:03:40 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>

#define MAX_VAL 75

int main( void ) {
	
{
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
	std::cout << "Array arrSize. Default initialization of an element: ";
	std::cout << arrSize[1] << std::endl;
	
	Array< int > cpyArr(arrSize);
}

    Array<int> numbers(MAX_VAL);
	srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
    }
	std::cout << numbers[30] << std::endl;

	/* // You can also use other types:
    Array<std::string> stringArr;
    Array<double> doubleArr; */

	std::cout << "Size of array numbers: " << numbers.size() << std::endl;

	return 0;
	
}


/*
int * b = new int[5]; // default-initialized, not zeroed for built-in types
std::cout << "*b: " << *b << std::endl; 

Output: *b: -622876016 */

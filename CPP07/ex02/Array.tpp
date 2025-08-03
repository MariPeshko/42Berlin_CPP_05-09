/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:30:06 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/03 14:10:29 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>

// Default constructor
// Construction with no parameter: Creates an empty array
template <typename T>
Array<T>::Array( void ) :
	_array(NULL)
{ };

// Parametrized constructor
template <typename T>
Array<T>::Array( unsigned int n ) :
	_array(new T[n]() )
{ 
	
};

// Copy Constructor
template <typename T>
Array<T>::Array ( Array const & src ) :
	_array(NULL)	{ }

// Assignment operator 
template <typename T>
Array<T> &	Array<T>::operator=( Array const &assign ) {
	
	if (this != &assign) {
		//this->_grade = assign._grade;
	}
    return *this;
}

// Destructor
template <typename T>
Array<T>::~Array() { 
    // delete allocated memory
    delete[] _array;
};

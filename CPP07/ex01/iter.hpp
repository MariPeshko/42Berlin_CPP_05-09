/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:42:47 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/01 20:56:16 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Templates must be defined in the header files.

#ifndef	ITER_HPP
# define ITER_HPP

#include <iostream>

/**
 * To support both const and non-const arrays, the iter function should 
 * accept a function pointer that takes a const reference (const T&). 
 * The func function should also take a const reference.
 */

/**  function template that can be instantiated 
 * with both const and non-const reference parameters. */
template < typename T >
void	print (const T& elem) {
	std::cout << elem;
	return ;
}

/* iter() takes three parameters:
1) address of an array,
2) the length of the array,
3) a function that will be called on every element of the array

Your iter function template must work with any type
of array. The third parameter can be an instantiated 
function template. 

The function passed as the third parameter may take 
its argument by const reference or non-const reference, 
depending on the context.

Think carefully about how to support both const 
and non-const elements in your iter function.*/
template < typename T >
void	iter( T* arr, size_t length, void (*f)(const T &)) {
	std::cout << "iter is called, function print() prints each element" << std::endl;
	for (size_t i = 0; i < length; i++) {
		f(arr[i]);
		std::cout << " ";
	}
	std::cout << std::endl;
	return ;
}

template < typename T >
size_t	sizeArr (const T& arr) {

	size_t s = sizeof(arr) / sizeof(arr[0]);
	return s;
}

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:42:47 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/08 16:05:53 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ITER_HPP
# define ITER_HPP

#include <iostream>

/**
 * To support both const and non-const arrays, the iter function should 
 * accept a function pointer that takes a const reference (const T&). 
 * The func function should also take a const reference.
 */

/* function template that can be instantiated 
 with both const and non-const reference parameters. */
template < typename T >
void	print (const T& elem) {
	std::cout << elem;
	return ;
}

/* increment isn't possible because iter() function has 
 * void (*f)(const T &) as third parameter. 
 *  error: increment of read-only reference ‘elem’*/

/*
Your iter function template must work with any type
of array. The third parameter can be an instantiated 
function template. 

The function passed as the third parameter may take 
its argument by const reference or non-const reference, 
depending on the context.

Think carefully about how to support both const 
and non-const elements in your iter function.

For an array of int int[] the function becomes: 
void iter(int* arr, size_t length, void(*f)(const int&))
*/
template < typename T >
void	iter( T* arr, size_t length, void (*f)(const T &)) {
	if (!arr || !f)
		return ;
	for (size_t i = 0; i < length; i++) {
		f(arr[i]);
		std::cout << " ";
	}
	std::cout << std::endl;
	return ;
}

#endif

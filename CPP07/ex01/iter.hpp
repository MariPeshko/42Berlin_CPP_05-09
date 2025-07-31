/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:42:47 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/31 20:41:08 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Templates must be defined in the header files.

#ifndef	ITER_HPP
# define ITER_HPP


/* Three parameters:
1) address of an array,
2) the length of the array (?unsigned),
3) a function that will be called on every element of the array

Your iter function template must work with any type
of array. The third parameter can be an instantiated 
function template. 

The function passed as the third parameter may take 
its argument by const reference or non-const reference, 
depending on the context 

Think carefully about how to support both const 
and non-const elements in your iter function.*/
template < typename T >
//void	iter( T & x, T & y, T & z) {
void	iter( T & x, T & y, T & z) {

	
	return ;
}

/* template <typename T>
void iter(T* array, int length, void (*func)(T const&)) { ... } */

/* This can get tricky when you want to allow both:

void func(const T&)

void func(T&)

So a flexible solution may require overloads 
or an extra template on the function itself. */


#endif

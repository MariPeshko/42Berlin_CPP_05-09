/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:42:52 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/31 16:42:53 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Templates must be defined in the header files.

#ifndef	WHATEVER_HPP
# define WHATEVER_HPP

template < typename T >
void	swap( T & x, T & y) {

	T	tmp = y;
	y = x;
	x = tmp;
	return ;
}

/**
 * Compares the two values passed as parameters and returns the smallest one.
 * If they are equal, it returns the second one.
 * 
 * When you use the < (less than) operator with std::string 
 * objects in C++, it performs a lexicographical comparison.
 */ 
template < typename T >
T const &	min( T const & x, T const & y ) {
	if (x < y) {
		return x;
	} else {
		return y;
	}
}

/* Compares the two values passed as parameters and returns the greatest one.
If they are equal, it returns the second one. */
template < typename T >
T const &	max( T const & x, T const & y ) {
	if (x > y) {
		return x;
	} else {
		return y;
	}
}

#endif

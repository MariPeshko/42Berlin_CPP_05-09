/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:25:02 by mpeshko           #+#    #+#             */
/*   Updated: 2025/09/02 10:52:09 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

/**
 * Assuming T is a container of integers, this function has to find 
 * the first occurrence of the second parameter in the first parameter.
 * 
 * If value not found, find() returns container.end() (STL convention)
 */
template<typename T>
typename T::iterator	easyfind(T& container, int value) {
	
	return std::find(container.begin(), container.end(), value);

}

#endif

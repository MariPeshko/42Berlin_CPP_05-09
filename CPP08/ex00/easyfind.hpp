/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:25:02 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/22 21:03:54 by mpeshko          ###   ########.fr       */
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
 * Benefits of returning iterator: STL consistency: Follows standard 
 * library conventions.
 */
/* template < typename T>
int easyfind(T & container, int target ) {
    for (typename T::iterator it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    return container[0];
} */

/* template<typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end()) {
        throw std::runtime_error("Value not found");
    }
    return it;
} */

/* template<typename T>
typename T::iterator easyfind(T& container, int value) {
    return std::find(container.begin(), container.end(), value);
    // Returns container.end() if not found (STL convention)
} */

template<typename T>
void easyfind(T& container, int value) {
	if (std::find(container.begin(), container.end(), value) == container.end())
		std::cout << "container does not contain " << value << '\n';
	else
		std::cout << "container contains " << value << '\n';
    //return std::find(container.begin(), container.end(), value);
    // Returns container.end() if not found (STL convention)
}

/* void example_contains()
{
    const auto haystack = {1, 2, 3, 4};
 
    for (const int needle : {3, 5})
        if (std::find(haystack.begin(), haystack.end(), needle) == haystack.end())
            std::cout << "haystack does not contain " << needle << '\n';
        else
            std::cout << "haystack contains " << needle << '\n';
} */

#endif
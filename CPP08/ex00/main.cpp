/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:24:45 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/22 21:00:58 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>

int main () 
{
    std::vector<unsigned>   u_vector;
    unsigned                value;
    
    while (std::cin >> value) {
        u_vector.push_back(value);
    }
    std::cout << "u_vector.size = " << u_vector.size() << std::endl;
	
	::easyfind(u_vector, 100);
	::easyfind(u_vector, 98);
	
	// 1. Check if element was found
    std::vector<int>::iterator it = easyfind(u_vector, 30);
    if (it != u_vector.end()) {
        std::cout << "Found value: " << *it << std::endl;
        std::cout << "At position: " << (it - u_vector.begin()) << std::endl;
    } else {
        std::cout << "Value not found!" << std::endl;
    }


	//////


	// 4. Use with different container types
    std::list<int> lst;
    lst.push_back(5);
    lst.push_back(15);
    lst.push_back(25);

	

	return 0;
}
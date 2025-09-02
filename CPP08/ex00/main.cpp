/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:24:45 by mpeshko           #+#    #+#             */
/*   Updated: 2025/09/02 11:07:10 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>

int main ()
{
	// TEST 1: VECTOR
	std::string divider(60, '-');

	std::cout << divider << std::endl;
	std::cout << "TEST 1: VECTOR" << std::endl;
	
	std::vector<int>	vector;
	vector.push_back(45);   // value to find
	vector.push_back(65);
	vector.push_back(99);
	vector.push_back(100);
	vector.push_back(34);
	vector.push_back(-67);
	vector.push_back(95);
	vector.push_back(76);
	vector.push_back(88);
	vector.push_back(75);
	vector.push_back(-83);
	std::cout << "vector size = " << vector.size() << std::endl;
	
	// easy find 1
	int nmb = 45;
	std::cout << "\nSearching for " << nmb << std::endl;
	std::vector<int>::const_iterator it = easyfind(vector, nmb);
	
	
	
	if (it != vector.end()) {
		std::cout << "Found value: " << *it << std::endl;
		std::cout << "At position: " << (it - vector.begin()) << std::endl;
	} else if (it == vector.end()) {
		std::cout << "Value not found!" << std::endl;
	}
	
	// easy find 2
	nmb = 1;
	std::cout << "\nSearching for " << nmb << std::endl;
	it = easyfind(vector, nmb);
	if (it != vector.end()) {
		std::cout << "Found value: " << *it << std::endl;
		std::cout << "At position: " << (it - vector.begin()) << std::endl;
	} else if (it == vector.end()) {
		std::cout << "Integer " << nmb << " isn't found" << std::endl;
	}

	// TEST 2: LIST
	std::cout << divider << std::endl;
	std::cout << "TEST 2: LIST" << std::endl;
	
	std::list<int>	lst;
	lst.push_back(5);
	lst.push_back(15);
	lst.push_back(25);
	std::cout << "list size = " << lst.size() << std::endl;

	nmb = 15;
	// Note: std::list doesn't support random access, so no position calculation
	// as we can do for vectors
	std::list<int>::const_iterator l_it = easyfind(lst, nmb);
	if (l_it != lst.end()) {
		std::cout << "Found value: " << *l_it << std::endl;
		int	position = 0;
		for (std::list<int>::iterator temp = lst.begin(); temp != l_it; ++temp) {
			++position;
		}
		std::cout << "At position: " << position << std::endl;
	} else {
		std::cout << "Value not found!" << std::endl;
	}

	// TEST 3: DEQUE
	std::cout << divider << std::endl;
	std::cout << "TEST 3: DEQUE" << std::endl;
	
	std::deque<int>	deque;
	deque.push_back(5);
	deque.push_back(15);
	deque.push_back(25);
	deque.push_back(-25);
	std::cout << "deque size = " << deque.size() << std::endl;

	nmb = -25;
	std::deque<int>::const_iterator d_it = easyfind(deque, nmb);
	if (d_it != deque.end()) {
		std::cout << "Found value: " << *d_it << std::endl;
		std::cout << "At position: " << (d_it - deque.begin()) << std::endl;
	} else {
		std::cout << "Value not found!" << std::endl;
	}

	// TEST 4: EMPTY CONTAINER
	std::cout << divider << std::endl;
	std::cout << "TEST 4: EMPTY CONTAINER" << std::endl;
	std::vector<int> empty_vec;
	std::cout << "empty_vec size = " << empty_vec.size() << std::endl;
	std::vector<int>::const_iterator empty_it = easyfind(empty_vec, 0);
	if (empty_it == empty_vec.end())
		std::cout << "Empty container test passed" << std::endl;
	else if (empty_it != empty_vec.end())
		std::cout << "Empty container test NOT passed" << std::endl;

	return 0;
	
}

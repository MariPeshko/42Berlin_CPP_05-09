/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:24:45 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/23 15:59:15 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>

int main ()
{
	// TEST 1: VECTOR
	std::cout << "TEST 1: VECTOR" << std::endl;
	
	std::vector<int>	vector;
	vector.push_back(45);
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
	std::cout << "vector.size = " << vector.size() << std::endl;
	
	std::vector<int>::iterator it = easyfind(vector, 45);
	if (it != vector.end()) {
		std::cout << "Found value: " << *it << std::endl;
		std::cout << "At position: " << (it - vector.begin()) << std::endl;
	} else {
		std::cout << "Value not found!" << std::endl;
	}

	it = easyfind(vector, 1);
	if (it == vector.end())
		std::cout << "Integer 1 isn't found" << std::endl;

	// TEST 2: LIST
	std::cout << "\nTEST 2: LIST" << std::endl;
	
	std::list<int>	lst;
	lst.push_back(5);
	lst.push_back(15);
	lst.push_back(25);
	std::cout << "list.size = " << lst.size() << std::endl;

	// Note: std::list doesn't support random access, so no position calculation
	// as we can do for vectors
	// error: no operator "-" matches these operands
	std::list<int>::iterator l_it = easyfind(lst, 25);
	if (l_it != lst.end()) {
		std::cout << "Found value: " << *l_it << std::endl;
		// Calculate position manually for list
		int	position = 0;
		for (std::list<int>::iterator temp = lst.begin(); temp != l_it; ++temp) {
			++position;
		}
		std::cout << "At position: " << position << std::endl;
	} else {
		std::cout << "Value not found!" << std::endl;
	}

	// TEST 3: DEQUE
	std::cout << "\nTEST 3: DEQUE" << std::endl;
	std::deque<int>	deque;
	deque.push_back(5);
	deque.push_back(15);
	deque.push_back(25);
	deque.push_back(-25);
	std::cout << "deque.size = " << deque.size() << std::endl;

	std::deque<int>::iterator d_it = easyfind(deque, 15);
	if (d_it != deque.end()) {
		std::cout << "Found value: " << *d_it << std::endl;
		std::cout << "At position: " << (d_it - deque.begin()) << std::endl;
	} else {
		std::cout << "Value not found!" << std::endl;
	}

	// TEST 4: EMPTY CONTAINER
	std::cout << "\nTEST 4: EMPTY CONTAINER" << std::endl;
	std::vector<int> empty_vec;
	std::vector<int>::iterator empty_it = easyfind(empty_vec, 42);
	if (empty_it == empty_vec.end())
		std::cout << "Empty container test passed" << std::endl;

	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:24:18 by mpeshko           #+#    #+#             */
/*   Updated: 2025/09/01 22:23:26 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <string>

int main()
{
	std::string divider(60, '-');
	{
		std::cout << divider << std::endl;
		MutantStack<int> mstack;

		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout  << "size " << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(4);
		mstack.push(737);
		
		//[...]
		
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		std::cout << "The value at the current iterator posision " << *it << std::endl;
		--it;
		std::cout << "The value at the current iterator posision " <<  *it << std::endl;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack);
		std::cout << "Copied stack s. On top: " << s.top() << std::endl;
	}
	{
		std::cout << divider << std::endl;
		// first test with a list container
		std::cout << "\ntest with a list" << std::endl;
		std::list<int> lst;

		lst.push_back(5);
		lst.push_back(17);
		std::cout << lst.back() << std::endl;	// a reference to the last element
		lst.pop_back();							// Removes last element 
		std::cout << "size " << lst.size() << std::endl;
		lst.push_back(3);
		lst.push_back(4);
		lst.push_back(737);

		lst.push_back(0);
		std::list<int>::iterator lit = lst.begin();
		std::list<int>::iterator lite = lst.end();
		++lit;
		std::cout << "The value at the current iterator posision " << *lit << std::endl;
		--lit;
		std::cout << "The value at the current iterator posision " <<  *lit << std::endl;
		while (lit != lite)
		{
			std::cout << *lit << std::endl;
			++lit;
		}
		std::list<int> lst2(lst);
		std::cout << "Copied list lst. The last element: " << lst2.back() << std::endl;
	}
	std::cout << divider << std::endl;
	// first test with a list container
	std::cout << "\nmy additional tests" << std::endl;
	std::cout << "String Test" << std::endl;
	
	MutantStack<std::string> sstack;
	sstack.push("Where Do We Come From?");
	sstack.push("What Are We?");
	sstack.push("Where Are We Going?");
	sstack.push("\nIt's a name of the painting by French artist Paul Gauguin");

	for (MutantStack<std::string>::iterator it = sstack.begin(); it != sstack.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::cout  << "size " << sstack.size() << std::endl;
	while (!sstack.empty()) {
		std::cout << "Popping: " << sstack.top() << std::endl;
		sstack.pop();
	}
	std::cout  << "size " << sstack.size() << std::endl;

	return 0;
}
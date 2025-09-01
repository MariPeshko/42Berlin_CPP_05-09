/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:24:18 by mpeshko           #+#    #+#             */
/*   Updated: 2025/09/01 19:22:42 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main()
{
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout  << "size " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	
	//[...]
	
	mstack.push(0);
	/* MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	} */
	std::stack<int> s(mstack);
	std::cout << "Copied stack s. On top: " << s.top() << std::endl;

	// first test with a list container
	std::cout << "\ntest with a list" << std::endl;
	std::list<int> lst;

	lst.push_back(5);
	lst.push_back(17);
	std::cout << lst.back() << std::endl;	// a reference to the last element
	lst.pop_back();							// Removes last element 
	std::cout << "size " << lst.size() << std::endl;
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);

	lst.push_back(0);
	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator ite = lst.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::list<int> lst2(lst);
	std::cout << "Copied list lst. The last element: " << lst2.back() << std::endl;

	
	return 0;
}
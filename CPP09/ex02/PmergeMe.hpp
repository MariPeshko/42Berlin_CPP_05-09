/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:19 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/28 13:47:08 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
/* #include <sstream>
#include <stdexcept> */

struct Pair {
    int smaller;
    int larger;
};

class PmergeMe {
	private:
		std::vector<int>	_numbers;
		std::vector<int>	_sorted_numbers;
		int					_size;

		void insertInSortedVector(std::vector<int>& vec, int value);

		// Core algorithm functions
		// void fordJohnsonSort(std::vector<int>& vec);
		// void insertIntoMainChain(std::vector<int>& mainChain, int value);
		// std::vector<int> generateJacobsthalSequence(int n);
		
		// // Utility functions
		
		

	public:
		PmergeMe(const std::vector<int> & _numbers);
		~PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& assign);
		
		void sort(std::vector<int>& vec);
		void sortPairs(std::vector<Pair>& pairs, int unpaired, bool has_unpaired);
		void buildSortedVector(std::vector<int>& vec, std::vector<Pair>& pairs, 
			int unpaired_element, bool has_unpaired);
    	void display();

		static bool	isValidInput(const std::string & input);
		static bool parseString(const std::string & inputstr, std::vector<int> & numbers);
		static bool isDuplicates(const std::vector<int> & numbers);
};



#endif

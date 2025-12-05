/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:19 by mpeshko           #+#    #+#             */
/*   Updated: 2025/12/05 16:57:43 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define DEBUG_RECURSION 0
#define DEBUG_PART2 0
#define FULL_DEBUG 0
#define Jacobsthal 0
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define ORANGE "\033[38;5;208m"

struct	Pair {
	int	smaller;
	int	larger;
};

class PmergeMe {
	
	private:
		std::vector<int>	_numbers;
		std::vector<int>	_sorted_numbers;
		int					_size;

		// Core algorithm functions
		// Step 1: 
		void	createPairs(std::vector<Pair> &pairs, const std::vector<int> &vec, 
					int &unpaired_element, bool &has_unpaired);
		// Step 2: Extract larger elements (in fordJohnsonSort() )
		// Step 3: Sort recursively. Call fordJohnsonSort()
		// Step 4: Reorder pairs based on sorted larger elements
		void	reorderPairs(std::vector<Pair> & pairs,
					const std::vector<int> &larger_elements);
		// Step 5: Build final result
		void	buildSortedVector(std::vector<int>& vec, const std::vector<Pair>& pairs, 
					int unpaired_element, bool has_unpaired);
		
		
		// Utility functions
		std::vector<size_t>	generateJacobsthalSequence(size_t n);
		std::vector<size_t>	generateInsertionOrder(size_t pend_size);
		void				insertInSortedVector(std::vector<int>& vec, int value, size_t bound);
		

	public:
		PmergeMe(const std::vector<int> & _numbers);
		~PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe&	operator=(const PmergeMe& assign);
		
		static long long	fordJohnsonWorstCase(int n);
		static int			nbr_of_comps;
		static int			nbr_of_recur;
		
		void		fordJohnsonSort(std::vector<int>& vec);
		void		display();
		static bool	isSortedAscending(const std::vector<int>& vec);

		// Parsing
		static bool	isValidInput(const std::string & input);
		static bool	parseString(const std::string & inputstr, std::vector<int> & numbers);
		static bool	isDuplicates(const std::vector<int> & numbers);
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:13 by mpeshko           #+#    #+#             */
/*   Updated: 2025/12/09 16:38:02 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream> // for std::istringstream
#include <cctype>  // for std::isdigit
#include <climits> // INT_MAX
#include <set>
#include <algorithm> // for std::min

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int	PmergeMe::nbr_of_comps = 0;
int	PmergeMe::nbr_of_recur = 0;

PmergeMe::PmergeMe(const std::vector<int> &parsed_numbers) :
	_numbers_vec(parsed_numbers),
	_numbers_deque(),
	_totalUsVec(0),
	_totalUsDeq(0)
{  _size = _numbers_vec.size(); }

PmergeMe::PmergeMe(const std::deque<int> &parsed_numbers) :
	_numbers_vec(),
	_numbers_deque(parsed_numbers),
	_totalUsVec(0),
	_totalUsDeq(0)
{  _size = _numbers_deque.size(); }

PmergeMe::~PmergeMe() {}

static void display_deque(const std::deque<int> & deq) {
	for (std::deque<int>::const_iterator it = deq.begin();
		it != deq.end(); ++it)
			cout << *it << " ";
}

static void	display_vector(const std::vector<int> & vct) {
	for (std::vector<int>::const_iterator it = vct.begin();
		it != vct.end(); ++it)
			cout << *it << " ";
	cout << endl;
}

static void	display_vector(const std::vector<size_t> & vct) {
	for (std::vector<size_t>::const_iterator it = vct.begin();
		it != vct.end(); ++it)
			cout << *it << " ";
	cout << endl;
}

/**
 * Ford-Johnson sorting algorithm for vector container.
 * Recursive method.
 * @param vec - sequence of input numbers
 */
void	PmergeMe::VecFordJohnsonSort(std::vector<int> &vec)
{
	++PmergeMe::nbr_of_recur;
	if (DEBUG_RECURSION) {
		cout << GREEN << "Recursion track: Layer " << PmergeMe::nbr_of_recur << " called with: ";
		display_vector(vec);
	}
	if (vec.size() <= 1) {
		this->_sorted_numbers_vec = vec;
		return ;
	}
	if (vec.size() == 2) {
		PmergeMe::nbr_of_comps++;
		if (vec[0] > vec[1]) std::swap(vec[0], vec[1]);
		this->_sorted_numbers_vec = vec;
		return ;
	}
	// Step 1: Create pairs and handle unpaired element
	std::vector<Pair>	pairs;
	int					unpaired_element = 0;
	bool				has_unpaired = false;

	createPairs(pairs, vec, unpaired_element, has_unpaired);
	// Debug output
	if (DEBUG_PART1) {
		cout << BLUE << "Pairs. Divide elements into pairs: ";
		for (size_t i = 0; i < pairs.size(); ++i)
			cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
		if (has_unpaired) cout << BLUE << "+ unpaired: " << unpaired_element;
		cout << RESET << endl;
	} 
	
	// Step 2: Extract larger elements (a1, a2, a3, ...) for recursive sorting
	std::vector<int>	larger_elements;
	for (size_t i = 0; i < pairs.size(); ++i)
		larger_elements.push_back(pairs[i].larger);

	if (DEBUG_PART1) {
		cout << YELLOW << "Larger elements for recursive sort: ";
		display_vector(larger_elements); cout << RESET;
	}
	// Step 3: Sort recursively
	VecFordJohnsonSort(larger_elements);
	// larger_elements is now SORTED
	if (DEBUG_RECURSION) cout << GREEN << "Recursion track: Exit from " << PmergeMe::nbr_of_recur << " layer" << RESET << endl;
	--PmergeMe::nbr_of_recur;
	if (DEBUG_RECURSION) cout << GREEN << "Recursion track: Current layer " << PmergeMe::nbr_of_recur << RESET << endl;
	if (DEBUG_RECURSION || DEBUG_PART2) {
		cout << ORANGE << "SORTED MAIN CHAIN A : ";
		display_vector(larger_elements); cout << RESET;
	}
	// Step 4: Reorder pairs based on sorted larger elements
	reorderPairs(pairs, larger_elements);
	if (DEBUG_PART1 || DEBUG_PART2) {
		cout << BLUE << "Pairs. Reordered: ";
		for (size_t i = 0; i < pairs.size(); ++i)
			cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
		if (has_unpaired) cout << " + unpaired: " << unpaired_element;
		cout << RESET << endl;
	}
	// Step 5: Build final result in the original vec
	buildSortedVector(vec, pairs, unpaired_element, has_unpaired);
	_sorted_numbers_vec = vec;
}

void	PmergeMe::DeqFordJohnsonSort(std::deque<int>& deq) {

	if (deq.size() <= 1) {
		this->_sorted_numbers_deque = deq;
		return ;
	}
	if (deq.size() == 2) {
		PmergeMe::nbr_of_comps++;
		if (deq[0] > deq[1]) std::swap(deq[0], deq[1]);
		this->_sorted_numbers_deque = deq;
		return ;
	}
	// Step 1: Create pairs and handle unpaired element
	std::deque<Pair>	pairs;
	int					unpaired_element = 0;
	bool				has_unpaired = false;

	createPairs(pairs, deq, unpaired_element, has_unpaired);
	// Step 2: Extract larger elements (a1, a2, a3, ...) for recursive sorting
	std::deque<int>	larger_elements;
	for (size_t i = 0; i < pairs.size(); ++i)
		larger_elements.push_back(pairs[i].larger);
		
	// Step 3: Sort recursively
	DeqFordJohnsonSort(larger_elements);
	// larger_elements is now SORTED
	
	// Step 4: Reorder pairs based on sorted larger elements
	reorderPairs(pairs, larger_elements);
	// Step 5: Build final result in the original deq
	buildSortedDeq(deq, pairs, unpaired_element, has_unpaired);
	_sorted_numbers_deque = deq;
}

// Step 1: Create pairs from adjacent elements
void	PmergeMe::createPairs(std::vector<Pair> &pairs, const std::vector<int> &vec,
						   int &unpaired_element, bool &has_unpaired)
{
	if (vec.size() % 2 != 0) {
		has_unpaired = true;
		unpaired_element = vec.back();
	}
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end();) {
		if ((it + 1) == vec.end())
			break; // Odd number, last element handled above
		Pair p;
		PmergeMe::nbr_of_comps++;
		if (*it > *(it + 1)) {
			p.larger = *it;
			p.smaller = *(it + 1);
		} else {
			p.larger = *(it + 1);
			p.smaller = *it;
		}
		pairs.push_back(p);

		++it;
		if (it != vec.end())
			++it;
	}
}

void	PmergeMe::createPairs(std::deque<Pair> &pairs, const std::deque<int> &vec,
						   int &unpaired_element, bool &has_unpaired)
{
	if (vec.size() % 2 != 0) {
		has_unpaired = true;
		unpaired_element = vec.back();
	}
	for (std::deque<int>::const_iterator it = vec.begin(); it != vec.end();) {
		if ((it + 1) == vec.end())
			break; // Odd number, last element handled above
		Pair p;
		PmergeMe::nbr_of_comps++;
		if (*it > *(it + 1)) {
			p.larger = *it;
			p.smaller = *(it + 1);
		} else {
			p.larger = *(it + 1);
			p.smaller = *it;
		}
		pairs.push_back(p);

		++it;
		if (it != vec.end())
			++it;
	}
}

/**
 * Build sorted vector.
 * - Create main chain (sorted larger elements) and pend elements (unsorted 
 * elements).
 * - Generate insertion order based on Jacobsthal numbers.
 * - Inserting pend elements in the sorted main chain.
 * 
 * @param vec it's a reference to the vector that came from recursive
 * sorting method.
 */
void PmergeMe::buildSortedVector(std::vector<int> &vec, const std::vector<Pair> &pairs,
								 int unpaired_element, bool has_unpaired)
{
	std::vector<int>	main_chain;	   // (a1, a2, ...)
	std::vector<int>	pend_elements; // (b1, b2, ...) + unpaired
	
	if (DEBUG_PART2) cout << ORANGE << "PART2. Building a sorted vector.\n";
	if (DEBUG_PART2) cout << BLUE <<  "b1 = " << pairs[0].smaller << " and it first goes to main_chain" << RESET << endl;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (i == 0)
			main_chain.push_back(pairs[i].smaller); // b1
		else
			pend_elements.push_back(pairs[i].smaller); // b2, b3, b4, ...
		main_chain.push_back(pairs[i].larger);		   // a1, a2, a3, ...
	}

	if (has_unpaired)
		pend_elements.push_back(unpaired_element);

	if (DEBUG_PART2) {
		cout << BLUE << "MAIN CHAIN:    ";
		for (size_t i = 0; i < main_chain.size(); ++i)
			cout << main_chain[i] << " ";
		cout << endl;
		cout << "PEND ELEMENTS: ";
		for (size_t i = 0; i < pend_elements.size(); ++i)
			cout << pend_elements[i] << " ";
		cout << RESET << endl;
	}
	// Start with main chain
	vec = main_chain;
	// Generate optimal insertion order using Jacobsthal sequence
	std::vector<size_t> insert_order;
	insert_order = generateInsertionOrder(pend_elements.size());

	if (Jacobsthal) {
		cout << GREEN << "Jacobsthal insertion order: ";
		for (size_t i = 0; i < insert_order.size(); ++i) {
			cout << insert_order[i] << " ";
		}
		cout << RESET << endl;
	}
	// bound the binary search for b_i by the current position of its partner a_i in the main chain
	// keep track of indexposition of pairs
	std::vector<size_t>	indexposition(pairs.size(), 0);
	if (FULL_DEBUG) cout << "_ _ Index position calculation for a bound _ _" << endl;
	for (size_t i = 1; i < pairs.size(); i++) {
		if (FULL_DEBUG) cout << i + 1 << " pair. Smaller b_" << i + 1 << " element " << pairs[i].smaller << endl;
		for (size_t j = 0; j < main_chain.size(); j++) {
			if (pairs[i].larger == main_chain[j]) {
				indexposition[i - 1] = j;
				if (FULL_DEBUG) cout << "index of a_" << i + 1 << " element " << pairs[i].larger << " in main chain is: ";
				if (FULL_DEBUG) cout << j << endl;  
			}
		}
	}
	if (has_unpaired) {
		indexposition.push_back(main_chain.size());
		if (FULL_DEBUG) cout << "For unpaired_element " << unpaired_element << " index position is the ";
		if (FULL_DEBUG) cout << "whole main_chain size " << main_chain.size() << endl;  
	}
	// Insert pend elements in Jacobsthal order
	for (size_t i = 0; i < insert_order.size(); ++i)
	{
		size_t index = insert_order[i];
		if (index < pend_elements.size())
		{
			if (FULL_DEBUG) cout << GREEN << "i is " << i << "; index is " << index << "; ";
			if (FULL_DEBUG) cout << "indexposition[index] is " << indexposition[index] << endl;
			size_t bound;
			if (has_unpaired && index == (pend_elements.size() - 1)) {
				if (FULL_DEBUG) cout << "for unpaired element we use binary search for a whole chain" << endl;
				bound = vec.size();
			}
			else
				bound = indexposition[index] + i;
			
			if (FULL_DEBUG) {
				cout << YELLOW << "Inserting pend_elements[" << index << "] = "
				<< pend_elements[index] << endl;
				cout << "bound: " << bound << RESET << endl;
			}
			insertInSortedContainer(vec, pend_elements[index], bound);
		}
	}
	if (DEBUG_PART2) {
		cout << "CURRENT SORTED VECTOR: ";
		display_vector(vec); 
		if (isSortedAscending(vec)) cout << GREEN << "Sorted correctly!" << RESET << endl;
		else cout << RED << "Error. Not sorted correctly" << RESET << endl;
		cout << endl;
	}
}

void	PmergeMe::buildSortedDeq(std::deque<int> &deq, const std::deque<Pair> &pairs,
								 int unpaired_element, bool has_unpaired) {
	std::deque<int>	main_chain;	   // (a1, a2, ...)
	std::deque<int>	pend_elements; // (b1, b2, ...) + unpaired
	
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (i == 0)
			main_chain.push_back(pairs[i].smaller); // b1
		else
			pend_elements.push_back(pairs[i].smaller); // b2, b3, b4, ...
		main_chain.push_back(pairs[i].larger);		   // a1, a2, a3, ...
	}

	if (has_unpaired)
		pend_elements.push_back(unpaired_element);
		
	// Start with main chain
	deq = main_chain;
	// Generate optimal insertion order using Jacobsthal sequence
	std::vector<size_t> insert_order;
	insert_order = generateInsertionOrder(pend_elements.size());

	if (Jacobsthal) {
		cout << GREEN << "Jacobsthal insertion order: ";
		for (size_t i = 0; i < insert_order.size(); ++i) {
			cout << insert_order[i] << " ";
		}
		cout << RESET << endl;
	}
	// bound the binary search for b_i by the current position of its partner a_i in the main chain
	// keep track of indexposition of pairs
	std::vector<size_t>	indexposition(pairs.size(), 0);
	for (size_t i = 1; i < pairs.size(); i++) {
		for (size_t j = 0; j < main_chain.size(); j++) {
			if (pairs[i].larger == main_chain[j]) {
				indexposition[i - 1] = j;
			}
		}
	}
	if (has_unpaired) {
		indexposition.push_back(main_chain.size());
	}
	// Insert pend elements in Jacobsthal order
	for (size_t i = 0; i < insert_order.size(); ++i) {
		size_t index = insert_order[i];
		if (index < pend_elements.size()) {
			size_t bound;
			if (has_unpaired && index == (pend_elements.size() - 1))
				bound = deq.size();
			else
				bound = indexposition[index] + i;
			insertInSortedContainer(deq, pend_elements[index], bound);
		}
	}			
}

/**
 * Formula J(k) = J(k-1) + 2*J(k-2)
 * 
 * @param n is hard-coded 15. The biggest number is a sequence is 10923.
 * It is enough for test of this program. Up to 10000 numbers.
 * 
 * Note:
 * k is the mathematical position (1st, 2nd, 3rd, etc.). 
 * i is the loop counter, but array indices are 0-based.
 * 
 * Mathematical Index J(1) == Array Index jac_seq[0]
 * 
 * We need to offset by 1 to convert from mathematical indexing 
 * (1-based) to array indexing (0-based)
 */
std::vector<size_t>	PmergeMe::generateJacobsthalSequence(size_t n)
{
	std::vector<size_t>	jac_seq;
	
	if (n == 0)
		return jac_seq;
	jac_seq.push_back(1); // J(1) = 1
	if (n == 1)
		return jac_seq;
	jac_seq.push_back(1); // J(2) = 1
	if (n == 2)
		return jac_seq;

	for (size_t i = 3; i <= n; ++i) {
		size_t next = jac_seq[i - 2] + 2 * jac_seq[i - 3];
		jac_seq.push_back(next);
	}

	return jac_seq;
}

/**
 * Function that generates the insertion index sequence pi for the current
 * length of Pend List.
 * 
 * This allows inserting elements into chains of length 2^k - 1,
 * which requires the minimum number of comparisons.
 * 
 * Groups: Insertion happens in groups. Each group starts with an element 
 * whose index corresponds to a Jacobsthal number (for example, b3, b5, b11).
 * This guarantees that elements that will have the greatest comparison savings 
 * are inserted first, before their potential insertion positions are "spoiled" 
 * (increased) by subsequent insertions.
 * 
 * The main_chain already contains b₁, so pend_elements contains: 
 * pend_elements[0] = b₂  ← Array index 0 = classic b₂.
 * Classic order: (1), (3,2), (5,4), (11,10,9,8,7,6), ... → b₁ NOT needed, 
 * as it's already in main_chain.
 * Required order: (b₃,b₂), (b₅,b₄) = indices [1,0], [3,2]
 */
std::vector<size_t>	PmergeMe::generateInsertionOrder(size_t pend_size)
{
	if (Jacobsthal) cout << BLUE << "Generating insertion order for pending size: " << pend_size << RESET << endl;
	std::vector<size_t>	insert_order;
	if (pend_size == 0)
		return insert_order;

	std::vector<size_t>	jac_seq = generateJacobsthalSequence(15);
	if (Jacobsthal) {
		cout << BLUE << "JacobsthalSequence: ";
		display_vector(jac_seq); cout << RESET;
	}
	
	std::vector<bool>	inserted(pend_size, false);
	size_t				group_end = 1; // Initial boundary (b₁ already processed)

	for (size_t j_index = 1; j_index < jac_seq.size() &&
		 	insert_order.size() < pend_size; ++j_index)
	{
		size_t jacob_num = jac_seq[j_index]; // J₂=3, J₃=5, J₄=11, ...

		// Limit Jacob number to pend_elements size + 1 (because b₁ is not in pend)
		size_t current_end = std::min(jacob_num, pend_size + 1);

		if (Jacobsthal) cout << "Jacob group " << j_index << ": from b" << current_end
				  << " down to b" << (group_end + 1) << endl;

		// Insert elements in reverse order from current_end to group_end+1
		for (size_t b_index = current_end; b_index > group_end; --b_index) {
			// Convert classic index b_i to pend_elements index
			// b₂ → pend[0], b₃ → pend[1], b₄ → pend[2], ...
			if (b_index >= 2) { // Skip b₁ (already in main_chain)
				size_t	pend_index = b_index - 2; // b₂→0, b₃→1, b₄→2, ...
				if (pend_index < pend_size && !inserted[pend_index]) {
					if (Jacobsthal) cout << "Adding b" << b_index << " → pend_index " << pend_index << endl;
					insert_order.push_back(pend_index);
					inserted[pend_index] = true;
				}
			}
		}
		group_end = current_end;
	}
	// Add remaining elements (if any)
	for (size_t i = 0; i < pend_size; ++i) {
		if (!inserted[i])
		{
			insert_order.push_back(i);
			inserted[i] = true;
		}
	}
	return insert_order;
}

void	PmergeMe::VecDisplay()
{
	cout << YELLOW << "Before: ";
	if (_size <= 15) {
		for (std::vector<int>::const_iterator it = _numbers_vec.begin();
			 it != _numbers_vec.end(); ++it)
			cout << *it << " ";
	} else {
		std::vector<int>::const_iterator it = _numbers_vec.begin();
		for (int i = 0; i < 4; i++) {
			cout << *it << " ";
			++it;
		}
		cout << "[...] ";
		/// Increments given iterator it by n elements.
		std::advance(it, _numbers_vec.size() - 5);
		cout << *it;
	}
	cout << endl;
	cout << GREEN << "After:  ";
	if (_size <= 15) {
		for (std::vector<int>::const_iterator it = _sorted_numbers_vec.begin();
			 it != _sorted_numbers_vec.end(); ++it)
			cout << *it << " ";
	} else {
		std::vector<int>::const_iterator it = _sorted_numbers_vec.begin();
		for (int i = 0; i < 4; i++, it++) {
			cout << *it << " ";
		}
		cout << "[...] ";
		/// Increments given iterator it by n elements.
		std::advance(it, _sorted_numbers_vec.size() - 5);
		cout << *it;
	}
	cout << RESET << endl;
	if (SORTED) {
		if (isSortedAscending(_sorted_numbers_vec)) cout << GREEN << "Sorted correctly!" << RESET << endl;
			else cout << RED << "Error. Not sorted correctly" << RESET << endl;
	}
}

void	PmergeMe::DeqDisplay()
{
	cout << YELLOW << "_ _ _ Deque sorting _ _ _\nBefore: ";
	if (_size <= 15) {
		display_deque(_numbers_deque);
	} else {
		std::deque<int>::const_iterator it = _numbers_deque.begin();
		for (int i = 0; i < 4; i++) {
			cout << *it << " ";
			++it;
		}
		cout << "[...] ";
		std::advance(it, _numbers_deque.size() - 5);
		cout << *it;
	}
	cout << endl;
	cout << GREEN << "After:  ";
	if (_size <= 15) {
		display_deque(_sorted_numbers_deque);
	} else {
		std::deque<int>::const_iterator it = _sorted_numbers_deque.begin();
		for (int i = 0; i < 4; i++, it++) {
			cout << *it << " ";
		}
		cout << "[...] ";
		std::advance(it, _sorted_numbers_deque.size() - 5);
		cout << *it;
	}
	cout << RESET << endl;
	if (SORTED) {
		if (isSortedAscending(_sorted_numbers_deque)) cout << GREEN << "Sorted correctly!" << RESET << endl;
			else cout << RED << "Error. Not sorted correctly" << RESET << endl;
	}
}

// static
bool PmergeMe::isValidInput(const string &input)
{
	if (input.empty()) {
		cerr << "Error: empty input" << endl;
		return false;
	} else if (input[0] == '-')	{
		cerr << "Error" << endl; // negative integer
		return false;
	}
	for (size_t i = 0; i < input.length(); i++)	{
		if (!std::isdigit(static_cast<unsigned char>(input[i]))) {
			cerr << "Error: " << input[i] << " not a digit" << endl;
			return false;
		}
	}
	return true;
}

bool PmergeMe::parseString(const string &inputstr, std::vector<int> &numbers)
{
	std::istringstream	iss(inputstr);
	long number = 0;
	if (!(iss >> number) || !iss.eof())	{
		cerr << "Error: Invalid integer conversion." << endl;
		return false;
	}
	if (number > INT_MAX || number < 0)	{
		cerr << "Error" << endl;
		return false;
	}
	numbers.push_back(static_cast<int>(number));

	return true;
}

bool PmergeMe::isDuplicates(const std::vector<int> &numbers)
{
	std::set<int> seen;

	for (std::vector<int>::const_iterator it = numbers.begin();
		 it != numbers.end(); ++it)
	{
		if (seen.find(*it) != seen.end())
		{
			cerr << "Duplicate found" << endl;
			return true;
		}
		seen.insert(*it);
	}
	return false;
}

long long	PmergeMe::fordJohnsonWorstCase(int n)
{
	long long C = 0;
	for (int i = 1; i <= n; ++i)
		C += (long long)std::ceil(log2(3.0 * i / 4.0));
	return C;
}

/**
 * The number "1000000L" represents 1 million liters, written 
 * numerically as 1,000,000.
 */
void	PmergeMe::timeDiffVec(const struct timeval& begin, const struct timeval& end) {
	long	seconds  = end.tv_sec - begin.tv_sec;
	long	usecDiff = end.tv_usec - begin.tv_usec;
	this->_totalUsVec  = seconds * 1000000L + usecDiff;
	
	this->_vec_comparisons = PmergeMe::nbr_of_comps;
}

void	PmergeMe::timeDiffDeq(const struct timeval& begin, const struct timeval& end) {
	long	seconds  = end.tv_sec - begin.tv_sec;
	long	usecDiff = end.tv_usec - begin.tv_usec;
	this->_totalUsDeq  = seconds * 1000000L + usecDiff;

	this->_deq_comparisons = PmergeMe::nbr_of_comps;
}

void	PmergeMe::displayVecTime(){
	cout << "Time to process a range of " << this->_size << " elements with std::vector: ";
	cout << _totalUsVec << " µs" << endl;
	//cout << "In ms = " << (_totalUsVec / 1000) << " ms" << std::endl;
}

void	PmergeMe::displayDeqTime(){
	cout << "Time to process a range of " << this->_size << " elements with std::deque:  ";
	cout << _totalUsDeq << " µs" << endl;
	//cout << "In ms = " << (_totalUsDeq / 1000) << " ms" << std::endl;
}

void	PmergeMe::displayVecComparisons(){
	cout << GREEN << "Theoretical max comparisons: ";
	cout << fordJohnsonWorstCase(_size) << endl;
	cout << BLUE << "Number of comparisons:       ";
	cout << this->_vec_comparisons << RESET << endl;
}

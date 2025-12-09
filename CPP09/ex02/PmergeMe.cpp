/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:13 by mpeshko           #+#    #+#             */
/*   Updated: 2025/12/09 10:42:49 by mpeshko          ###   ########.fr       */
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

PmergeMe::PmergeMe(const std::vector<int> &parsed_numbers)
	:
	_numbers_vec(parsed_numbers),
	_numbers_deque(),
	_totalUsVec(0),
	_totalUsDeq(0)
{
	_size = _numbers_vec.size();
}

PmergeMe::PmergeMe(const std::deque<int> &parsed_numbers)
	:
	_numbers_vec(),
	_numbers_deque(parsed_numbers),
	_totalUsVec(0),
	_totalUsDeq(0)
{
	_size = _numbers_deque.size();
}

PmergeMe::~PmergeMe() {}

/* static void display_vector(const std::vector<size_t> & vct) {
	for (std::vector<size_t>::const_iterator it = vct.begin();
		it != vct.end(); ++it)
			cout << *it << " ";
} */

static void	display_vector(const std::vector<int> & vct) {
	for (std::vector<int>::const_iterator it = vct.begin();
		it != vct.end(); ++it)
			cout << *it << " ";
	cout << endl;
}

// Binary search for insertion with a bound
void	PmergeMe::insertInSortedVector(std::vector<int> &vec, int value, size_t bound)
{
	size_t left = 0;
	size_t right = bound;

	while (left < right) 	{
		size_t mid = left + (right - left) / 2;
		PmergeMe::nbr_of_comps++;
		if (vec[mid] < value) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}
	vec.insert(vec.begin() + left, value);
}

/* Recursive method */
void PmergeMe::fordJohnsonSort(std::vector<int> &vec)
{
	++PmergeMe::nbr_of_recur;
	if (DEBUG_RECURSION) {
		cout << GREEN << "fordJohnsonSort() called ";
		cout << PmergeMe::nbr_of_recur << " time(s) with: ";
		for (size_t i = 0; i < vec.size(); ++i)	cout << vec[i] << " ";
		cout << "(size=" << vec.size() << ")" << RESET << endl;
	}
	// Base cases
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
	if (DEBUG_RECURSION) {
		cout << BLUE << "Divide elements into pairs (smaller, larger):\n";
		for (size_t i = 0; i < pairs.size(); ++i)
			cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
		if (has_unpaired)
			cout << BLUE << " + unpaired: " << unpaired_element;
		cout << RESET << endl;
	} 
	
	// Step 2: Extract larger elements (a1, a2, a3, ...) for recursive sorting
	std::vector<int>	larger_elements;
	for (size_t i = 0; i < pairs.size(); ++i)
		larger_elements.push_back(pairs[i].larger);

	if (DEBUG_RECURSION) {
		cout << YELLOW << "Larger elements for recursive sort: ";
		for (size_t i = 0; i < larger_elements.size(); ++i)
			cout << larger_elements[i] << " ";
		cout << RESET << endl;
	}
	// Step 3: Sort recursively
	fordJohnsonSort(larger_elements);
	if (DEBUG_RECURSION) {
		cout << ORANGE << "After " << PmergeMe::nbr_of_recur << " layer of the recursive sort.";
		cout << RESET << endl;
	}
	--PmergeMe::nbr_of_recur;
	if (DEBUG_RECURSION || DEBUG_PART2) {
		cout << ORANGE << "SORTED MAIN CHAIN A : ";
		for (size_t i = 0; i < larger_elements.size(); ++i)
			cout << larger_elements[i] << " ";
		cout << RESET << endl;
	}
	// Step 4: Reorder pairs based on sorted larger elements
	reorderPairs(pairs, larger_elements);
	if (DEBUG_PART2) {
		cout << GREEN << "Reordered pairs:\n";
		for (size_t i = 0; i < pairs.size(); ++i)
			cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
		if (has_unpaired)
			cout << " + unpaired: " << unpaired_element;
		cout << RESET << endl;
	}
	
	// Step 5: Build final result
	buildSortedVector(vec, pairs, unpaired_element, has_unpaired);
	_sorted_numbers_vec = vec;
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

/* Rearrange the pairs according to the sorted larger elements */
void PmergeMe::reorderPairs(std::vector<Pair> &pairs,
							const std::vector<int> &larger_elements)
{

	std::vector<Pair> reordered_pairs;
	for (size_t i = 0; i < larger_elements.size(); ++i)
	{
		// Find a pair with this larger element
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].larger == larger_elements[i])
			{
				reordered_pairs.push_back(pairs[j]);
				pairs.erase(pairs.begin() + j); // Delete the pair found
				break;
			}
		}
	}
	pairs = reordered_pairs;
}

/**
 * Build sorted vector.
 * Create main chain, sorted larger elements, and
 * pend elements, unsorted elements.
 * Generate insertion order based on Jacobsthal numbers.
 * Inserting pend_elements in the sorted main chain.
 */
void PmergeMe::buildSortedVector(std::vector<int> &vec, const std::vector<Pair> &pairs,
								 int unpaired_element, bool has_unpaired)
{
	std::vector<int>	main_chain;	   // (a1, a2, ...)
	std::vector<int>	pend_elements; // (b1, b2, ...) + unpaired
	
	if (DEBUG_PART2) cout << ORANGE << "PART2. Building a sorted vector.\n";
	if (DEBUG_PART2) cout << YELLOW <<  "b1 = " << pairs[0].smaller << " and it first goes to main_chain" << RESET << endl;
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
			insertInSortedVector(vec, pend_elements[index], bound);
			
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

std::vector<size_t> PmergeMe::generateJacobsthalSequence(size_t n)
{

	std::vector<size_t> jac_seq;
	if (n == 0)
		return jac_seq;
	jac_seq.push_back(1); // J(1) = 1
	if (n == 1)
		return jac_seq;
	jac_seq.push_back(1); // J(2) = 1
	if (n == 2)
		return jac_seq;

	// J(k) = J(k-1) + 2*J(k-2)
	for (size_t i = 3; i <= n; ++i)
	{
		size_t next = jac_seq[i - 2] + 2 * jac_seq[i - 3]; // ??
		jac_seq.push_back(next);
	}

	return jac_seq;
}

// порядок Якобсталя: i=3, 2, 5, 4, 11, ...)
// Це дозволить вставляти елементи у ланцюги довжиною 2^k - 1,
// що вимагає найменшої кількості порівнянь.

// функція, яка генерує послідовність індексів вставки pi для поточної
// довжини Вашого Pend List

/* У main_chain вже є b₁, тому pend_elements містить:
pend_elements[0] = b₂  ← Індекс масиву 0 = класичний b₂ */
/* Класичний порядок: (1), (3,2), (5,4) → НЕ потрібен b₁, бо він уже в main_chain
Потрібний порядок: (b₃,b₂), (b₅,b₄) = індекси [1,0], [3,2] */
std::vector<size_t>	PmergeMe::generateInsertionOrder(size_t pend_size)
{
	std::vector<size_t>	insert_order;
	if (pend_size == 0)
		return insert_order;

	std::vector<size_t>	jac_seq = generateJacobsthalSequence(20);
	std::vector<bool>	inserted(pend_size, false);

	// Класична послідовність Якобсталя: 1, 3, 5, 11, 21, ...
	// Групи вставки: (1), (3,2), (5,4), (11,10,9,8,7,6), ...
	// Але b₁ уже в main_chain, тому починаємо з групи (3,2)
	size_t group_end = 1; // Початкова межа (b₁ уже оброблено)

	for (size_t j_index = 1; j_index < jac_seq.size() && insert_order.size() < pend_size; ++j_index) {
		size_t jacob_num = jac_seq[j_index]; // J₂=3, J₃=5, J₄=11, ...

		// Обмежуємо Jacob число розміром pend_elements + 1 (тому що b₁ не в pend)
		size_t current_end = std::min(jacob_num, pend_size + 1);

		if (Jacobsthal) cout << "Jacob group " << j_index << ": from b" << current_end
				  << " down to b" << (group_end + 1) << endl;

		// Вставляємо елементи у зворотному порядку від current_end до group_end+1
		for (size_t b_index = current_end; b_index > group_end; --b_index) {
			// Конвертуємо класичний індекс b_i в індекс pend_elements
			// b₂ → pend[0], b₃ → pend[1], b₄ → pend[2], ...
			if (b_index >= 2) { // Пропускаємо b₁ (він уже в main_chain)
				size_t pend_index = b_index - 2; // b₂→0, b₃→1, b₄→2, ...
				if (pend_index < pend_size && !inserted[pend_index])
				{
					if (Jacobsthal) cout << "Adding b" << b_index << " → pend_index " << pend_index << endl;
					insert_order.push_back(pend_index);
					inserted[pend_index] = true;
				}
			}
		}
		group_end = current_end;
	}
	// Додаємо решту елементів (якщо є)
	for (size_t i = 0; i < pend_size; ++i) {
		if (!inserted[i])
		{
			insert_order.push_back(i);
			inserted[i] = true;
		}
	}

	return insert_order;
}

void	PmergeMe::displayVec()
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

void	PmergeMe::displayVecTime(){
	cout << "Time to process a range of 5 elements with std::vector: ";
	cout << _totalUsVec << " µs" << endl;
	// std::cout << "Time difference in ms = " << (_totalUsVec / 1000) << "[ms]" << std::endl;
}

void	PmergeMe::displayDeqTime(){
	cout << "Time to process a range of 5 elements with std::vector: ";
	cout << _totalUsDeq << " µs" << endl;
	// std::cout << "Time difference in ms = " << (_totalUsVec / 1000) << "[ms]" << std::endl;
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

	std::istringstream iss(inputstr);
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

long long PmergeMe::fordJohnsonWorstCase(int n)
{
	long long C = 0;
	for (int i = 1; i <= n; ++i)
		C += (long long)std::ceil(log2(3.0 * i / 4.0));
	return C;
}

bool PmergeMe::isSortedAscending(const std::vector<int>& vec)
{
	if (vec.size() < 2) return true;
	for (size_t i = 1; i < vec.size(); ++i) {
		if (vec[i - 1] > vec[i]) return false;
	}
	return true;
}

/**
 * The number "1000000L" represents 1 million liters, written 
 * numerically as 1,000,000.
 */
void	PmergeMe::timeDiffVec(const struct timeval& begin, const struct timeval& end) {
	long	seconds  = end.tv_sec - begin.tv_sec;
	long	usecDiff = end.tv_usec - begin.tv_usec;
	this->_totalUsVec  = seconds * 1000000L + usecDiff;
}

void	PmergeMe::timeDiffDeq(const struct timeval& begin, const struct timeval& end) {
	long	seconds  = end.tv_sec - begin.tv_sec;
	long	usecDiff = end.tv_usec - begin.tv_usec;
	this->_totalUsDeq  = seconds * 1000000L + usecDiff;
}

void	PmergeMe::displayVecComparisons(){
	cout << GREEN << "Theoretical max comparisons: ";
	cout << fordJohnsonWorstCase(_size) << endl;
	cout << BLUE << "Number of comparisons:       ";
	cout << PmergeMe::nbr_of_comps << RESET << endl;
}

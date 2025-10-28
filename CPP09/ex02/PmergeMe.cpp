/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:59:13 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/28 19:19:27 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>	// for std::istringstream
#include <cctype>	// for std::isdigit
#include <climits>  // INT_MAX
#include <set>

#include <algorithm> // Для std::min

PmergeMe::PmergeMe(const std::vector<int> & parsed_numbers)
	: _numbers(parsed_numbers) {
		_size = _numbers.size();
	}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& copy) :
	_numbers(copy._numbers) ,
	_sorted_numbers(copy._sorted_numbers)
	{}

PmergeMe& PmergeMe::operator=(const PmergeMe& assign) {
	if (this != &assign) {
		_numbers = assign._numbers;
		_sorted_numbers = assign._sorted_numbers;
	}
	return *this;
}

/* static void display_vector(const std::vector<size_t> & vct) {
	for (std::vector<size_t>::const_iterator it = vct.begin();
		it != vct.end(); ++it)
			std::cout << *it << " ";
} */

/* static void display_vector(const std::vector<int> & vct) {
	for (std::vector<int>::const_iterator it = vct.begin();
		it != vct.end(); ++it)
			std::cout << *it << " ";
} */

// Знаходимо правильну позицію для вставки (binary search)
void PmergeMe::insertInSortedVector(std::vector<int>& vec, int value) {
    
    size_t left = 0;
    size_t right = vec.size();
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (vec[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    // Вставляємо на знайдену позицію
    vec.insert(vec.begin() + left, value);
}

/* Recursive method */
void PmergeMe::sort(std::vector<int>& vec) {
    
	std::cout << "sort() called with: ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << "(size=" << vec.size() << ")" << std::endl;
    
    // Base cases
    if (vec.size() <= 1) {
		this->_sorted_numbers = vec;
        return;
	}
    if (vec.size() == 2) {
        if (vec[0] > vec[1])
            std::swap(vec[0], vec[1]);
		this->_sorted_numbers = vec;
        return;
    }
    
    // Step 1: Create pairs and handle unpaired element
    std::vector<Pair> pairs;
    int unpaired_element = 0;
    bool has_unpaired = false;
    
    if (vec.size() % 2 != 0) {
        has_unpaired = true;
        unpaired_element = vec.back();
    }
    
    // Create pairs from adjacent elements
    for (std::vector<int>::const_iterator it = vec.begin();
         it != vec.end(); ) {
        if ((it + 1) == vec.end()) {
            break; // Odd number, last element handled above
        }
        
        Pair p;
        if (*it > *(it + 1)) {
            p.larger = *it;
            p.smaller = *(it + 1);
        } else {
            p.larger = *(it + 1);
            p.smaller = *it;
        }
        pairs.push_back(p);
        
        ++it;
        if (it != vec.end()) {
            ++it;
        }
    }

	// Debug output
    /* std::cout << "Sort(). Sorted pair before sortPairs(): ";
    for (size_t i = 0; i < pairs.size(); ++i) {
        std::cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
    }
    if (has_unpaired)
        std::cout << " + unpaired: " << unpaired_element;
    std::cout << std::endl; */
	
	// Step 2: Extract larger elements (a1, a2, a3, ...) for recursive
	// Ford-Johnson sorting
    std::vector<int> larger_elements;
    for (size_t i = 0; i < pairs.size(); ++i)
        larger_elements.push_back(pairs[i].larger);
    
    // Add unpaired element to the sorting process - removed
    
    std::cout << "Larger elements for recursive sort: ";
    for (size_t i = 0; i < larger_elements.size(); ++i)
        std::cout << larger_elements[i] << " ";
    std::cout << std::endl;
    
    // Step 3: Sort recursively
    sort(larger_elements);
    
	std::cout << "After recursive sort. Sorted main chain A : ";
    for (size_t i = 0; i < larger_elements.size(); ++i)
        std::cout << larger_elements[i] << " ";
    std::cout << std::endl;

    // Step 4: Reorder pairs based on sorted larger elements
	std::vector<Pair> reordered_pairs;
    
    // Переставляємо пари відповідно до відсортованих larger елементів
    for (size_t i = 0; i < larger_elements.size(); ++i) {
        // Пропускаємо unpaired елемент
        if (has_unpaired && larger_elements[i] == unpaired_element) {
            continue;
        }
        
        // Знаходимо пару з цим larger елементом
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (pairs[j].larger == larger_elements[i]) {
                reordered_pairs.push_back(pairs[j]);
                pairs.erase(pairs.begin() + j);
                break;
            }
        }
    }
    
    pairs = reordered_pairs;
    
    // Debug output
    std::cout << "Reordered pairs: ";
    for (size_t i = 0; i < pairs.size(); ++i)
        std::cout << "(" << pairs[i].smaller << "," << pairs[i].larger << ") ";
    if (has_unpaired)
        std::cout << " + unpaired: " << unpaired_element;
    std::cout << std::endl;
	
    // Step 5: Build final result
    buildSortedVector(vec, pairs, unpaired_element, has_unpaired);
}

void PmergeMe::buildSortedVector(std::vector<int>& vec, const std::vector<Pair>& pairs, 
		int unpaired_element, bool has_unpaired) {
	// Main chain - відсортовані larger елементи
    std::vector<int> main_chain; // (a1, a2, ...)
    std::vector<int> pend_elements; // (b1, b2, ...) + unpaired
    
    for (size_t i = 0; i < pairs.size(); ++i) {
		// b1 to main_chain
		if (i == 0)
			main_chain.push_back(pairs[i].smaller); // b1
		else
			pend_elements.push_back(pairs[i].smaller); // b2, b3, b4, ...
        main_chain.push_back(pairs[i].larger); // a1, a2, a3, ...
    }

	if (has_unpaired)
		pend_elements.push_back(unpaired_element);
    
    std::cout << "Main chain: ";
    for (size_t i = 0; i < main_chain.size(); ++i)
        std::cout << main_chain[i] << " ";
    std::cout << std::endl;
    
    std::cout << "Pend elements: ";
    for (size_t i = 0; i < pend_elements.size(); ++i)
        std::cout << pend_elements[i] << " ";
    std::cout << std::endl;
    
    // Start with main chain
    vec = main_chain;

	// Generate optimal insertion order using Jacobsthal sequence
    std::vector<size_t> insertion_order = generateInsertionOrder(pend_elements.size());
    
	std::cout << "Jacobsthal insertion order: ";
    for (size_t i = 0; i < insertion_order.size(); ++i) {
        std::cout << insertion_order[i] << " ";
    }
    std::cout << std::endl;
	
    // Insert pend elements in Jacobsthal order

	for (size_t i = 0; i < insertion_order.size(); ++i) {
        size_t index = insertion_order[i];
        if (index < pend_elements.size()) {
            std::cout << "Inserting pend_elements[" << index << "] = " 
                     << pend_elements[index] << std::endl;
            insertInSortedVector(vec, pend_elements[index]);
        }
    }
	
    /* for (size_t i = 0; i < pend_elements.size(); ++i) {
        insertInSortedVector(vec, pend_elements[i]);
    } */


    
    _sorted_numbers = vec;
}

std::vector<size_t>	PmergeMe::generateJacobsthalSequence(size_t n) {
	
	std::vector<size_t> jacobsthal;
	if (n == 0)
		return jacobsthal;
	jacobsthal.push_back(1);  // J(1) = 1
	if (n == 1)
		return jacobsthal;
    jacobsthal.push_back(1);  // J(2) = 1  
    if (n == 2)
		return jacobsthal;
    
    // J(k) = J(k-1) + 2*J(k-2)
    for (size_t i = 3; i <= n; ++i) {
        size_t next = jacobsthal[i-2] + 2 * jacobsthal[i-3]; // ??
        jacobsthal.push_back(next);
    }
	
	return jacobsthal;
}

// порядок Якобсталя: i=3, 2, 5, 4, 11, ...)
// Це дозволить вставляти елементи у ланцюги довжиною 2^k - 1, 
// що вимагає найменшої кількості порівнянь.

// функція, яка генерує послідовність індексів вставки pi для поточної 
// довжини Вашого Pend List

// Gemini
/* std::vector<size_t> PmergeMe::generateInsertionOrder(size_t pend_size) {
    
    std::vector<size_t> insertion_order;
    if (pend_size == 0)
        return insertion_order;

    // 1. Генеруємо послідовність Якобсталя
    // Нам потрібні індекси b_i (де i = 2, 3, 4, ...)
    // Класичні J_k: J1=1, J2=3, J3=5, J4=11, ...
    std::vector<size_t> jacobsthal = generateJacobsthalSequence(pend_size + 20); 
    
    // Вектор для відстеження вставлених елементів (індекси 0, 1, 2, ...)
    std::vector<bool> inserted(pend_size, false);
    
    // Індекс k для J_k. Починаємо з k=2, оскільки J1 (b1) вже оброблено.
    // J_2 = 3. Це означає, що ми вставлятимемо елементи аж до b3.
    size_t k = 2; 

    // Вставляємо елемент b1 (класично), якщо він є у Pend List
    // Оскільки B1 вже в main_chain, Pend List починається з b2 (індекс 0).
    // Перша група вставки: B_3 та B_2.
    
    // Починаємо генерацію груп Якобсталя
    while (insertion_order.size() < pend_size) {

        // --- 1. Визначення меж вставки ---
        // target_i: Класичний індекс b_i, який є поточним J_k
        // prev_i: Класичний індекс b_i, який є попереднім J_{k-1}
        
        size_t target_i = 0;
        if (k < jacobsthal.size()) {
            target_i = jacobsthal[k];
        } else {
            // Якщо індекс J_k виходить за межі згенерованого J-списку
            target_i = pend_size + 100; // Просто велике число
        }
        
        // Попереднє число Якобсталя. J1=1, J2=3, J3=5...
        size_t prev_i = (k > 1) ? jacobsthal[k - 1] : 0; 

        // --- 2. Коригування меж під розмір Pend List ---
        // У нас Pend List починається з b2 (індекс 0)
        // target_limit: Кінцевий індекс в Pend List, який ми вставляємо
        // start_i: Початковий індекс в Pend List (після попередньої групи)
        
        size_t start_i = prev_i;

        // --- 3. Вставляємо елементи у зворотному порядку ---
        // Індекси b_i: [..., 4, 3, 2]
        // Індекси в Pend List: [..., 2, 1, 0] (якщо b2, b3, b4)
        
        bool group_inserted = false;
		
		// Ітеруємо від J_k до J_{k-1} + 1 у класичних індексах b_i (тобто спадаємо)
		// Ми використовуємо target_i, оскільки він містить J_k або min(J_k, pend_size+1)
		// Починаємо з індексу J_k. Закінчуємо на індексі J_{k-1} + 1.
		for (size_t i = std::min(target_i, pend_size + 1); i > start_i + 1; --i) { 
			// i - класичний індекс b_i, починаючи від 2.
			// Це забезпечує, що ми отримуємо [J_k, J_{k-1} + 1]
			// pend_index = i - 2 (оскільки b1 ігноруємо, а b2 - це індекс 0)
			size_t pend_index = i - 2; 
			if (pend_index < pend_size && !inserted[pend_index]) {
				insertion_order.push_back(pend_index);
				inserted[pend_index] = true;
				group_inserted = true;
			}
		}
        
        // Якщо не було вставлено жодного елемента, група J_k занадто велика.
        if (!group_inserted && target_i > pend_size) {
             // --- 4. Додаємо решту елементів (лінійно) ---
             for (size_t i = 0; i < pend_size; ++i) {
                 if (!inserted[i]) {
                     insertion_order.push_back(i);
                     inserted[i] = true;
                 }
             }
             break;
        }

        // --- 5. Перехід до наступної групи ---
        k++; 
    }
    
    return insertion_order;
} */

/* У main_chain вже є b₁, тому pend_elements містить:
pend_elements[0] = b₂  ← Індекс масиву 0 = класичний b₂ */
/* Класичний порядок: (1), (3,2), (5,4) → НЕ потрібен b₁, бо він уже в main_chain
Потрібний порядок: (b₃,b₂), (b₅,b₄) = індекси [1,0], [3,2] */
std::vector<size_t> PmergeMe::generateInsertionOrder(size_t pend_size) {
    std::vector<size_t> insertion_order;
    if (pend_size == 0) return insertion_order;

    std::vector<size_t> jacobsthal = generateJacobsthalSequence(20);
    std::vector<bool> inserted(pend_size, false);
    
    // Класична послідовність Якобсталя: 1, 3, 5, 11, 21, ...
    // Групи вставки: (1), (3,2), (5,4), (11,10,9,8,7,6), ...
    // Але b₁ уже в main_chain, тому починаємо з групи (3,2)
    size_t group_end = 1; // Початкова межа (b₁ уже оброблено)
    
    for (size_t j_index = 1; j_index < jacobsthal.size() && insertion_order.size() < pend_size; ++j_index) {
        size_t jacob_num = jacobsthal[j_index]; // J₂=3, J₃=5, J₄=11, ...
        
        // Обмежуємо Jacob число розміром pend_elements + 1 (тому що b₁ не в pend)
        size_t current_end = std::min(jacob_num, pend_size + 1);
        
        std::cout << "Jacob group " << j_index << ": from b" << current_end 
                  << " down to b" << (group_end + 1) << std::endl;
        
        // Вставляємо елементи у зворотному порядку від current_end до group_end+1
        for (size_t b_index = current_end; b_index > group_end; --b_index) {
            // Конвертуємо класичний індекс b_i в індекс pend_elements
            // b₂ → pend[0], b₃ → pend[1], b₄ → pend[2], ...
            if (b_index >= 2) { // Пропускаємо b₁ (він уже в main_chain)
                size_t pend_index = b_index - 2; // b₂→0, b₃→1, b₄→2, ...
                if (pend_index < pend_size && !inserted[pend_index]) {
                    std::cout << "Adding b" << b_index << " → pend_index " << pend_index << std::endl;
                    insertion_order.push_back(pend_index);
                    inserted[pend_index] = true;
                }
            }
        }
        
        group_end = current_end;
    }

	// Додаємо решту елементів (якщо є)
    for (size_t i = 0; i < pend_size; ++i) {
        if (!inserted[i]) {
            insertion_order.push_back(i);
            inserted[i] = true;
        }
    }
    
    return insertion_order;
}

/* std::vector<size_t>	PmergeMe::generateInsertionOrder(size_t pend_size) {
	
	std::vector<size_t> insertion_order;
	
    if (pend_size == 0)
		return insertion_order;
	// Generate Jacobsthal numbers up to pend_size
	// 20 достатньо для практичних цілей
    std::vector<size_t> jacobsthal = generateJacobsthalSequence(20);
	//display_vector(jacobsthal);
    
    std::vector<bool> inserted(pend_size, false);
    size_t jacob_index = 2; // Починаємо з J(3) = 3 // Why not 1?
    
    while (insertion_order.size() < pend_size) {
        // Знайти наступне число Якобсталя <= pend_size
        size_t target = 0;
        if (jacob_index < jacobsthal.size()) {
            target = jacobsthal[jacob_index];
        }
        
        // Якщо Якобсталеве число перевищує розмір, беремо останній елемент
        if (target > pend_size) {
            target = pend_size;
        }
        
        // Вставляємо елементи від target до попереднього Якобсталевого 
		// числа (у зворотному порядку)
        size_t prev_jacob = 1; // За замовчуванням - перше число Якобсталя
		if (jacob_index > 2) {
			prev_jacob = jacobsthal[jacob_index - 1];
		}
        
        for (size_t i = target; i > prev_jacob; --i) {
            if (i <= pend_size && !inserted[i - 1]) { // -1 бо індекси від 0
                insertion_order.push_back(i - 1);
                inserted[i - 1] = true;
            }
        }
        
        jacob_index++;
        
        // Додаємо решту елементів у порядку зростання
        if (jacob_index >= jacobsthal.size() || 
			jacobsthal[jacob_index] > pend_size) {
            for (size_t i = 0; i < pend_size; ++i) {
                if (!inserted[i]) {
                    insertion_order.push_back(i);
                    inserted[i] = true;
                }
            }
            break;
        }
    }
    
    return insertion_order;
} */

void PmergeMe::display() {
	std::cout << "Before: ";
	if (_size <= 5) {
		for (std::vector<int>::const_iterator it = _numbers.begin();
		it != _numbers.end(); ++it)
			std::cout << *it << " ";
	}
	else {
		std::vector<int>::const_iterator it = _numbers.begin();
		for (int i = 0; i < 4; i++) {
			std::cout << *it << " ";
			++it;
		}
		std::cout << "[...] ";
		/// Increments given iterator it by n elements.
		std::advance(it, _numbers.size() - 5);  
		std::cout << *it;
	}
	std::cout << std::endl;
	std::cout << "After:  ";
	if (_size <= 5) {
		for (std::vector<int>::const_iterator it = _sorted_numbers.begin();
		it != _sorted_numbers.end(); ++it)
			std::cout << *it << " ";
	} else {
		std::vector<int>::const_iterator it = _sorted_numbers.begin();
		for (int i = 0; i < 4; i++, it++) {
			std::cout << *it << " ";
		}
		std::cout << "[...] ";
		/// Increments given iterator it by n elements.
		std::advance(it, _sorted_numbers.size() - 5);  
		std::cout << *it;
	}
	std::cout << std::endl;
}

// static
bool	PmergeMe::isValidInput(const std::string & input) {
	if (input.empty()) {
		std::cerr << "Error: empty input" << std::endl;
		return false;
	}
	else if (input[0] == '-') {
		std::cerr << "Error" << std::endl; // negative integer
		return false;
	}
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!std::isdigit(static_cast<unsigned char>(input[i])))
		{
			std::cerr << "Error: " << input[i] << " not a digit" << std::endl;
			return false;
		}
	}
	return true;
}

bool PmergeMe::parseString(const std::string & inputstr, std::vector<int> & numbers) {
	
	std::istringstream iss(inputstr);
	long number = 0;
	if (!(iss >> number) || !iss.eof()) {
		std::cerr << "Error: Invalid integer conversion." << std::endl;
		return false;
	}
	if (number > INT_MAX || number < 0) {
		std::cerr << "Error" << std::endl;
		return false;
	}
	numbers.push_back(static_cast<int>(number));
	
	return true;
}

bool PmergeMe::isDuplicates(const std::vector<int> & numbers) {
	std::set<int> seen;
    
    for (std::vector<int>::const_iterator it = numbers.begin(); 
         it != numbers.end(); ++it) {
        if (seen.find(*it) != seen.end()) {
			std::cerr << "Duplicate found" << std::endl;
            return true; 
        }
        seen.insert(*it);
    }
    return false;
}

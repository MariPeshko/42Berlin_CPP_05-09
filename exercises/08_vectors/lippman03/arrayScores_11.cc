/*
 * This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
 * Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 * 
*/ 

#include <cstddef>
using std::size_t;

#include <vector>
using std::vector;

#include <iostream>
using std::cin; using std::cout; using std::endl;


int main ()
{
	vector<unsigned> grades;
	// count the number of grades by clusters of ten: 
	// 0--9, 10--19, . . . 90--99, 100
	unsigned scores[11] = {};  // 11 buckets, all value initialized to 0
	unsigned grade;
	while (cin >> grade) {
		if (grade <= 100)
			// increment the counter for the current cluster
			++scores[grade/10]; 
		grades.push_back(grade);
	}
	cout << "grades.size = " << grades.size() << endl;

	for (auto g : grades)  // for every element in grades
		cout << g << " " ;
	cout << endl;

	for (auto i : scores)       // for each counter in scores
		cout << i << " ";       // print the value of that counter
	cout << endl;
}

/**
 * C++ 11
 * cc:33:27: error: range-based ‘for’ loops only available with 
 * ‘-std=c++11’ or ‘-std=gnu++11’
 * for (unsigned g : grades)
 *                   ~~~~~~
 * 
 * cc:37:14: error: ‘auto’ changes meaning in C++11; please remove it 
 * [-Werror=c++11-compat]
   37 |         for (auto i : scores) 
                     ~~~~ 
 */

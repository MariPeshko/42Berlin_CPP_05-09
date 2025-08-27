/*
 * This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
 * Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 * 
 * "Copyright (c) 2013 by Objectwrite, Inc., Josee Lajoie, and Barbara E. Moo."
*/ 

#include <vector>
using std::vector;

#include <iostream>
using std::cout; using std::endl; 

// EXERCISES SECTION 3.4.1
// Exercise 3.23
int main()
{
	// C++11
	/* vector<int> v{1,2,3,4,5,6,7,8,9};

	//i is a REFERENCE TO THE ELEMENT (int&)
	for (auto &i : v)
		i *= i;           // square the element value
	for (auto i : v)      // for each element in v
		cout << i << " "; // print the element
	cout << endl; */

	vector<int> v; // {1,2,3,4,5,6,7,8,9};
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(9);

	for (vector<int>::iterator it = v.begin(); it != v.end();
				++it)		// for each element in v (note: i is a reference)
		*it *= *it;			// modifies the element via dereferencing the iterator
	for (vector<int>::iterator it = v.begin(); it != v.end();
				++it)
		cout << *it << " "; // print the element
	cout << endl;

	return 0;
}


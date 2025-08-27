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

	// C++98 version: replace range-based for loop with iterator
	for (vector<unsigned>::iterator it = grades.begin(); it != grades.end(); ++it)
        cout << *it << " ";
    cout << endl;
	
	int cl = 0;
	// C++98 version: replace range-based for loop with traditional for loop
	for (size_t i = 0; i < 11; ++i) {
		if (cl != 100) {
			cout << "Cluster " << cl << "--" << (cl + 9) << ": ";
		} else cout << "Cluster " << cl << "   : ";
        cout << scores[i] << " ";
		cout << endl;
		cl += 10;
	}

	return 0;
}


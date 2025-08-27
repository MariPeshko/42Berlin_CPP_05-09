#include <iostream>
using std::cout; using std::cin; using std::endl;

#include <vector>
using std::vector;

#include <string>
using std::string;

/**
 * TO run a program:
 * 
 * ./binary_search < ../data/sorted_list
 * 
 */

// 3.4.2 Iterator Arithmetic. // Using Iterator Arithmetic p. 112
// Exercise 3.26

// Exercise 3.26: In the binary search program on page 112, why did 
// we write mid = beg + (end - beg) / 2; instead of mid = (beg + end) /2;?
// Answer:
// 1. Compiler: "no operator "+" matches these operands"
// 2. For vector<int>::iterator, beg + end is undefined (can’t add two iterators).
// 3. But end - beg is valid (gives a distance, like ptrdiff_t). 
//    Then beg + distance/2 works fine.

int	main ( void )
{
	vector<string>	text;

	string	line;
	while (getline(cin, line))
		text.push_back(line);

	string	sought = "f";
	
	// beg and end will denote the range we’re searching
	auto beg = text.begin();
	auto end = text.end();

	auto mid = text.begin() + (end - beg)/2; // original midpoint

	// while there are still elements to look at and we haven’t yet found sought
	while (mid != end && *mid != sought) {
		if (sought < *mid) // is the element we want in the first half?
			end = mid; // if so, adjust the range to ignore the second half
		else // the element we want is in the second half
			beg = mid + 1; // start looking with the element just after mid
		mid = beg + (end - beg)/2; // new midpoint
	}

	if (mid != text.end() && *mid == sought)
		cout << "It is found on the line " << (mid - text.begin()) + 1 << endl;
	else
		cout << "There is no " << sought << " in the text." << endl;
	
	return 0;
}

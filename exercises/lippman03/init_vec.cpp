//Table 3.4: Ways to Initialize a vector
/* Exercise 9.11: Show an example of each of the six ways to create 
and initialize a vector. Explain what values each vector contains. */

#include <vector>
using std::vector;

int main (void)
{
	int n = 5;
	int val = 42;

	// 
	// 1 way
    vector<int> v1;				//vector that holds objects of type T. Default initialization;
    							// v1 is empty.
	// 2 way
    vector<int> v2(v1);			// v2 has a copy of each element in v1.
    vector<int> v2 = v1;		// Equivalent to v2(v1), v2 is a copy of the elements in v1.
    
	// 3 way
	vector<int> v3(n, val);		// v3 has n elements with value val.

	// 4 way
    vector<int> v4(n);			// v4 has n copies of a value-initialized object.
								// (0 for ints)
	
	// 5 way
	int a = 10;
	int b = 20; 
	int c = 30;
	vector<int> v5{a,b,c}; 		// v5 has as many elements as there are initializers; 
								// elements are initialized by corresponding initializers.
    vector<int> v5 = {a,b,c};	// Equivalent to v5{a,b,c . . . }

	vector<int> v5{1, 2, 3};	// you could use literal values directly

	// 6 way Range constructor (from iterators/pointers)
	int arr[] = {1, 2, 3};
	std::vector<int> v5(arr, arr + 3);  // v5 has 3 elements copied from the array
}
#include <iostream>

#include <iostream>
using std::cout; using std::endl;

#include <functional>
using std::less;

#include <cstring>
using std::strcmp;

// version of compare that will be correct even if used on pointers
/* template <typename T> int compare(const T &v1, const T &v2)
{
	cout << "compare(T)" << "\t";

	if (less<T>()(v1, v2)) return -1;
	if (less<T>()(v2, v1)) return 1;

	return 0;
} */

// implement strcmp-like generic compare function 
// returns 0 if the values are equal, 1 if v1 is larger, -1 if v1 is smaller
template <typename T>
int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

///

int	main( void ) {

	int	a = 21;
	int	b = 42;

	if (compare(a, b) == 1)
		cout << "v2 < v1 OR less v2 v1" << endl;
	else
		cout << "v1 < v2 or less v1 v2" << endl;
	
	return 0;

}
// Templates must be defined in the header files.

#ifndef	WHATEVER_HPP
# define WHATEVER_HPP

template < typename T >
void	swap( T & x, T & y) {

	T	tmp = y;
	y = x;
	x = tmp;
	return ;
}

// For built-in types and std::string, < is already defined.
/* When you use the < (less than) operator with std::string 
objects in C++, it performs a lexicographical comparison. */
template < typename T >
T const &	min( T const & x, T const & y ) {
	 if (x < y) {
        return x;
    } else {
        return y;
    }
}

#endif
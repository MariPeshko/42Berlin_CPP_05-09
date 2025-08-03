#include <iostream>

// class template


template< typename T >
class List {

private:
	T *			_content;
	List<T> *	_next;

public:
    List<T>( T const & content) {
		// Etc...
	}

	List<T>( List<T> const & list ) {
		// Etc...
	}

    ~List( void ) {
		// Etc...
	}

	// Etc...

};

// *************************************************** //

int	main( void ) {

	List< int >			a( 42 );
	List< float >		b( 3.14f );
	List< List< int > >	c( a );

	return 0;
}

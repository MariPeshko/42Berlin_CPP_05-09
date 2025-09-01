/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:24:04 by mpeshko           #+#    #+#             */
/*   Updated: 2025/09/01 21:57:03 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <stack>

/**
 * Template class MutantStack<T> is derived from class std::stack<T>.
 * 
 */
template <typename T>
class	MutantStack : public std::stack<T> {
	
	private:
	
	public:
		MutantStack() 
			: std::stack<T>() {};
		~MutantStack() {};
		MutantStack(const MutantStack & copy)
			: std::stack<T>(copy) {};
		MutantStack & operator=(const MutantStack & assign) {
			if (this != &assign)
				std::stack<T>::operator=(assign);
			return *this;
		};
		
		// The compiler doesn’t know if iterator is a type or a static 
		// member/variable until T is substituted. The keyword typename 
		// tells the compiler: “Trust me, this is a type.”
		// So: typedef typename is the way to define an alias for 
		// a dependent type inside templates.
		typedef typename std::stack<T>::container_type::iterator iterator;
		iterator begin() {
			return this->c.begin();
		};
		iterator end() {
			return this->c.end();
		};

};

#endif
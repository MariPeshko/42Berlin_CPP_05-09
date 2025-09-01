/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:24:04 by mpeshko           #+#    #+#             */
/*   Updated: 2025/09/01 19:30:45 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <stack>

template <typename T>
class	MutantStack : public std::stack<T> {
	
	private:
	
	public:
		MutantStack() {};
		~MutantStack() {};
		MutantStack(const std::stack<T> & copy)
			: std::stack<T>(copy) {};
		MutantStack & operator=(const MutantStack & assign) {
			if (this != &assign)
				std::stack<T>::operator=(assign);
			return *this;
		};
		
		
	
};

#endif
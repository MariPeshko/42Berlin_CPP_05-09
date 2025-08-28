/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:22:15 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/28 22:14:21 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>

class Span {
	
private:
	const unsigned int	_N;
	std::vector<int> _numbers;

public:
    // Orthodox Canonical Form
    Span();
    Span(unsigned int N);
	Span(const Span & copy);
	Span & operator=(const Span & assign);
	~Span();

    unsigned int		getN() const;

	/* // Subscript Operator Overloading 
	T&			operator[](const unsigned int &index);
	const T&	operator[](const unsigned int &index) const; */
	
	unsigned int	size() const;
};

std::ostream &	operator<<(std::ostream &o, Span const &i);

#endif
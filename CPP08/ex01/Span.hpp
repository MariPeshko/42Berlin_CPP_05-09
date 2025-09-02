/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:22:15 by mpeshko           #+#    #+#             */
/*   Updated: 2025/09/02 11:16:36 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <vector>

class	Span {
	
private:
	const unsigned int	_N;
	std::vector<int>	_numbers;

public:
	// Orthodox Canonical Form
	Span();
	Span(unsigned int N);
	Span(const Span & copy);
	~Span();
	Span & operator=(const Span & assign);
	
	void			addNumber(int number);
	void			addManyNumbers(std::vector<int> & v);
	unsigned long	longestSpan() const;
	unsigned long	shortestSpan() const;
	unsigned int	getN() const;
	void			print() const;

};

std::ostream &	operator<<(std::ostream &o, Span const &i);

#endif

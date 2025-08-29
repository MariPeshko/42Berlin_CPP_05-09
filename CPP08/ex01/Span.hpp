/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:22:15 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/29 19:00:47 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <vector>

class Span {
	
private:
	const unsigned int	_N;
	std::vector<int>	_numbers;

public:
    // Orthodox Canonical Form
    Span();
    Span(unsigned int N);
	Span(const Span & copy);
	Span & operator=(const Span & assign);
	~Span();

    unsigned int	getN() const;
	void			addNumber(int number);
	unsigned long	longestSpan() const;
	unsigned long	shortestSpan() const;
	void			print() const;
	
};

std::ostream &	operator<<(std::ostream &o, Span const &i);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:01:43 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/18 18:33:04 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class	ScalarConverter
{
	public:
		// Do I need it?
		// a private constructor? (it's from the eval sheet)
		// it must not be instantiable by users - private ot "= deleted"

		/* ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter &operator=(const ScalarConverter &other); */

	static int convert(std::string const &literal);
};

#endif           // SCALARCONVERTER_HPP
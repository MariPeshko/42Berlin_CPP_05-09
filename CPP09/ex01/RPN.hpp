/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:04:02 by mpeshko           #+#    #+#             */
/*   Updated: 2025/10/12 21:06:17 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <string>

class RPN {
	private:
		std::stack<int> _rev_notation;
		bool	isValidInput(const std::string & input);
		bool	Operation(char c);

	public:
		RPN();
		~RPN();
		RPN(const RPN& copy);
		RPN& operator=(const RPN& assign);
		
		void Calculate(const std::string & input);
};

#endif

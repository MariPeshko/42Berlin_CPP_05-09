/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:42:29 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/12 21:07:28 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include "AForm.hpp"
#include <iostream>
#include <string>

class	Intern {
	
	public:
		Intern( void );
		Intern (Intern const & src);
		Intern &	operator=( Intern const &assign );
		~Intern();

		AForm*	makeForm(std::string formName, std::string formTarget);

		AForm*	ShrubCreation(std::string formTarget);
		AForm*	RobotomyCreation(std::string formTarget);
		AForm*	PresidentialCreation(std::string formTarget);

};

#endif

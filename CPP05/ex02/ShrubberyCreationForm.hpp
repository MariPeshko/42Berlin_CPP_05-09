/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:17:21 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/11 18:34:11 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include <iostream>
#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {
	
public:

	ShrubberyCreationForm( void );
	ShrubberyCreationForm( std::string target );
	ShrubberyCreationForm (ShrubberyCreationForm const & src);
	ShrubberyCreationForm &	operator=( ShrubberyCreationForm const &assign );
	~ShrubberyCreationForm();

	void				action() const;
	const std::string &	getTarget() const;
	
private:
	std::string			_target;

};

std::ostream &operator<<(std::ostream &o, const ShrubberyCreationForm &form);

#endif
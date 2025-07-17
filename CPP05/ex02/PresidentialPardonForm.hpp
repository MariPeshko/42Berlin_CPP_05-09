/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:56:27 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/12 14:58:59 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include <iostream>
#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
	
public:

	PresidentialPardonForm( void );
	PresidentialPardonForm( std::string target );
	PresidentialPardonForm (PresidentialPardonForm const & src);
	PresidentialPardonForm &	operator=( PresidentialPardonForm const &assign );
	~PresidentialPardonForm();

	void				action() const;
	const std::string &	getTarget() const;
	
private:
	std::string			_target;

};

std::ostream &operator<<(std::ostream &o, const PresidentialPardonForm &form);

#endif
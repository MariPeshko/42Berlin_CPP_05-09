/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:51:01 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/12 14:52:39 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include <iostream>
#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
	
public:

	RobotomyRequestForm( void );
	RobotomyRequestForm( std::string target );
	RobotomyRequestForm (RobotomyRequestForm const & src);
	RobotomyRequestForm &	operator=( RobotomyRequestForm const &assign );
	~RobotomyRequestForm();

	void				action() const;
	const std::string &	getTarget() const;
	
private:
	std::string			_target;

};

std::ostream &operator<<(std::ostream &o, const RobotomyRequestForm &form);

#endif
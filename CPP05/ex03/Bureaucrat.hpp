/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:40:36 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/24 12:54:25 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include "AForm.hpp"
#include <iostream>
#include <string>
#include <exception>

class	Bureaucrat {
	
	public:
		Bureaucrat( void );
		Bureaucrat(int grade, std::string name);
		Bureaucrat (Bureaucrat const & src);
		Bureaucrat &	operator=( Bureaucrat const &assign );
		~Bureaucrat();

		int					getGrade() const;
		const std::string&	getName() const;
		void				upgrade();
		void				downgrade();

		void				signForm(AForm &f);

		void				executeForm(AForm const & form);

		// override the what() method
		class GradeTooHighException : public std::exception { 
			public:
				const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const throw();
		};

	private:
		int					_grade;
		const std::string	_name;

};

std::ostream &	operator<<(std::ostream &o, Bureaucrat const &i);

#endif
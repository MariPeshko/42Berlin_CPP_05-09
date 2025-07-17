/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:40:36 by mpeshko           #+#    #+#             */
/*   Updated: 2025/07/10 20:20:41 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include "Form.hpp"
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

		unsigned int		getGrade() const;
		const std::string&	getName() const;
		void				upgrade();
		void				downgrade();

		void				signForm(Form &f);

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
		const std::string	_name;
		int					_grade;

};

std::ostream &	operator<<(std::ostream &o, Bureaucrat const &i);

#endif
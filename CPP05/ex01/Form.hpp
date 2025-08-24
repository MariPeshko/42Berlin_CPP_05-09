/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:17:35 by mpeshko           #+#    #+#             */
/*   Updated: 2025/08/24 12:50:40 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class	Form {
	
	public:
		Form( void );
		Form( std::string name, int grade, int exgrade );
		Form (Form const & src);
		Form &	operator=( Form const &assign );
		~Form();

		int					getGrade() const;
		int					getExGrade() const;
		const std::string&	getName() const;
		const std::string	getSigned() const;
		bool				getBoolSigned() const;

		void				beSigned(Bureaucrat &b);

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
		bool				_signed;
		const int			_formGrade;
		const int			_formGradeExe;

};

std::ostream &	operator<<(std::ostream &o, Form const &i);

#endif
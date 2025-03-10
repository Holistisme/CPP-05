#pragma once

/* ############################################################################################## */

#include "../Form/Form.hpp"

/* ############################################################################################## */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

/* ############################################################################################## */

class Form;

/* ############################################################################################## */

class Bureaucrat {
	private:
		const std::string	_name;
		unsigned int		_grade;

		const std::string &setRandomName(void);

		void gradeValidity(const unsigned int request);
	public:
		explicit Bureaucrat(void);
		Bureaucrat(const std::string &name, const unsigned int grade);
		Bureaucrat(const Bureaucrat &source);
	
		Bureaucrat &operator=(const Bureaucrat &source);

		~Bureaucrat(void);

		const std::string &getName(void) const;
		unsigned int	  getGrade(void) const;

		void incrementGrade(void);
		void decrementGrade(void);

		void signForm(Form &form);

		class GradeTooHighException	: public std::exception { public: const char* what() const throw(); };
		class GradeTooLowException	: public std::exception { public: const char* what() const throw(); };
};

/* ############################################################################################## */

std::ostream &operator<<(std::ostream &stream, const Bureaucrat &bureaucrat);
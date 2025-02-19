#pragma once

/* ############################################################################################## */

#include "../Bureaucrat/Bureaucrat.hpp"

/* ############################################################################################## */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

/* ############################################################################################## */

class Form {
	private:
		const std::string  _name;
		bool			   _signed;
		const unsigned int _requiredGrade;
		const unsigned int _executableGrade;

		const std::string &setRandomName(void) const;

		void gradeValidity(const unsigned int request);
	public:
		explicit Form(void);
		Form(const std::string &name, const unsigned int requiredGrade, const unsigned int executableGrade);
		Form(const Form &source);
	
		Form &operator=(const Form &source);

		~Form(void);

		const std::string &getName(void)		   const;
		bool	 		  isSigned(void)		   const;
		unsigned int	  getRequiredGrade(void)   const;
		unsigned int	  getExecutableGrade(void) const;

		void beSigned(const Bureaucrat &bureaucrat);

		class GradeTooHighException	: public std::exception { public: const char* what() const throw(); };
		class GradeTooLowException	: public std::exception { public: const char* what() const throw(); };
		class IsAlreadySigned		: public std::exception { public: const char* what() const throw(); };
};

/* ############################################################################################## */

std::ostream &operator<<(std::ostream &stream, const Form &form);
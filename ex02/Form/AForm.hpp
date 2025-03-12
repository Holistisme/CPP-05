#pragma once

/* ############################################################################################## */

#include "../Bureaucrat/Bureaucrat.hpp"

/* ############################################################################################## */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

/* ############################################################################################## */

class Bureaucrat;

/* ############################################################################################## */

class AForm {
	private:
		const std::string  _name;
		bool			   _signed;
		const unsigned int _requiredGrade;
		const unsigned int _executableGrade;

		void gradeValidity(const unsigned int request);
	public:
		explicit AForm(void);
		AForm(const std::string &name, const unsigned int requiredGrade, const unsigned int executableGrade);
		AForm(const AForm &source);
	
		AForm &operator=(const AForm &source);

		virtual ~AForm(void);

		const std::string &setRandomName(void) const;

		const std::string &getName(void)		   const;
		bool	 		  isSigned(void)		   const;
		unsigned int	  getRequiredGrade(void)   const;
		unsigned int	  getExecutableGrade(void) const;

		void beSigned(const Bureaucrat &bureaucrat);

		void		 checkExecution(const Bureaucrat &executor) const;
		virtual void execute(const Bureaucrat &executor)		const = 0;

		class GradeTooHighException	: public std::exception { public: const char* what() const throw(); };
		class GradeTooLowException	: public std::exception { public: const char* what() const throw(); };
		class IsAlreadySigned		: public std::exception { public: const char* what() const throw(); };
		class IsNotSigned			: public std::exception { public: const char* what() const throw(); };
};

/* ############################################################################################## */

std::ostream &operator<<(std::ostream &stream, const AForm &aform);
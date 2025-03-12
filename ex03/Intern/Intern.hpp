#pragma once

/* ############################################################################################## */

#include "../Form/AForm.hpp"

#include "../Form/PresidentialPardonForm/PresidentialPardonForm.hpp"
#include "../Form/RobotomyRequestForm/RobotomyRequestForm.hpp"
#include "../Form/ShrubberyCreationForm/ShrubberyCreationForm.hpp"

/* ############################################################################################## */

#include <iostream>
#include <stdexcept>

/* ############################################################################################## */

class AForm;

/* ############################################################################################## */

class Intern {
	public:
		explicit Intern(void);
		Intern(const Intern &source);
	
		Intern &operator=(const Intern &source);

		~Intern(void);

		AForm *makeForm(const std::string &name, const std::string &target) const;
};
#pragma once

/* ############################################################################################## */

#include "./../AForm.hpp"
#include "./../../ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

class PresidentialPardonForm : public AForm {
	private:
		std::string _target;
	public:
		explicit PresidentialPardonForm(const std::string &target);
		PresidentialPardonForm(const PresidentialPardonForm &source);

		PresidentialPardonForm &operator=(const PresidentialPardonForm &source);

		~PresidentialPardonForm(void);

		const std::string setRandomName(void) const;

		void execute(const Bureaucrat &executor) const;
};
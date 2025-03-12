#pragma once

/* ############################################################################################## */

#include "./../AForm.hpp"
#include "./../../ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

#include <fstream>

/* ############################################################################################## */

class ShrubberyCreationForm : public AForm {
	private:
		std::string _target;
	public:
		explicit ShrubberyCreationForm(const std::string &target);
		ShrubberyCreationForm(const ShrubberyCreationForm &source);

		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &source);

		~ShrubberyCreationForm(void);

		const std::string setRandomName(void) const;

		void execute(const Bureaucrat &executor) const;

		static AForm *create(const std::string &target);
};
#pragma once

/* ############################################################################################## */

#include "./../AForm.hpp"
#include "./../../ColorFormatLib/ColorFormat.hpp"

#include <cstdlib>

/* ############################################################################################## */

class RobotomyRequestForm : public AForm {
	private:
		std::string _target;
	public:
		explicit RobotomyRequestForm(const std::string &target);
		RobotomyRequestForm(const RobotomyRequestForm &source);

		RobotomyRequestForm &operator=(const RobotomyRequestForm &source);

		~RobotomyRequestForm(void);

		const std::string setRandomName(void) const;

		void execute(const Bureaucrat &executor) const;
};
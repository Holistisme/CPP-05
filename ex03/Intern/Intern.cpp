#include "./Intern.hpp"

/* ############################################################################################## */

Intern::Intern(void)				 {				 }
Intern::Intern(const Intern &source) { (void)source; }

Intern &Intern::operator=(const Intern &source) {
	(void)source;
	return *this;
}

Intern::~Intern(void) {}

/* ############################################################################################## */

AForm *Intern::makeForm(const std::string &name, const std::string &target) const {
	struct formCreation {
		const std::string &name;
		AForm			  *(*create)(const std::string &name);
	};

	formCreation formList[3] = {
		{"Presidential Pardon", &PresidentialPardonForm::create},
		{"Robotomy Request",	&RobotomyRequestForm::create},
		{"Shrubbery Creation",	&ShrubberyCreationForm::create}
	};

	for (size_t i = 0 ; i < 3 ; i++)
		if (name == formList[i].name) {
			AForm *form = formList[i].create(target);
			std::cout << "Intern creates " << ColorFormat::formatString(form->getName(), "magenta", "italic") << '.' << std::endl;
			return form;
		}

	std::cerr << ColorFormat::formatString("Intern", "red", "strikethrough") << " could not create the inexistent form "
			  << ColorFormat::formatString(not name.empty() ? name : "???", "magenta") << ". Because of you he got fired! But who cares?" << std::endl;
	return (NULL);
}
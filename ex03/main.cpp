#include "Bureaucrat/Bureaucrat.hpp"
#include "Intern/Intern.hpp"
#include "Form/AForm.hpp"
#include "Form/PresidentialPardonForm/PresidentialPardonForm.hpp"
#include "Form/RobotomyRequestForm/RobotomyRequestForm.hpp"
#include "Form/ShrubberyCreationForm/ShrubberyCreationForm.hpp"

/* ############################################################################################## */

#include "ColorFormatLib/ColorFormat.hpp"
#include "InputLib/Input.hpp"

/* ############################################################################################## */

static Bureaucrat trainBureaucrat(const std::string &prompt);

/* ############################################################################################## */


int main(void) {
	try {
		std::cout << "Welcome in " << ColorFormat::formatString("InternJob™", "yellow", "blink", "bold") << '!' << std::endl;
		std::srand(time(0));

		while (true) {
			Bureaucrat signatory = trainBureaucrat("\n=== Time to train a bureaucrat for a future signature! ===\n");
			Bureaucrat executor	 = trainBureaucrat("\n=== Time to train a bureaucrat for a future execution! ===\n");
			Intern	   intern;

			std::cout << "\nThe new signatory is " << signatory << std::endl;
			std::cout << "The new executor is "	 << executor  << std::endl;
	
			std::cout << "\nThree forms are available for signature and execution: [" << ColorFormat::formatString("Signature", "cyan", "italic") << " - " << ColorFormat::formatString("Execution", "yellow", "italic") << "]" << std::endl;
			std::cout << "Presidential Pardon [" << ColorFormat::formatString("25", "cyan", "italic") << " - " << ColorFormat::formatString("5", "yellow", "italic") << "]" << std::endl;
			std::cout << "Robotomy Request [" << ColorFormat::formatString("72", "cyan", "italic") << " - " << ColorFormat::formatString("45", "yellow", "italic") << "]" << std::endl;
			std::cout << "Shrubbery Creation [" << ColorFormat::formatString("145", "cyan", "italic") << " - " << ColorFormat::formatString("137", "yellow", "italic") << "]" << std::endl;
	
			AForm *form = intern.makeForm(Input ("\nChoose the form type (in words):").stringFormat(), "");
			if (form) {
				signatory.signForm(*form);
				executor.executeForm(*form);
				delete form;
			}
			std::cout << ColorFormat::formatString("\n\n\n=== Let's move on to the next test! ===\n\n", "bold", "underline") << std::endl;
		}
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

static Bureaucrat trainBureaucrat(const std::string &prompt) {
	std::cout << ColorFormat::formatString(prompt, "bold") << std::endl;

	Input		 bureaucratName("What " + ColorFormat::formatString("name", "cyan") + " to give the bureaucrat (leave empty for skip)?");
	unsigned int grade = 0;

	if (not bureaucratName.stringFormat().empty()) {
		Input bureaucratGrade("What level of " + ColorFormat::formatString("grade", "yellow") + " to give the bureaucrat?");

		try { grade = bureaucratGrade.unsignedIntegerFormat(); }
		catch (...) {
			std::cout << "In the absence of a valid grade, the bureaucrat will " << ColorFormat::rainbow("randomly", "blink") << " draw one!\n" << std::endl;
			grade = rand() % 150 + 1;
		}

		try {
			Bureaucrat bureaucrat(bureaucratName.stringFormat(), grade);
			return bureaucrat;
		}
		catch (const Bureaucrat::GradeTooHighException &e) { std::cerr << e.what() << std::endl; }
		catch (const Bureaucrat::GradeTooLowException  &e) { std::cerr << e.what() << std::endl; }
	}
	std::cout << "A " << ColorFormat::rainbow("random", "blink") << " bureaucrat will come forward!" << std::endl;
	Bureaucrat bureaucrat;
	return bureaucrat;
}
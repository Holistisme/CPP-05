#include "Bureaucrat/Bureaucrat.hpp"
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
		std::cout << "Welcome in " << ColorFormat::formatString("Execution™", "red", "blink", "bold") << '!' << std::endl;
		std::srand(time(0));

		while (true) {
			Bureaucrat signatory = trainBureaucrat("\n=== Time to train a bureaucrat for a future signature! ===\n");
			Bureaucrat executor	 = trainBureaucrat("\n=== Time to train a bureaucrat for a future execution! ===\n");
			std::cout << "\nThe new signatory is " << signatory << std::endl;
			std::cout << "The new executor is "	 << executor  << std::endl;
	
			std::cout << "\nThree forms are available for signature and execution: [" << ColorFormat::formatString("Signature", "cyan", "italic") << " - " << ColorFormat::formatString("Execution", "yellow", "italic") << "]" << std::endl;
			std::cout << "1 - Presidential Pardon Form [" << ColorFormat::formatString("25", "cyan", "italic") << " - " << ColorFormat::formatString("5", "yellow", "italic") << "]" << std::endl;
			std::cout << "2 - Robotomy Request Form [" << ColorFormat::formatString("72", "cyan", "italic") << " - " << ColorFormat::formatString("45", "yellow", "italic") << "]" << std::endl;
			std::cout << "3 - Shrubbery Creation Form [" << ColorFormat::formatString("145", "cyan", "italic") << " - " << ColorFormat::formatString("137", "yellow", "italic") << "]" << std::endl;
	
			unsigned int formToExecute;
			while (true) {
				try {
					formToExecute = Input ().unsignedIntegerFormat();
					if (formToExecute >= 1 and formToExecute <= 3)
						break;
					else
						std::cerr << "Error: Bureaucrats know how to count. And they know you don't." << std::endl;
				} catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
			}
	
			std::string target = Input ("Choose the form target (you can always leave it blank if you want fun):").stringFormat();
			AForm *form = NULL;
			PresidentialPardonForm presidentialPardonForm(target);
			RobotomyRequestForm    robotomyRequestForm(target);
			ShrubberyCreationForm  shrubberyCreationForm(target);
	
			switch (formToExecute) {
				case 1: form = &presidentialPardonForm; break;
				case 2: form = &robotomyRequestForm;	break;
				case 3: form = &shrubberyCreationForm;	break;
			}

			signatory.signForm(*form);
			executor.executeForm(*form);
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
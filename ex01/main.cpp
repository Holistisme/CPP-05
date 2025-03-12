#include "Bureaucrat/Bureaucrat.hpp"
#include "Form/Form.hpp"

/* ############################################################################################## */

#include "ColorFormatLib/ColorFormat.hpp"
#include "InputLib/Input.hpp"

/* ############################################################################################## */

static void awardCeremony(Bureaucrat &bureaucrat);
static void bureaucratSignature(Bureaucrat &bureaucrat);

/* ############################################################################################## */


int main(void) {
	try {
		std::cout << "Welcome in " << ColorFormat::formatString("FormUp™", "magenta", "blink", "bold") << '!' << std::endl;
		std::srand(time(0));

		while (true) {
			try {
				std::cout << ColorFormat::formatString("\n=== Let's create a custom form! ===\n", "bold") << std::endl;
				Form customForm(Input ("What " + ColorFormat::formatString("name", "magenta") + " should we give it?").stringFormat(),
								Input ("Grade required for " + ColorFormat::formatString("signature", "blue") + ":").unsignedIntegerFormat(),
								Input ("Grade required for " + ColorFormat::formatString("signature", "yellow") + ":").unsignedIntegerFormat());
				std::cout << '\n' << customForm << std::endl;
				Bureaucrat("Rick Astley", 1).signForm(customForm);
				Bureaucrat("Nick Rustley", 5).signForm(customForm);
				break;
			} catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
		}

		while (true) {
			std::cout << ColorFormat::formatString("\n=== Time to form a bureaucrat for a future signature! ===\n", "bold") << std::endl;
			Input		 bureaucratName("What " + ColorFormat::formatString("name", "cyan") + " to give the bureaucrat (leave empty for skip)?");
			unsigned int grade = 0;

			if (not bureaucratName.stringFormat().empty()) {
				Input bureaucratGrade("What level of " + ColorFormat::formatString("grade", "yellow") + " to give the bureaucrat?");

				try { grade = bureaucratGrade.unsignedIntegerFormat(); }
				catch (...) {
					std::cout << "In the absence of a valid grade, the bureaucrat will " << ColorFormat::rainbow("randomly", "blink") << " draw one!" << std::endl;
					grade = rand() % 150 + 1;
				}
				std::cout << std::endl;

				try {
					Bureaucrat bureaucrat(bureaucratName.stringFormat(), grade);
					awardCeremony(bureaucrat);
				}
				catch (const Bureaucrat::GradeTooHighException &e) { std::cerr << e.what() << std::endl; }
				catch (const Bureaucrat::GradeTooLowException  &e) { std::cerr << e.what() << std::endl; }
			}
			else {
				std::cout << "A " << ColorFormat::rainbow("random", "blink") << " bureaucrat will come forward!\n" << std::endl;
				Bureaucrat bureaucrat;
				awardCeremony(bureaucrat);
			}

			std::cout << std::endl;
			std::cout << ColorFormat::formatString("Let's move on to another bureaucrat...", "italic") << '\n' << std::endl;
		}
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
}

static void awardCeremony(Bureaucrat &bureaucrat) {
	std::cout << bureaucrat << std::endl;
	if (std::rand() % 2) {
		std::cout << "Sorry " << ColorFormat::formatString(bureaucrat.getName(), "blue", "italic") << ", but you " << ColorFormat::formatString("cheated", "red", "underline") << '!' << std::endl;
		try { bureaucrat.decrementGrade(); }
		catch (const Bureaucrat::GradeTooLowException &e) {
			std::cerr << ColorFormat::formatString(bureaucrat.getName(), "red", "strikethrough") << ColorFormat::formatString(", YOUR INTELLECTUAL INFERIORITY AMAZES US ALL, YOU ARE EXCLUDED!", "red", "bold") << std::endl;
			return;
		}
	}
	else {
		std::cout << "A little " << ColorFormat::formatString("outstanding", "green", "underline") << " for you, " << ColorFormat::formatString(bureaucrat.getName(), "blue", "italic") << '!' << std::endl;
		try { bureaucrat.incrementGrade(); }
		catch (const Bureaucrat::GradeTooHighException &e) {
			std::cerr << ColorFormat::formatString(bureaucrat.getName(), "green", "bold") << ColorFormat::formatString(", YOUR INTELLECTUAL SUPERIORITY AMAZES US ALL, SO TAKE OVER THE PRESIDENCY!", "green", "italic") << std::endl;
		}
	}
	std::cout << bureaucrat << std::endl;
	bureaucratSignature(bureaucrat);
}

static void bureaucratSignature(Bureaucrat &bureaucrat) {
	Form form;
	std::cout << ColorFormat::formatString("\n=== Let's sign a random form! ===\n", "bold") << std::endl;
	std::cout << form << std::endl;

	try {
		std::cout << "The bureaucrat tries to sign it..." << std::endl;
		bureaucrat.signForm(form);
		if (form.isSigned() and Input ("The signature is " + ColorFormat::formatString("dirty", "red") + ", should the bureaucrat re-sign? (" + ColorFormat::formatString("y", "green") + " to continue)").stringFormat() == "y")
			bureaucrat.signForm(form);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}
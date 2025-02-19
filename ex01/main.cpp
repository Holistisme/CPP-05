#include "Bureaucrat/Bureaucrat.hpp"
#include "Form/Form.hpp"

/* ############################################################################################## */

#include "ColorFormatLib/ColorFormat.hpp"
#include "InputLib/Input.hpp"

/* ############################################################################################## */

static void awardCeremony(Bureaucrat &bureaucrat);

/* ############################################################################################## */


int main(void) {
	std::cout << "Welcome in " << ColorFormat::formatString("Bureaucrat™", "green", "blink", "bold") << " !\n" << std::endl;
	std::srand(time(0));

	while (true) {
		try {
			Input formInputs[3][3];
			Form  formLists[3];
			for (size_t i = 0 ; i < 3 ; i++) {
				std::cout << "Let's create three forms, write the " << i << ":" << std::endl;
				try {
					formInputs[i][0] = Input("What name should I give it (leave blank for a random form)?");
					if (not formInputs[i][0].stringFormat().empty()) {
						try { formInputs[i][1] = Input("Grade required for signature:"); }
						catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
						try { formInputs[i][2] = Input("Grade required for application:"); }
						catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
					}
				}
				catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
				unsigned int signatureGrade	  = rand() % 150 + 1;
				unsigned int applicationGrade = rand() % signatureGrade + 1;
				try {
					signatureGrade	 = formInputs[i][1].unsignedIntegerFormat();
					applicationGrade = formInputs[i][1].unsignedIntegerFormat();
				}
				catch (...) {
					std::cout << "In the absence of a valid grade, the form will " << ColorFormat::rainbow("randomly", "blink") << " draw one!" << std::endl;
				}
			}

			Input		 bureaucratName("What " + ColorFormat::formatString("name", "cyan") + " to give the bureaucrat?");
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
		} catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
}

static void awardCeremony(Bureaucrat &bureaucrat) {
	std::cout << bureaucrat << std::endl;
	if (std::rand() % 2) {
		std::cout << "Sorry " << ColorFormat::formatString(bureaucrat.getName(), "blue", "italic") << ", but you " << ColorFormat::formatString("cheated", "red", "underline") << '!' << std::endl;
		try { bureaucrat.decrementGrade(); }
		catch (const Bureaucrat::GradeTooLowException &e) {
			std::cerr << ColorFormat::formatString(bureaucrat.getName(), "red", "strikethrough") << ColorFormat::formatString(", YOUR INTELLECTUAL INFERIORITY AMAZES US ALL, YOU ARE EXCLUDED!", "red", "bold") << std::endl;
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
}
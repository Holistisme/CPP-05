#include "Bureaucrat.hpp"

/* ############################################################################################## */

#include "ColorFormatLib/ColorFormat.hpp"
#include "InputLib/Input.hpp"

/* ############################################################################################## */

static void awardCeremony(Bureaucrat &bureaucrat);

/* ############################################################################################## */

/**
 * @brief Entry point of the Bureaucrat simulation program.
 * 
 * This function creates and manages Bureaucrat objects, allowing the user to input a name and grade.
 * If the user does not provide a valid grade, one will be randomly assigned.
 * The Bureaucrat will then participate in an award ceremony, where they may be promoted or demoted.
 * 
 * The program runs in an infinite loop until the user manually exits (e.g., with Ctrl+D).
 * 
 * @return 0 on successful execution, 1 if an exception is encountered.
 */
int main(void) {
	std::cout << "Welcome in " << ColorFormat::formatString("Bureaucrat™", "green", "blink", "bold") << " !\n" << std::endl;
	std::srand(time(0));

	while (true) {
		try {
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

/**
 * @brief Simulates an award ceremony for a Bureaucrat.
 * 
 * During the ceremony, the Bureaucrat may either be promoted or demoted based on a random decision.
 * - If demoted, their grade decreases (worsens).
 * - If promoted, their grade increases (improves).
 * - If they reach the highest or lowest possible grade, a special message is displayed.
 * 
 * @param bureaucrat The Bureaucrat object to participate in the ceremony.
 */
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
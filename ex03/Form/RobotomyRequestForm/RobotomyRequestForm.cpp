#include "./RobotomyRequestForm.hpp"

/* ############################################################################################## */

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)			: AForm("RobotomyRequestForm", 72, 45), _target(not target.empty() ? target : setRandomName()) {}
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &source) : AForm(source), _target(source._target)													   {}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &source) {
	if (this != &source) {
		AForm::operator=(source);
		_target = source._target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm(void) {}

/* ############################################################################################## */

const std::string RobotomyRequestForm::setRandomName(void) const {
	static const std::string randomNames[] = {
	"Elon Musk",				   "The CEO of Bureaucracy Inc.",		"A rebellious AI",
    "The President",			   "A mad scientist",					"A rogue time traveler",
    "A talking cat",			   "A paranoid android",				"A malfunctioning chatbot",
    "The last human alive",		   "A cyborg accountant",				"A bureaucratic overlord",
    "An alien diplomat",		   "A corrupt senator",					"A lazy intern",
    "The world's richest man",	   "A ninja hacker",					"A disgruntled employee",
    "A sentient quantum computer", "A robot uprising leader",			"A cyborg warlord",
    "A talking parrot",			   "A rogue janitor",					"A bioengineered monster",
    "A crazy conspiracy theorist", "A malfunctioning self-driving car", "A time-traveling dictator",
    "A heavily modified cyborg",   "A robot clown",						"A neural network gone rogue",
    "An AI-powered bureaucrat",	   "The mayor of CyberCity",			"A pizza delivery drone",
    "A mad king",				   "A rebel leader",					"A billionaire with too much power",
    "An alien king",			   "A sorcerer turned cyborg",			"A space pirate captain",
    "A rogue clone",			   "A human-turned-AI hybrid",			"A rogue battle droid"
	};

	return randomNames[std::rand() % 42];
}

/* ############################################################################################## */

void RobotomyRequestForm::execute(const Bureaucrat &executor) const {
	checkExecution(executor);

	std::cout << ColorFormat::formatString("*BZZZZZZZZT* *DRRRRRRRR*", "bold") << std::endl;

	std::rand() % 2 ? std::cout << "🤖 "				 << ColorFormat::formatString(_target, "green", "italic") << " has been successfully robotomized! 🤖" << std::endl
					: std::cout << "🤦 The robotomy of " << ColorFormat::formatString(_target, "red", 	"italic") << " has failed! 🤦"						  << std::endl;
}

/* ############################################################################################## */

AForm *RobotomyRequestForm::create(const std::string &target) {
	return new RobotomyRequestForm(target);
}
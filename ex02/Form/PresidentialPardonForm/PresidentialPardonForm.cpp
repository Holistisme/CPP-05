#include "./PresidentialPardonForm.hpp"

/* ############################################################################################## */

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)			 : AForm("PresidentialPardonForm", 25, 5), _target(not target.empty() ? target : setRandomName()) {}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &source) : AForm(source), _target(source._target)														  {}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &source) {
	if (this != &source) {
		AForm::operator=(source);
		_target = source._target;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {}

/* ############################################################################################## */

const std::string PresidentialPardonForm::setRandomName(void) const {
	static const std::string randomNames[] = {
	"A notorious hacker",					"A tax-evading billionaire",		 "A cybercriminal mastermind",
	"A time-traveling outlaw",				"A wanted space smuggler",			 "The world's worst driver",
    "A wizard who cheated in magic exams",	"An AI convicted of fraud",			 "A professional scam artist",
    "A retired mafia boss",					"A bank robber who stole $1",		 "A vampire caught in daylight",
    "A failed supervillain",				"A pirate king",					 "A corrupt politician",
    "A disgraced reality TV star",			"A professional cheater",			 "A rogue scientist",
    "A secret society leader",				"A con artist monk",				 "A disgraced stockbroker",
    "An immortal trickster",				"A scientist who cloned dinosaurs",  "A dark web kingpin",
    "A ghost who refuses to leave court",	"A mythical outlaw",				 "An alien caught smuggling space cheese",
    "A corporate spy",						"A black market burrito dealer",	 "A magician who made money disappear",
    "A hedge fund scammer",					"A cult leader",					 "A rogue AI selling fake news",
    "An arms dealer who sold rubber ducks", "A failed fortune teller",			 "A TV evangelist with fake miracles",
    "A disgraced superhero",				"A wizard who turned the moon pink", "A time-traveling tax collector",
    "A CEO who stole all the staplers",		"A cat burglar (literally, a cat)",	 "A hypnotist who convinced people he was innocent"
	};

	return randomNames[std::rand() % 42];
}

/* ############################################################################################## */

void PresidentialPardonForm::execute(const Bureaucrat &executor) const {
	checkExecution(executor);

	std::cout << "📜 " << ColorFormat::formatString(_target, "italic", "blue") << " has been granted a presidential pardon by "
		+ ColorFormat::formatString("Zaphod Beeblebrox", "bold", "red") + ". 📜" << std::endl;
}
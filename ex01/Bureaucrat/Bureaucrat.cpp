#include "Bureaucrat.hpp"
#include "../ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

Bureaucrat::Bureaucrat(void) :	_name(setRandomName()),
								_grade(std::rand() % 150 + 1) {}

const std::string &Bureaucrat::setRandomName(void) {
	static const std::string randomNames[] = {
		"Napoleon Bonaparte",	"Julius Caesar",		"Winston Churchill",	"Cleopatra",
		"Alexander the Great",	"Leonardo da Vinci",	"Marie Curie",			"Genghis Khan",
		"George Washington",	"Charlemagne",			"Otto von Bismarck",	"Nikola Tesla",
		"Isaac Newton",			"Albert Einstein",		"Theodore Roosevelt",	"Joan of Arc",
		"Louis XIV",			"Karl Marx",			"Voltaire",				"Plato", 
		"Socrates",				"Aristotle",			"Galileo Galilei",		"Sigmund Freud",
		"Confucius",			"Sun Tzu",				"Shakespeare",			"Robespierre",
		"Tsar Nicholas II",		"Charles Darwin",		"Thomas Edison",		"Queen Victoria",
		"Nelson Mandela",		"Simon Bolivar",		"Friedrich Nietzsche",	"Jean-Jacques Rousseau",
		"Che Guevara",			"Martin Luther",		"Hammurabi",			"Empress Dowager Cixi",
		"Francis Bacon",		"Jean-Baptiste Colbert"
	};

	return randomNames[std::rand() % 42];
}

/* ############################################################################################## */

Bureaucrat::Bureaucrat(const std::string &name, const unsigned int grade) : _name(name) {
	gradeValidity(grade);
	_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &source) : _name(source._name), _grade(source._grade) {}

/* ############################################################################################## */

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &source) {
	if (this != &source)
		_grade = source._grade;
	return *this;
}


/* ############################################################################################## */

Bureaucrat::~Bureaucrat(void) {}

/* ############################################################################################## */

const std::string &Bureaucrat::getName(void) const	{ return _name;	 }
unsigned int	  Bureaucrat::getGrade(void) const	{ return _grade; };

/* ############################################################################################## */

void Bureaucrat::incrementGrade(void) {
	gradeValidity(_grade - 1);
	--_grade;
}

void Bureaucrat::decrementGrade(void) {
	gradeValidity(_grade + 1);
	++_grade;
}

/* ############################################################################################## */

void Bureaucrat::gradeValidity(const unsigned int request) {
	if (request < 1)
		throw GradeTooHighException();
	if (request > 150)
		throw GradeTooLowException();
}

/* ############################################################################################## */

const char *Bureaucrat::GradeTooHighException::what() const throw() { return "Grade too high!"; };
const char *Bureaucrat::GradeTooLowException::what()  const throw() { return "Grade too low!";	};

/* ############################################################################################## */

std::ostream &operator<<(std::ostream &stream, const Bureaucrat &bureaucrat) {
    stream << ColorFormat::formatString(bureaucrat.getName(), "blue", "italic") << ", bureaucrat grade " << ColorFormat::formatGradientUnsignedInteger(bureaucrat.getGrade(), 150, 1) << '.';
    return stream;
}

void Bureaucrat::signForm(Form &form) {
	try {
		form.beSigned(*this);
		std::cout << ColorFormat::formatString(getName(), "blue", "italic") << " signed " << ColorFormat::formatString(getName(), "magenta") << '.' << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << ColorFormat::formatString(getName(), "blue", "italic") << " couldn’t sign " << ColorFormat::formatString(getName(), "magenta")
			<< " because " << ColorFormat::formatString(e.what(), "red") << '.' << std::endl;
	}
}
#include "Form.hpp"
#include "../ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */
/* ############################################################################################## */

Form::Form(void) : _name(setRandomName()),
				   _signed(false),
				   _requiredGrade(std::rand() % 150 + 1),
				   _executableGrade(std::rand() % _requiredGrade + 1) {}

const std::string &Form::setRandomName(void) const {
	static const std::string randomNames[42] = {
		"Request for Bureaucratic Evaluation",				   "Permit for Paperwork Processing",
        "Authorization for Additional Forms",				   "Certificate of Administrative Compliance",
        "Petition for More Bureaucracy",					   "Application for Office Coffee Supply",
        "Request for Executive Approval",					   "Requisition of Paper Clips and Staples",
        "Proposal for Useless Meetings",					   "License for Procrastination",
        "Declaration of Red Tape Completion",				   "Validation of Official Signature",
        "Authorization for Chair Adjustment",				   "Form for Submitting Forms",
        "Permit to Request a New Permit",					   "Certificate of Completed Paperwork",
        "Proposal for a Proposal",							   "Authorization for Three-Hour Lunch Break",
        "Registration for the Bureaucratic Olympics",		   "Request for More Request Forms",
        "Approval for Office Gossip Circulation",			   "Application to Take a Break",
        "Declaration of Stapler Ownership",					   "Validation of Signature Authenticity",
        "Authorization to Breathe in the Office",			   "Request for Additional Paperwork Delays",
        "Permit to Use the Printer",						   "Application for Formal Complaint Filing",
        "Submission of a Pointless Memo",					   "Declaration of Pen Shortage",
        "Request for Desk Space Expansion",					   "Formal Notification of Lunch Schedule",
        "Petition for Extended Deadline on Previous Petition", "Authorization to Submit an Authorization Request",
        "Certificate of Official Desk Plant Approval",		   "Proposal for Extended Coffee Breaks",
        "Request for Budget Increase on Office Snacks",		   "Requisition for an Extra Paperweight",
        "Permit for Additional Bureaucratic Nonsense",		   "Request to Change the Default Font of Official Documents",
        "Notification of Insufficient Post-it Notes",		   "Declaration of Desk Cleanliness Compliance"
	};

	return randomNames[std::rand() % 42];
}

/* ############################################################################################## */

Form::Form(const std::string &name, const unsigned int requiredGrade, const unsigned int executableGrade) : _name(not name.empty() ? name : setRandomName()), _signed(false),
																											_requiredGrade(requiredGrade), _executableGrade(executableGrade) {
	gradeValidity(requiredGrade);
	gradeValidity(executableGrade);
}

Form::Form(const Form &source) : _name(source._name),  _signed(source._signed), _requiredGrade(source._requiredGrade), _executableGrade(source._executableGrade) {}

Form &Form::operator=(const Form &source) {
	if (this != &source)
		_signed = source._signed;
	return *this;
}

Form::~Form(void) {}

/* ############################################################################################## */

const std::string &Form::getName(void)			 const { return _name;			  }
bool	 		  Form::isSigned(void)			 const { return _signed;		  }
unsigned int	  Form::getRequiredGrade(void)   const { return _requiredGrade;	  }
unsigned int	  Form::getExecutableGrade(void) const { return _executableGrade; }

/* ############################################################################################## */

void Form::gradeValidity(const unsigned int request) {
	if (request < 1)
		throw GradeTooHighException();
	if (request > 150)
		throw GradeTooLowException();
}

/* ############################################################################################## */

const char *Form::GradeTooHighException::what() const throw() { return "Grade too high";		  };
const char *Form::GradeTooLowException::what()  const throw() { return "Grade too low";		  };
const char *Form::IsAlreadySigned::what()		const throw() { return "Form is already signed"; };

/* ############################################################################################## */

std::ostream &operator<<(std::ostream &stream, const Form &form) {
	std::string state = not form.isSigned() ? ColorFormat::formatString(" not already signed", "green") : ColorFormat::formatString(" is already signed.", "red");

	stream << ColorFormat::formatString(form.getName(), "magenta", "italic") << state
		<< ". The grade required for signature is " << ColorFormat::formatGradientUnsignedInteger(form.getRequiredGrade(), 150, 1)
		<< ", and the grade required for its execution is " << ColorFormat::formatGradientUnsignedInteger(form.getExecutableGrade(), 150, 1) << '.';
    return stream;
}

void Form::beSigned(const Bureaucrat &bureaucrat) {
	if (!_signed) {
		if (bureaucrat.getGrade() > _requiredGrade)
			throw GradeTooLowException();
		_signed = true;
	}
	else
		throw IsAlreadySigned();
}
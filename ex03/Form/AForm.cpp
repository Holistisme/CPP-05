#include "AForm.hpp"
#include "../ColorFormatLib/ColorFormat.hpp"

/* ############################################################################################## */

AForm::AForm(void) : _name(setRandomName()),
				   _signed(false),
				   _requiredGrade(std::rand() % 150 + 1),
				   _executableGrade(std::rand() % _requiredGrade + 1) {}

const std::string &AForm::setRandomName(void) const {
	static const std::string randomNames[42] = {
		"Request for Bureaucratic Evaluation",				   "Permit for Paperwork Processing",
        "Authorization for Additional AForms",				   "Certificate of Administrative Compliance",
        "Petition for More Bureaucracy",					   "Application for Office Coffee Supply",
        "Request for Executive Approval",					   "Requisition of Paper Clips and Staples",
        "Proposal for Useless Meetings",					   "License for Procrastination",
        "Declaration of Red Tape Completion",				   "Validation of Official Signature",
        "Authorization for Chair Adjustment",				   "AForm for Submitting AForms",
        "Permit to Request a New Permit",					   "Certificate of Completed Paperwork",
        "Proposal for a Proposal",							   "Authorization for Three-Hour Lunch Break",
        "Registration for the Bureaucratic Olympics",		   "Request for More Request AForms",
        "Approval for Office Gossip Circulation",			   "Application to Take a Break",
        "Declaration of Stapler Ownership",					   "Validation of Signature Authenticity",
        "Authorization to Breathe in the Office",			   "Request for Additional Paperwork Delays",
        "Permit to Use the Printer",						   "Application for AFormal Complaint Filing",
        "Submission of a Pointless Memo",					   "Declaration of Pen Shortage",
        "Request for Desk Space Expansion",					   "AFormal Notification of Lunch Schedule",
        "Petition for Extended Deadline on Previous Petition", "Authorization to Submit an Authorization Request",
        "Certificate of Official Desk Plant Approval",		   "Proposal for Extended Coffee Breaks",
        "Request for Budget Increase on Office Snacks",		   "Requisition for an Extra Paperweight",
        "Permit for Additional Bureaucratic Nonsense",		   "Request to Change the Default Font of Official Documents",
        "Notification of Insufficient Post-it Notes",		   "Declaration of Desk Cleanliness Compliance"
	};

	return randomNames[std::rand() % 42];
}

/* ############################################################################################## */

AForm::AForm(const std::string &name, const unsigned int requiredGrade, const unsigned int executableGrade) : _name(not name.empty() ? name : setRandomName()), _signed(false),
																											_requiredGrade(requiredGrade), _executableGrade(executableGrade) {
	gradeValidity(requiredGrade);
	gradeValidity(executableGrade);
}

AForm::AForm(const AForm &source) : _name(source._name),  _signed(source._signed), _requiredGrade(source._requiredGrade), _executableGrade(source._executableGrade) {}

AForm &AForm::operator=(const AForm &source) {
	if (this != &source)
		_signed = source._signed;
	return *this;
}

AForm::~AForm(void) {}

/* ############################################################################################## */

const std::string &AForm::getName(void)			 const { return _name;			   }
bool	 		  AForm::isSigned(void)			 const { return _signed;		   }
unsigned int	  AForm::getRequiredGrade(void)   const { return _requiredGrade;   }
unsigned int	  AForm::getExecutableGrade(void) const { return _executableGrade; }

/* ############################################################################################## */

void AForm::gradeValidity(const unsigned int request) {
	if (request < 1)
		throw GradeTooHighException();
	if (request > 150)
		throw GradeTooLowException();
}

/* ############################################################################################## */

const char *AForm::GradeTooHighException::what() const throw() { return "Grade too high";		  };
const char *AForm::GradeTooLowException::what()  const throw() { return "Grade too low";		  };
const char *AForm::IsAlreadySigned::what()		 const throw() { return "Form is already signed"; };
const char *AForm::IsNotSigned::what()			 const throw() { return "Form is not signed";	  };

/* ############################################################################################## */

std::ostream &operator<<(std::ostream &stream, const AForm &AForm) {
	std::string state = not AForm.isSigned() ? ColorFormat::formatString(" not already signed", "red") : ColorFormat::formatString(" already signed", "green");

	stream << ColorFormat::formatString(AForm.getName(), "magenta", "italic") << state
		<< ". The grade required for signature is " << ColorFormat::formatGradientUnsignedInteger(AForm.getRequiredGrade(), 150, 1)
		<< ", and the grade required for its execution is " << ColorFormat::formatGradientUnsignedInteger(AForm.getExecutableGrade(), 150, 1) << '.';
    return stream;
}

void AForm::beSigned(const Bureaucrat &bureaucrat) {
	if (!_signed) {
		if (bureaucrat.getGrade() > _requiredGrade)
			throw GradeTooLowException();
		_signed = true;
	}
	else
		throw IsAlreadySigned();
}

void AForm::checkExecution(const Bureaucrat &executor) const {
	if (not isSigned())
		throw AForm::IsNotSigned();
	if (executor.getGrade() > getExecutableGrade())
		throw AForm::GradeTooLowException();
}
NAME		= InternJob

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -Wshadow -std=c++98

FORM		= ./Form

SOURCE		= main.cpp													\
			Bureaucrat/Bureaucrat.cpp									\
			ColorFormatLib/ColorFormat.cpp								\
			Intern/Intern.cpp											\
			InputLib/Input.cpp											\
			$(FORM)/AForm.cpp											\
			$(FORM)/PresidentialPardonForm/PresidentialPardonForm.cpp	\
			$(FORM)/RobotomyRequestForm/RobotomyRequestForm.cpp			\
			$(FORM)/ShrubberyCreationForm/ShrubberyCreationForm.cpp		\

OBJECTS		= $(SOURCE:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
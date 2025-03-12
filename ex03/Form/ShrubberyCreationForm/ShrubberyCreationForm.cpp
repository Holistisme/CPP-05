#include "./ShrubberyCreationForm.hpp"

/* ############################################################################################## */

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)			  : AForm("ShrubberyCreationForm", 145, 137), _target(not target.empty() ? target : setRandomName()) {}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &source) : AForm(source), _target(source._target)															 {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &source) {
	if (this != &source) {
		AForm::operator=(source);
		_target = source._target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {}

/* ############################################################################################## */

const std::string ShrubberyCreationForm::setRandomName(void) const {
	static const std::string randomNames[] = {
	"The_Amazon_Rainforest",		"Central_Park",					  "The_Sahara_Desert",
	"A_barren_office_cubicle",		"A_forgotten_backyard",			  "The_Moon's_surface",
	"The_Eiffel_Tower_rooftop",		"A_secret_military_base",		  "A_lonely_sidewalk",
	"A_dystopian_wasteland",		"A_billionaire's_private_island", "A_medieval_castle_garden",
	"A_spaceship_oxygen_garden",	"A_neglected_bonsai_tree",		  "A_polluted_city_block",
	"A_lost_jungle_temple",			"A_UFO_crash_site",				  "A_sci-fi_biodome",
	"A_vampire’s_castle_courtyard", "An_abandoned_nuclear_plant",	  "A_floating_sky_city",
	"A_pirate_ship_deck",			"An_underwater_cave",			  "A_billionaire’s_balcony",
	"The_peak_of_Mount_Everest",	"A_robot_factory_rooftop",		  "A_forgotten_space_station",
	"A_hidden_elf_sanctuary",		"A_crashed_alien_mothership",	  "A_government_bunker",
	"An_overgrown_metro_station",	"A_zombie_apocalypse_refuge",	  "An_abandoned_amusement_park",
	"A_futuristic_megacity",		"A_cyberpunk_rooftop",			  "An_AI-controlled_greenhouse",
	"A_massive_underground_cavern", "A_sci-fi_Mars_colony",			  "A_legendary_lost_island",
	"A_floating_iceberg_garden",	"A_wizard’s_tower",				  "A_dragon’s_cave"
	};

	return randomNames[std::rand() % 42];
}

/* ############################################################################################## */

void ShrubberyCreationForm::execute(const Bureaucrat &executor) const {
	checkExecution(executor);

	std::ofstream targetFile((_target + "_shrubbery").c_str());
	if (!targetFile)
		throw std::runtime_error("Unable to open file " + _target + "_shrubbery");

	std::string trees[10] = {
		"               ,@@@@@@@,\n"
		"       ,,,.   ,@@@@@@/@@,  .oo8888o.\n"
		"   ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o\n"
		"  ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n"
		"  %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n"
		"  %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'\n"
		"   `&%\\ ` /%&'    |.|        \\ '|8'\n"
		"       |o|        | |         | |\n"
		"       |.|        | |         | |\n"
		"    \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/\n"
	};

	for (size_t i = 0 ; i < 10 ; i++)
		targetFile << trees[i];
	targetFile.close();
	if (targetFile.fail())
		throw std::runtime_error("Error while closing the file " + _target + "_shrubbery");

	std::cout << "🌳 " << ColorFormat::formatString(_target + "_shrubbery", "green", "italic") << " has been created successfully! 🌳" << std::endl;
}

/* ############################################################################################## */

AForm *ShrubberyCreationForm::create(const std::string &target) {
	return new ShrubberyCreationForm(target);
}
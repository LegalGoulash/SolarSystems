#ifndef MENU_H
#define MENU_H
#include"Galaxy.h"
#include"SolarSystemLoader.h"
#include <memory>
#include<filesystem>
class Menu {
private:
	static void handleGalaxyMenu(Galaxy& galaxy);
	static void handleSunMenu(Sun& sun);
	static void handlePlanetMenu(Planet& planet);
	static void displayMainMenu();
	static void displayGalaxy(const Galaxy& galaxy);

	//ezeket levedem mert nem peladnyosithato
	Menu() = delete;
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
public:
	static void runMainMenu();

};

#endif // !1



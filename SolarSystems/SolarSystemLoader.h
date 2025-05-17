#ifndef SOLAR_SYSTEM_LOADER_H
#define SOLAR_SYSTEM_LOADER_H

#include "Galaxy.h"
#include <memory>
#include <fstream>

class SolarSystemLoader
{
private:
	//ezek segedek nem kell hogy hozzaferjen mas
	static void loadSuns(std::ifstream& file, Galaxy& galaxy);
	static void loadPlanets(std::ifstream& file, Galaxy& galaxy);
	static void loadMoons(std::ifstream& file, Galaxy& galaxy);
	SolarSystemLoader() = delete;
	SolarSystemLoader(const SolarSystemLoader&) = delete;
	SolarSystemLoader& operator=(const SolarSystemLoader&) = delete;
public:
	// galaxis betoltese
	static std::unique_ptr<Galaxy> loadGalaxy(const std::string& sunFile, const std::string& planetFile, const std::string& moonFile);

	//galaxis mentese
	static bool SaveGalaxy(const Galaxy& galaxy, const std::string& sunFile, const std::string& planetFile, const std::string& moonFile);


};


#endif // !SOLAR_SYSTEM_LOADER_H


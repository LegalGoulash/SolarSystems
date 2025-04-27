#include "SolarSystemLoader.h"
#include "Planet.h"
#include "Moon.h"
#include <sstream>
#include <stdexcept>



void SolarSystemLoader::loadSuns(std::ifstream& file, Galaxy& galaxy)
{
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        double mass, radius, temp;

        if (iss >> std::quoted(name) >> mass >> radius >> temp) {
            galaxy.addSun(name, mass, radius, temp);
        }
    }
}

void SolarSystemLoader::loadPlanets(std::ifstream& file, Galaxy& galaxy)
{
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string sunName, planetName;
        double mass, distance, radius;

        if (iss >> std::quoted(sunName) >> std::quoted(planetName) >> mass >> distance >> radius) {
            Sun* sun = galaxy.findSun(sunName);
            if (sun) {
                sun->addPlanet(planetName, mass, distance, radius);
            }
        }
    }
}

void SolarSystemLoader::loadMoons(std::ifstream& file, Galaxy& galaxy)
{
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string sunName, planetName, moonName;
        double mass, distance, radius;

        if (iss >> std::quoted(sunName) >> std::quoted(planetName) >> std::quoted(moonName) >> mass >> distance >> radius) {
            Sun* sun = galaxy.findSun(sunName);
            if (sun) {
                Planet* planet = sun->findPlanet(planetName);
                if (planet) {
                    planet->addMoon(moonName, mass, distance, radius);
                }
            }
        }
    }
}

std::unique_ptr<Galaxy> SolarSystemLoader::loadGalaxy(const std::string& sunFile, const std::string& planetFile, const std::string& moonFile)
{
    auto galaxy = std::make_unique<Galaxy>("Betoltott Galaxis");

    // NAPOK 
    std::ifstream sunStream(sunFile);
    if (!sunStream) {
        throw std::runtime_error("Napok fajl nem talalhato: " + sunFile +
            "\nGyozodj meg rola, hogy a fajl a 'data' mappaban van!");
    }
    loadSuns(sunStream, *galaxy);

    // BOLYGOK figyelmeztetunk ha nem talalhato
    std::ifstream planetStream(planetFile);
    if (!planetStream) {
        std::cerr << "Figyelmeztetes: Bolygok fajl nem talalhato: " << planetFile << "\n";
    }
    else {
        loadPlanets(planetStream, *galaxy);
    }


    // HOLDAK 
    std::ifstream moonStream(moonFile);
    if (!moonStream) {
        std::cerr << "Figyelmeztetes: Holdak fajl nem talalhato: " << moonFile << "\n";
    }
    else {
        loadMoons(moonStream, *galaxy);
    }

    return galaxy;
}


bool SolarSystemLoader::SaveGalaxy(const Galaxy& galaxy, const std::string& sunFile, const std::string& planetFile, const std::string& moonFile)
{
    // Napok 
    std::ofstream sunStream(sunFile);
    if (!sunStream.is_open()) return false;

    try {
        for (const auto& sun : galaxy.getSuns()) {
            if (!sun) continue;
            sunStream << std::quoted(sun->getName()) << " "
                << sun->getMass() << " "
                << sun->getRadius() << " "
                << sun->getTemperature() << "\n";
        }
    }
    catch (...) {
        return false;
    }

    // Bolygók 
    std::ofstream planetStream(planetFile);
    if (!planetStream.is_open()) return false;

    try {
        for (const auto& sun : galaxy.getSuns()) {
            if (!sun) continue;
            for (const auto& planet : sun->getPlanets()) {
                if (!planet) continue;
                planetStream << std::quoted(sun->getName()) << " "
                    << std::quoted(planet->getName()) << " "
                    << planet->getMass() << " "
                    << planet->getDistance() << " "
                    << planet->getRadius() << "\n";
            }
        }
    }
    catch (...) {
        return false;
    }

    // Holdak 
    std::ofstream moonStream(moonFile);
    if (!moonStream.is_open()) return false;

    try {
        for (const auto& sun : galaxy.getSuns()) {
            if (!sun) continue;
            for (const auto& planet : sun->getPlanets()) {
                if (!planet) continue;
                for (const auto& moon : planet->getMoons()) {
                    if (!moon) continue;
                    moonStream << std::quoted(sun->getName()) << " "
                        << std::quoted(planet->getName()) << " "
                        << std::quoted(moon->getName()) << " "
                        << moon->getMass() << " "
                        << moon->getDistance() << " "
                        << moon->getRadius() << "\n";
                }
            }
        }
    }
    catch (...) {
        return false;
    }

    return true;
}
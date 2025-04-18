#include "Sun.h"
#include"Planet.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>    
#include <stdexcept>   

//seged fvk vagy inkabb kiszervezes

bool Sun::caseInsensitiveCompare(const std::string& a, const std::string& b) {
	return a.size() == b.size() &&
		std::equal(a.begin(), a.end(), b.begin(),
			[](char x, char y) { return std::tolower(x) == std::tolower(y); });
}
bool Sun::isValidNameChar(char c) {
	return std::isalnum(static_cast<unsigned char>(c)) ||
		c == ' ' || c == '-' || c == '_' || c == '.';
}

void Sun::validatePlanetName(const std::string& name) const {
	if (name.empty()) throw std::invalid_argument("Nev nem lehet ures");

	for (char c : name) {
		if (!isValidNameChar(c)) {
			throw std::invalid_argument("Ervenytelen karakter: " + std::string(1, c));
		}
	}

	if (std::any_of(planets.begin(), planets.end(),
		[&name](const auto& planet) {
			return caseInsensitiveCompare(planet->getName(), name);
		})) {
		throw std::invalid_argument("Mar letezo bolygo: " + name);
	}
}

void Sun::validatePlanetParameters(double mass, double distance, double radius) const {
	if (mass <= Planet::MIN_MASS) throw std::invalid_argument("Tomeg tul kicsi");
	if (distance < 0) throw std::invalid_argument("Tavolsag nem lehet negativ");
	if (radius <= Planet::MIN_RADIUS) throw std::invalid_argument("Sugar tul kicsi");
}
//konstruktor
Sun::Sun(const std::string& name, double mass, double radius, double temperature)
	: name(name), mass(mass), radius(radius), temperature(temperature) {

	// nev check
	if (name.empty()) {
		throw std::invalid_argument("A Nap neve nem lehet ures!");
	}

	if (!std::all_of(name.begin(), name.end(), isValidNameChar)) {
		throw std::invalid_argument("A nev csak betuket, szamokat, szokozt és speciális karaktereket (-_.) tartalmazhat!");
	}

	//parameterek 

	if (mass < MIN_MASS) {
		throw std::invalid_argument("A tomeg nem lehet kisebb mint " + std::to_string(MIN_MASS) + " kg");
	}

	if (radius < MIN_RADIUS) {
		throw std::invalid_argument("A sugar nem lehet kisebb mint " + std::to_string(MIN_RADIUS) + " km");
	}

	if (temperature < MIN_TEMP) {
		throw std::invalid_argument("A homerseklet nem lehet alacsonyabb mint " + std::to_string(MIN_TEMP) + " K");
	}
}

//getterek
const std::string& Sun::getName() const
{
	return name;
}

double Sun::getMass() const
{
	return mass;
}

double Sun::getRadius() const
{
	return radius;
}

double Sun::getTemperature() const
{
	return temperature;
}

const std::vector<std::unique_ptr<Planet>>& Sun::getPlanets() const
{
	return planets;
}
//setterek 

void Sun::setName(const std::string& newName)
{
	if (newName.empty())
	{
		throw std::invalid_argument("Nem lehet ures a nev");
	}
	for (char c : newName) {
		if (!isValidNameChar(c)) {
			throw std::invalid_argument("Ervenytelen karakter: " + std::string(1, c));
		}
	}
	name = newName;
}
void Sun::setMass(double newMass)
{
	if (newMass < MIN_MASS) throw std::invalid_argument("Tul kicsi a tomeg! Minimum: " + std::to_string(MIN_MASS) + " kg");

	mass = newMass;
}

void Sun::setRadius(double newRadius)
{
	if (newRadius < MIN_RADIUS) {
		throw std::invalid_argument("Nem lehet kissebb a sugara a bolygonak mint: "+std::to_string(MIN_RADIUS) +" km !");
	}
	radius = newRadius;// sugar lekezelese
}

void Sun::setTemperature(double newTemp)
{
	if (newTemp < MIN_TEMP) {
		throw std::invalid_argument("A homerseklet nem lehet alacsonyabb mint: " + std::to_string(MIN_TEMP) + " K");
	}
	temperature = newTemp;
}
// bojgoval mokolas
void Sun::addPlanet(std::unique_ptr<Planet> planet) {
	if (!planet) throw std::invalid_argument("Planet nem lehet NULL ptr!");

	// nev
	validatePlanetName(planet->getName());
	validatePlanetParameters(planet->getMass(), planet->getDistance(), planet->getRadius());

	planets.push_back(std::move(planet));
}

void Sun::addPlanet(const std::string& name, double mass, double distance, double radius)
{
	validatePlanetName(name);
	validatePlanetParameters(mass, radius, distance);

	planets.push_back(std::make_unique<Planet>(name, mass, distance, radius));
}



bool Sun::removePlanet(const std::string& planetName) {
	auto it = std::find_if(planets.begin(), planets.end(),
		[&planetName](const auto& planet) {
			return caseInsensitiveCompare(planet->getName(), planetName);
		});

	if (it != planets.end()) {
		planets.erase(it);
		return true;
	}
	return false;
}

Planet* Sun::findPlanet(const std::string& planetName) const {
	auto it = std::find_if(planets.begin(), planets.end(),
		[&planetName](const std::unique_ptr<Planet>& planet) {
			return caseInsensitiveCompare(planet->getName(), planetName);
		});
	return (it != planets.end()) ? it->get() : nullptr;
}

bool Sun::hasPlanet(const std::string& name) const
{
	return findPlanet(name) != nullptr;
}

size_t Sun::planetCount() const
{
	return planets.size();
}

void Sun::printData() const
{
	std::cout << std::left
		<< std::setw(15) << "Sun Name: " << name << "\n"
		<< std::setw(15) << "Mass: " << mass << "\n"
		<< std::setw(15) << "Radius: " << radius<< "\n"
		<< std::setw(15) << "Temperature: " << temperature << "\n";
}

void Sun::printPlanets() const
{
	std::cout << "Planets of " << name << "\n";
	for (const auto& planet : planets) {
		planet->printData();
		std::cout << "--------------------\n";
	}
}

bool Sun::operator==(const Sun& other) const
{
	return name == other.name &&
		mass == other.mass &&
		radius == other.radius &&
		temperature == other.temperature;
}

bool Sun::operator!=(const Sun& other) const
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Sun& sun)
{
	os << "Sun: " << sun.name << " (Mass: " << sun.mass << " kg, Radius: "
		<< sun.radius << " km, Temperature: " << sun.temperature << " Kelvin)";
	return os;
}


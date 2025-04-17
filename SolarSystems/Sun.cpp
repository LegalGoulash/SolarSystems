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

//helper vagy inkabb kiszervezes
static bool caseInsensitiveCompare(const std::string& a, const std::string& b) {
	return a.size() == b.size() &&
		std::equal(a.begin(), a.end(), b.begin(),
			[](char x, char y) { return std::tolower(x) == std::tolower(y); });
}
static bool isValidSunNameChar(char c) {
	return std::isalnum(static_cast<unsigned char>(c)) ||
		c == ' ' || c == '-' || c == '_' || c == '.';
}

//konstruktor
Sun::Sun(const std::string& name, double mass, double radius, double temperature)
	: name(name), mass(mass), radius(radius), temperature(temperature) {

	// nev check
	if (name.empty()) {
		throw std::invalid_argument("A Nap neve nem lehet ures!");
	}

	if (!std::all_of(name.begin(), name.end(), isValidSunNameChar)) {
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
		throw std::invalid_argument("A homerseklet tavolsag nem lehet kevesebb mint:" + std::to_string(MIN_TEMP) + "K");
	}
	temperature = newTemp;
}
// bojgoval mokolas
void Sun::addPlanet(std::unique_ptr<Planet> planet) {
	if (!planet) throw std::invalid_argument("Planet nem lehet NULL ptr!");

	// nev
	if (findPlanet(planet->getName())) {
		throw std::invalid_argument("A bolygo mar letezik: " + planet->getName());
	}

	// parameterek
	if (planet->getMass() <= MIN_MASS || planet->getRadius() <= MIN_RADIUS) {
		throw std::invalid_argument("Invalid planet properties!");
	}

	planets.push_back(std::move(planet));
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


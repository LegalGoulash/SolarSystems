#include "Planet.h"
#include "Moon.h" // unique ptr miatt kell 
#include <algorithm>
#include <string.h>
#include<cctype>

Planet::Planet(const std::string& name, double mass, double distance, double radius)
	: name(name), mass(mass), distance(distance), radius(radius)
{
	if (name.empty()) throw std::invalid_argument("Nem lehet ures a nev!");

	// Tömeg validálása (minimum Földtömeg 27%-a)
	const double MIN_MASS = 1.612e24; // kg
	if (mass < MIN_MASS) throw std::invalid_argument("Tul kicsi a tomeg! Minimum: " + std::to_string(MIN_MASS) + " kg");

	// Sugár validálása (minimum 200 km)
	const double MIN_RADIUS = 200.0; // km
	if (radius < MIN_RADIUS) throw std::invalid_argument("Tul kicsi a sugar! Minimum: " + std::to_string(MIN_RADIUS) + " km");

	// Távolság validálása (nem negatív)
	if (distance < 0) throw std::invalid_argument("A keringesi tavolsag nem lehet negativ!");
}

//getter fv.k 

const std::string& Planet::getName()const {
	return name;
}

double Planet::getMass() const {
	return mass;
}

double Planet::getRadius() const {
	return radius;
}

double Planet::getDistance() const {
	return distance;
}

const std::vector < std::unique_ptr < Moon >>& Planet::getMoons() const {
	return moons; 
}

//setter fv.k

void Planet::setName(const std::string& newName)  {
	if (newName.empty())
	{
		throw std::invalid_argument( " Nem lehet ures a nev"); //fancy
	}
	name = newName;//ures nev levedese
}

void Planet::setMass(double newMass) {
	const double MIN_MASS = 1.612e24;
	if (newMass <= MIN_MASS) {
		throw std::invalid_argument("A tomeg nem lehet kisebb mint " + std::to_string(MIN_MASS) + " kg");
	}
	mass = newMass;//tomeg lekezelese
}

void Planet::setRadius(double newRadius) {
	if (newRadius < 200) {
		throw std::invalid_argument( "Nem lehet kissebb  mint 200km sugara a bolygonak!");
	}
	radius = newRadius;// sugar lekezelese
}

void Planet::setDistance(double newDist) {
	if (newDist <= 0) {
		throw std::invalid_argument( "Nem lehet < 0 tavolsaga a holdnak!");
	}
	distance = newDist;// keringesi tav lekezelese
}

void Planet::printData() const {
	std::cout << std::left
		<< std::setw(15) << "Planet Name:" << name << "\n"
		<< std::setw(15) << "Mass:" << mass << " kg\n"
		<< std::setw(15) << "Radius:" << radius << " km\n"
		<< std::setw(15) << "Distance:" << distance << " km\n";

}// kiiras fancy modon 

void Planet::printMoons() const {
	std::cout << "Moons of " << name << ":\n";
	for (const auto& moon : moons) {
		moon->printData();
		std::cout << "----------------\n";
	}
}

//osszehasonlito es << operatorok 

bool Planet::operator==(const Planet& other) const {
	return name == other.name &&
		mass == other.mass &&
		distance == other.distance &&
		radius == other.radius;
}// osszehasonlito minden tag szamit

bool Planet::operator!=(const Planet& other) const {
	return !(*this == other); //sajatmagam pointer osszehasonlitasa a maiskkal

}

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
	os << "Planet: " << planet.name << " (Mass: " << planet.mass << " kg, Radius: "
		<< planet.radius << " km, Distance: " << planet.distance << " million km)";
	return os;
}
//nagyon bena vagyok es igy tudom megoldani xddd


// holdakkal valo mokolasok 
Moon* Planet::findMoon(const std::string& moonName) const {
	auto it = std::find_if(moons.begin(), moons.end(),
		[&moonName](const std::unique_ptr<Moon>& m) {
			const std::string& storedName = m->getName();
			return storedName.size() == moonName.size() &&
				std::equal(storedName.begin(), storedName.end(), moonName.begin(),
					[](char a, char b) { return std::tolower(a) == std::tolower(b); });
		});
	return (it != moons.end()) ? it->get() : nullptr;
}// felmasoltam a betu checkert 

void Planet::addMoon(std::unique_ptr<Moon> moon) {
	if (!moon) throw std::invalid_argument("Moon nem lehet NULL <ptr>");

	const double MIN_MASS = 1.612e24;
	const double MIN_RADIUS = 200.0;
	if (moon->getMass() <= MIN_MASS || moon->getRadius() < MIN_RADIUS) {
		throw std::invalid_argument("Invalid moon properties");
	}

	if (findMoon(moon->getName())) {
		throw std::runtime_error("Ezzel a nevvel mar letezik hold!");
	}

	moons.push_back(std::move(moon));
}

void Planet::addMoon(const std::string& name, double mass, double radius, double distance) {
	
	
	if (name.empty()) {
		throw std::invalid_argument("Nem lehet ures a hold neve!");
	}

	//nev formatum ellenorzes ezt felbovitettem hogy legyen - _ es ' '
	auto isValidChar = [](char c) {
		return std::isalnum(static_cast<unsigned char>(c)) ||
			c == ' ' || c == '-' || c == '_';
		};

	if (!std::all_of(name.begin(), name.end(), isValidChar)) {
		throw std::invalid_argument("A nev csak betuket, szamokat es szokozt tartalmazhat!");
	}

	//tobbi param ellenorzese
	const double MIN_MASS = 1.612e24; // kg
	const double MIN_RADIUS = 200.0; // km
	if (mass <= MIN_MASS) {
		throw std::invalid_argument("A tomeg legyen tobb mint: " + std::to_string(MIN_MASS));
	}
	if (radius < MIN_RADIUS) {
		throw std::invalid_argument("A sugar legyen nagyobb mint: " + std::to_string(MIN_RADIUS));
	}
	//case sensitive fixing 
	auto nameMatches = [&name](const std::unique_ptr<Moon>& m) {
		const std::string& moonName = m->getName();
		return moonName.size() == name.size() &&
			std::equal(moonName.begin(), moonName.end(), name.begin(),
				[](char a, char b) {
					return std::tolower(a) == std::tolower(b);
				});
		};

	if (std::any_of(moons.begin(), moons.end(), nameMatches)) {
		throw std::logic_error("Mar letezik hold ezzel a nevvel: " + name);
	}
	//arra is kell figyelni hogy upper vagy lower case 

	moons.push_back(std::make_unique < Moon >(name, mass, radius, distance));
	// uj hold hozza adasa a bolygohoz
}
//manualis hold hozzaadas 

bool Planet::removeMoon(const std::string& moonName) {
	auto it = std::find_if(moons.begin(), moons.end(),
		[&moonName](const auto& m) {
			const std::string& storedName = m->getName();
			return storedName.size() == moonName.size() &&
				std::equal(storedName.begin(), storedName.end(), moonName.begin(),
					[](char a, char b) { return std::tolower(a) == std::tolower(b); });
		});
	if (it != moons.end()) {
		moons.erase(it);
		return true;
	}
	return false;
}

bool Planet::hasMoon(const std::string& moonName)const {
	return findMoon(moonName) != nullptr; // ha van akkor nem nullptr '
}

size_t Planet::moonCount() const
{
	return moons.size();
}

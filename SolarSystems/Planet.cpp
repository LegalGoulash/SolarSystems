#include "Planet.h"
#include <algorithm>
Planet::Planet(const std::string& name, double mass, double distance, double radius)
	:name(name), mass(mass), distance(distance), radius(radius)
{
	if (name.empty()) { throw std::invalid_argument("Nem lehet ures a nev!"); }
	//inc hiba nev = 0
	if (mass <= 1.612e+24) { std::cerr << "Tul kicsi a tomeg: foldtomeg 27 % ertekre beallitas!\n"; this->mass = 1.612e+24; }
	else
	{
		this->mass = mass;
	}//tomeg hibakezeles olcso modon

	if (radius < 199.999) { std::cerr << "Tul kicsi a sugar, alapertekre allitas!\n"; this->radius = 200; }
	else
	{
		this->radius = radius;
	}// sugar kezelese olcso modon

	if (distance < 0) { std::cerr << "Tul kicsi a keringesi tavolsag 0km alapertekre allitas 200.000 km "; this->distance = 200000; }
	else
	{
		this->distance = distance;
	}// keringesi tavolsag hibakezelese olcso modon
}

//getter fv.k 

std::string Planet::getName()const {
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

//setter fv.k

void Planet::setName(const std::string& newName)  {
	if (newName.empty())
	{
		std::cerr << " Nem lehet ures a nev"; //codebro mondta hogy meno
		return;
	}
	name = newName;//ures nev levedese
}

void Planet::setMass(double newMass) {
	if (newMass <= 1.612e+24) {
		std::cerr << "Nem lehet < 1.612e+24 sully!";
	}
	mass = newMass;//tomeg lekezelese
}

void Planet::setRadius(double newRadius) {
	if (newRadius < 200) {
		std::cerr << "Nem lehet < 200 sugara a bolygonak!";
	}
	radius = newRadius;// sugar lekezelese
}

void Planet::setDistance(double newDist) {
	if (newDist <= 0) {
		std::cerr << "Nem lehet < 0 tavolsaga a holdnak!";
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

//osszehasonlito operatorok 

bool Planet::operator==(const Planet& other) const {
	return name == other.name &&
		mass == other.mass &&
		distance == other.distance &&
		radius == other.radius;
}// osszehasonlito minden tag szamit

bool Planet::operator!=(const Planet& other) const {
	return !(*this == other); //sajatmagam pointer osszehasonlitasa a maiskkal

}

//nagyon bena vagyok es igy tudom megoldani xddd
bool Planet::isMoonNameAvalible(const std::string& name)const {
	return std::none_of(moons.begin(), moons.end(),
		[&name](const auto& m) {return m->getName() == name; });
}

void Planet::addMoon(std::unique_ptr <Moon> moon) {
	if (!moon) throw std::invalid_argument("Moon nem lehet NULL <ptr> ");

	auto it = std::find_if(moons.begin(), moons.end(),
		[&moon](const auto& m) {return m->getName() == moon->getName(); });

	if (it != moons.end()) {
		throw std::runtime_error("Ilyen nevu hold mar letezik");
	}
}
void Planet::addMoon(const std::string& name, double mass, double radius, double distance) {
	if (!isMoonNameAvalible(name)) {
		throw std::runtime_error("Ezzel a nevvel mar letezik hold!");
	}
	moons.push_back(std::make_unique < Moon >(name, mass, radius, distance));
	// egyedi vektor letrehozas mert meno ;D
}
//manualis hold hozzaadas 

bool Planet::removeMoon(const std::string& moonName) {
	auto it = std::find_if(moons.begin(), moons.end(),
		[&moonName](const auto& m) {return m->getName() == moonName; });
	if (it != moons.end()) {
		moons.erase(it);
		return true;
	}
	return false;
}

Moon* Planet::findMoon(const std::string& moonName)const {
	auto it = std::find_if(moons.begin(), moons.end(),
		[&moonName](const auto& m) {return m->getName() == moonName; });

	return(it != moons.end()) ? it->get() : nullptr;
}

bool Planet::hasMoon(const std::string& moonName)const {
	return !isMoonNameAvalible(moonName);
}
#include "Moon.h"
#include <string>
#include <iostream>
#include<iomanip>


//constructor
Moon::Moon(const std::string& name, double mass, double radius, double distance)
	: name(name), mass(mass), radius(radius), distance(distance)
{
	// cosnt s
	const double MIN_MASS = 1.612e24; // kg (27% fold tomeg)
	const double MIN_RADIUS = 200.0;  // km
	const double DEFAULT_DISTANCE = 200000.0; // km

	// nev
	if (name.empty()) {
		throw std::invalid_argument("Nem lehet ures a nev!");
	}

	// suly
	if (mass < MIN_MASS) {
		throw std::invalid_argument("Tul kicsi a tomeg! Minimum: " +
			std::to_string(MIN_MASS) + " kg");
	}

	// keringes
	if (radius < MIN_RADIUS) {
		throw std::invalid_argument("Tul kicsi a sugar! Minimum: " +
			std::to_string(MIN_RADIUS) + " km");
	}

	// Validate distance
	if (distance < 0) {
		throw std::invalid_argument("Nincs negativ keringesi tav!");
	}
}

//getter fv.k

const std::string& Moon::getName() const {
	return name;
}

double Moon::getMass() const {
	return mass;
}

double Moon::getRadius() const{
	return radius;
}

double Moon::getDistance() const {
	return distance;
}
//setter fv.k 
void Moon::setName(const std::string& newName) {
	if (newName.empty())
	{
		throw std::invalid_argument(" Nem lehet ures a nev"); //fancy
	}
	name = newName;//ures nev levedese
}

void Moon::setMass(double newMass) {
	const double MIN_MASS = 1.612e24;
	if (newMass <= MIN_MASS) {
		throw std::invalid_argument("A tomeg nem lehet kisebb mint " + std::to_string(MIN_MASS) + " kg");
	}
	mass = newMass;//tomeg lekezelese
}

void Moon::setRadius(double newRadius) {
	if (newRadius < 200) {
		throw std::invalid_argument("Nem lehet kissebb  mint 200km sugara a bolygonak!)";
	}
	radius = newRadius;// sugar lekezelese
}

void Moon::setDistance(double newDist) {
	if (newDist <= 0) {
		throw std::invalid_argument("Nem lehet < 0 tavolsaga a holdnak!");
	}
	distance = newDist;// keringesi tav lekezelese
}

//Adatkiiras 
void Moon::printData() const {
	std::cout << std::left
		<< std::setw(15) << "Moon Name:" << name << "\n"
		<< std::setw(15) << "Mass:" << mass << " kg\n"
		<< std::setw(15) << "Radius:" << radius << " km\n"
		<< std::setw(15) << "Distance:" << distance << " km\n";

}// kiiras fancy modon 

//Osszehasonlitas operatorok
bool Moon :: operator==(const Moon& other) const {
	return name == other.name &&
		mass == other.mass &&
		radius == other.radius &&
		distance == other.distance;
}

bool Moon :: operator!=(const Moon& other) const {
	return !(*this == other);
}
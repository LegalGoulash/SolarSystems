#include "Moon.h"
#include <string>
#include <iostream>
#include<iomanip>


//constructor
Moon::Moon(const std::string& name, double mass, double radius, double distance)
	:name(name), mass(mass), radius(radius), distance(distance)
{
	if (mass < 1.612e+24) { std::cout << "Tul kicsi a tomeg: foldtomeg 27 % ertekre beallitas!\n"; this->mass = 1.612e+24; }
	else
	{
		this->mass = mass;
	}// tomeg hibakezelese olcso modon

	if (radius < 199.999) { std::cout << "Tul kicsi a sugar, alapertekre allitas!\n"; this->radius = 200; }
	else
	{
		this->radius = radius;
	}// sugar kezelese olcso modon

	if (distance < 0) { std::cout << "Tul kicsi a keringesi tavolsag 0km alapertekre allitas 200.000 km "; this->distance = 200000; }
	else
	{
		this->distance = distance;
	}// keringesi tavolsag hibakezelese olcso modon

}

//getter fv.k

std::string Moon::getName() const {
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
		std::cerr << " Nem lehet ures a nev"; //codebro mondta hogy meno
		return;
	}
	name = newName;//ures nev levedese
}

void Moon::setMass(double newMass) {
	if (newMass <= 0) {
		std::cerr << "Nem lehet < 0 sully!";
	}
	mass = newMass;//tomeg lekezelese
}

void Moon::setRadius(double newRadius) {
	if (newRadius <= 0) {
		std::cerr << "Nem lehet < 0 sugara a bolygonak!";
	}
	radius = newRadius;// sugar lekezelese
}

void Moon::setDistance(double newDist) {
	if (newDist <= 0) {
		std::cerr << "Nem lehet < 0 tavolsaga a holdnak!";
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
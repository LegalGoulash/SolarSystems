#include "Sun.h"
#include"Planet.h"
#include "Moon.h"//unique ptr miatt kell mind a 2
#include<string>
#include<vector>
#include<memory>
#include<iostream>
#include<algorithm>

//konstruktor
Sun::Sun(const std::string& name, double mass, double radius, double temperature)
	:name(name), mass(mass),radius(radius), temperature(temperature){}

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
	name = newName;
}

void Sun::setMass(double newMass)
{
	mass = newMass;
}

void Sun::setRadius(double newRadius)
{
	radius = newRadius;
}

void Sun::setTemperature(double newTemp)
{
	temperature = newTemp;
}
// bojgoval mokolas
void Sun::addPlanet(std::unique_ptr<Planet> planet)
{

}

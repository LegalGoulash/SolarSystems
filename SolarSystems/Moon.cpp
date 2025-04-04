#include "Moon.h"
#include <string>
#include <iostream>
#include<iomanip>
#include<stdexcept>

//constructor
Moon::Moon(const std::string& name, double mass, double radius, double distance)
	:name(name), mass(mass), radius(radius), distance(distance)
{
	if (mass <= 0) throw std::invalid_argument("Legyen pozitiv sullya");
}
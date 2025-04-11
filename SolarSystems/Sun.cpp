#include "Sun.h"
#include"Planet.h"
#include "Moon.h"//unique ptr miatt kell mind a 2
#include<string>
#include<vector>
#include<memory>
#include<iostream>
#include<algorithm>

Sun::Sun(const std::string& solarSystemName, const std::string& name, double mass, double radius, double luminosity)
	:solarSystemName_(solarSystemName), name(name), mass(mass), radius(radius), luminisity(luminosity) {
	if (name.empty())
	{
		throw std::invalid_argument("Nem lehet ures a nev!");
	}//nev hiba kezeles
}

const std::vector<std::unique_ptr<Planet>>& Sun::getPlanets() const
{
	// TODO: insert return statement here
}

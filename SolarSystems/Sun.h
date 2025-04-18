#ifndef SUN_H
#define SUN_H

#include<string>
#include<vector>
#include<memory>
#include<iostream>
#include<iomanip>
#include <algorithm>
#include "Planet.h"
#include "Moon.h"
//alosztalyok berangatasa


class Sun
{
private:
	// oda kell 
	std::string name;
	double mass; //kg ban
	double radius; //km ben 
	double temperature; // Kelvin ben
	std::vector<std::unique_ptr<Planet>> planets;
	// planet vektor


public:
	//konst ok 
	static constexpr double MIN_MASS = 1.9884e30; //kg
	static constexpr double MIN_RADIUS = 695700.0; //km
	static constexpr double MIN_TEMP = 4100.0; // kelvin
	//konstruktorok
	Sun(const std::string& name="Ismeretlen Csillag", double mass = 1.988416e30, double radius= 695700.0, double temperature = 4100.0);



	//getter fv.k
	const std::string& getName() const;
	double getMass() const;
	double getRadius() const;
	double getTemperature() const;
	const std::vector<std::unique_ptr<Planet>>& getPlanets() const; //vektorral ter vissza 

	//setterek

	void setName(const std::string& newName);
	void setMass(double newMass);
	void setRadius(double newRadius);
	void setTemperature(double newTemp);

	//bolygokkal mokolas 

	void addPlanet(std::unique_ptr<Planet> planet);
	void addPlanet(const std::string& name, double mass, double distance, double radius);
	bool removePlanet(const std::string& name);

	Planet* findPlanet(const std::string& name) const;

	bool hasPlanet(const std::string& name) const; //fv arra hogy van e ilyen 

	size_t planetCount() const; // egyszeruen hany bolygoja van 

	//adatkiiras

	void printData()const;
	void printPlanets() const; // bolygok kiirasa csak 

	//osszhasonlitasok operatorral es kiiras
	bool operator==(const Sun& other) const;
	bool operator!=(const Sun& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Sun& sun);

	
	//mivel van unique ptr kell a HAMMER
	~Sun() = default;
	Sun(const Sun&) = delete;
	Sun& operator=(const Sun&) = delete;
	Sun(Sun&&) = default;
	Sun& operator=(Sun&&) = default;

	//seged fv k 
	static bool caseInsensitiveCompare(const std::string& a, const std::string& b);
	static bool isValidNameChar(char c);
	void validatePlanetName(const std::string& name) const;
	void validatePlanetParameters(double mass, double distance, double radius) const;
};

#endif // !SUN_H
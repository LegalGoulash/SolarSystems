#ifndef SUN_H
#define SUN_H

#include<string>
#include<vector>
#include<memory>
#include<iostream>
#include<iomanip>
#include <algorithm>

//alosztalyok berangatasa
class Moon;
class Planet;

class Sun
{
private:
	// oda kell figyelni 
	std::string name;
	double mass; //kg ban
	double radius; //km ben 
	double temperature; // Kelvin ben
	std::vector<std::unique_ptr<Planet>> planets;
	// planet vektor


public:
	//konstruktorok
	Sun(const std::string& name="Ismeretlen Csillag", double mass = 1.989e30, double radius=696540.0, double temperature = 5780.0);



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

	Planet* findPlanet(const std::string& name) const;

	bool hasPlanet(const std::string& name) const; //fv arra hogy van e ilyen bolygolylyja
	bool isPlanetNameOk(const std::string& name) const;//fv arra hogy mar letezik e ilyen nevu bolygo ebben a redszerben

	bool removePlanet(const std::string& name);

	size_t planetCount()const; // egyszerune hany bolygoja van 

	//adatkiiras

	void printData()const;
	void printPlanets() const; // bolygok kiirasa csak 

	//osszhasonlitasok operatorral
	bool operator==(const Sun& other) const;
	bool operator!=(const Sun& other) const;
	
	//mivel van unique ptr kell a HAMMER
	~Sun() = default;
	Sun(const Sun&) = delete;
	Sun& operator=(const Sun&) = delete;
	Sun(Sun&&) = default;
	Sun& operator=(Sun&&) = default;

	// kiiro OP fuzhetoen xd elegge tulterheles
	friend std::ostream& operator<<(std::ostream& os, const Sun& sun);

};

#endif // !SUN_H
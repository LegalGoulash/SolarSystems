#ifndef SUN_H
#define SUN_H

#include<string>
#include<vector>
#include<memory>
#include<iostream>

//alosztalyok berangatasa
class Moon;
class Planet;

class Sun
{
private:
	std::string solarSystemName_; // oda kell figyelni 
	std::string name;
	double mass; //kg ban
	double radius; //km ben 
	double luminisity;
	std::vector<std::unique_ptr<Planet>> planets;
	// planet vektor

	//seged fv betolteshez
	void loadFromStream(std::istream& iss);
public:
	//konstruktorok
	Sun(const std::string& solarSystemName, const std::string& name, double mass, double radius, double lumisoty);
	// destruktor nem kell mert 
	// az ala tartozo objektumok onmaguknak lekezelik


	//getter fv.k
	const std::string& getSolarSystemName() const { return solarSystemName_; }
	const std::string& getName() const { return name; }
	double getMass() const { return mass; }
	double getRadius() const { return radius; }
	double getLuminosity() const { return luminisity; }
	const std::vector<std::unique_ptr<Planet>>& getPlanets() const { return planets; } //vektorral ter vissza 

	//setterek

	void setName(const std::string& newName);
	void setMass(double newMass);
	void setRadius(double newRadius);
	void setLuminosity(double newLum);
	//bolygokkal mokolas 

	void addPlanet(std::unique_ptr<Planet>& planet);
	Planet* findPlanet(const std::string& name) const;
	bool removePlanet(const std::string& name);

	//adatkiiras

	void printData()const;

	//osszhasonlitasok operatorral
	bool operator==(const Sun& other) const;
	bool operator!=(const Sun& other) const;

	//Sys loader szuksegessege miatti cucmak 
	static std::unique_ptr<Sun> createFromStream(std::istream& iss);

};

#endif // !SUN_H



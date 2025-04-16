#ifndef PLANET_H
#define PLANET_H

#include<string>
#include<memory>
#include <vector>
#include<iostream>
#include<iomanip>
#include<algorithm>

class Moon; // kivaltja a moon.h t mert moon vektorokat rangatunk ugye 

class Planet
{
private:
	std::string name;
	double mass; //kg ban
	double distance; //millio km ben aa napotol
	double radius; //km ben
	std::vector<std::unique_ptr<Moon>> moons; //holdakat tartalmaazo vektor
public:
	Planet(const std::string& name ="Nevtelen Bolygo", double mass= 1.612e+24, double distance=0.0, double radius= 199.999);
	
	

	//getter fv.k  
	const std::string& getName() const;
	double getMass() const;
	double getRadius() const;
	double getDistance() const;
	const std::vector<std::unique_ptr<Moon>>& getMoons() const {return moons; } // holdak kiirasa (v2 ) 

	//setter fv.k 

	void setName(const std::string& newName);
	void setMass(double newMass);
	void setRadius(double newRadius);
	void setDistance(double newDistance);

	//adat kiiras 
	void printData() const;
	void printMoons() const;

	//osszehasonlito op.
	bool operator==(const Planet& other) const;
	bool operator!=(const Planet& other) const;

	//masolas mozgatas 
	
	~Planet() = default;
	Planet(Planet&&) = default;
	Planet& operator=(Planet&&) = default;
	Planet(const Planet&) = default;
	Planet& operator=(const Planet&) = default;


	//Holdal valo izek
	void addMoon(std::unique_ptr<Moon> moon);
	void addMoon(const std::string& name, double mass, double radius, double distance);
	bool removeMoon(const std::string& moonName);
	Moon* findMoon(const std::string& moonName) const;
	bool hasMoon(const std::string& moonName) const;
	size_t moonCount() const;
	// nem nagyon jo ebben de ez van xddd

	friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
};



#endif // !PLANET_H
#ifndef PLANET_H
#define PLANET_H

#include<string>
#include<memory>
#include <vector>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include "Moon.h"

class Planet
{
private:
	std::string name;
	double mass; //kg ban
	double distance; //millio km ben aa napotol
	double radius; //km ben
	std::vector<std::unique_ptr<Moon>> moons; //holdakat tartalmaazo vektor
public:
	Planet(const std::string& name, double mass, double distance, double radius);
	~Planet() = default;

	//getter fv.k  
	std::string getName() const;
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

	//osszehasonlito op.
	bool operator==(const Planet& other) const;
	bool operator!=(const Planet& other) const;

	//masolas mozgatas 
	
	Planet(const Planet&) = default;
	Planet& operator=(const Planet&) = default;
	Planet(Planet&&) = default;
	Planet& operator= (Planet&&) = default;

	//Holdal valo izek
	void addMoon(std::unique_ptr<Moon> moon); // hold hozzaadasa a vektor hoz PL: file vetoltes

	void addMoon(const std::string& name, double mass, double radius, double distance);

	bool removeMoon(const std::string& moonName);

	Moon* findMoon(const std::string& moonName) const;
	
	bool isMoonNameAvalible(const std::string& name) const;
	//bena vagyok / nem nagyon jo de ez van xddd

	//SYS LOADER cucmok
	bool hasMoon(const std::string& moonName) const;
	size_t mooonCount() const { return moons.size(); }
};


#endif // !PLANET_H
#ifndef PLANET_H
#define PLANET_H

#include<string>
#include<memory>
#include <vector>
#include "Moon.h"

class Panet
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
	Planet& operatro = (Planet&&) = default;
};


#endif // !PLANET_H
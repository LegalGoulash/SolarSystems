#ifndef MOON_H
#define MOON_H
#include <string>
#include<iostream>
#include <iomanip> //szebb kiirashoz (YT tutorial)
class Moon
{
private: 
	std::string name;
	double mass;
	double radius;
	double distance;
public:
	// construktorok
	Moon(const std::string& name, double mass, double radius, double distance);

	//getterek
	std::string getName() const;
	double getMass() const;
	double getRadius() const;
	double getDistance() const;

	//setterek
	void setName(const std::string& newName);
	void setMass(double newMass);
	void setRadius(double newRad);
	void setDistance(double newDist);

	//adatkiiras
	void printData() const;

	//compare operatro tulterheles
	bool operator==(const Moon& other) const;
	bool operator!=(const Moon& other) const;

	//masolas mozgatas
	Moon(const Moon&) = default;
	Moon& operator=(const Moon&) = default;
	Moon(Moon&&) = default;
	Moon& operator = (Moon&&) = default;
};
#endif // !MOON_H

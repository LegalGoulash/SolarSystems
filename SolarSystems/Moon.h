#ifndef MOON_H
#define MOON_H
#include <string>
#include<iostream>
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
};
#endif // MOON_H




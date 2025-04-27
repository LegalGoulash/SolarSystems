#ifndef GALAXY_H
#define GALAXY_H

#include<string>
#include<vector>
#include<memory>
#include<iostream>
#include<iomanip>
#include <algorithm>
#include"Sun.h"

class Galaxy
{
private:
	std::string name;
	std::vector<std::unique_ptr<Sun>> suns;
	//seged fvk part 1

	void validateSunName(const std::string& name) const;
	void validateSunParameters(double mass, double radius, double temp) const;
public:
	Galaxy(const std::string& name );

	//getterek
	const std::string& getName() const;
	const std::vector<std::unique_ptr<Sun>>& getSuns() const;

	//setterek
	void setName(const std::string& newName);

	//napokkal valo bigyok
	void addSun(std::unique_ptr<Sun> sun);
	void addSun(const std::string& name, double mass, double radius, double temperature);
	bool removeSun(const std::string& name);
	Sun* findSun(const std::string& name)const;
	bool hasSun(const std::string& name);
	size_t sunCount() const;

	//kiiri fv-k

	void printData() const;
	void printSuns() const;

	//operatorok

	bool operator==(const Galaxy& other) const;
	bool operator!=(const Galaxy& other) const;
	//baraaatok

	friend std::ostream& operator<< (std::ostream& os, const Galaxy& galaxy);

	//Mozgatas megelozese

	~Galaxy() = default;
	Galaxy(const Galaxy&) = delete;
	Galaxy& operator=(const Galaxy&) = delete;
	Galaxy(Galaxy&&) = default;
	Galaxy& operator=(Galaxy&&) = default;
	//segedek

	static bool caseInsensitiveCompare(const std::string& a, const std::string& b);
	static bool isValidGalaxyNameChar(char c);
};


#endif // !GALAXY_H
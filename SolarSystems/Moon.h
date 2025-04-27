#ifndef MOON_H
#define MOON_H

#include <string>
#include <iostream>
#include <iomanip>

class Moon {
private:
    std::string name;
    double mass;
    double radius;
    double distance;

public:
    static constexpr double MIN_MASS = 1.612e24;  // kg
    static constexpr double MIN_RADIUS = 200.0;   // km

    Moon(const std::string& name, double mass, double radius, double distance);

    // Getterek
    const std::string& getName() const;
    double getMass() const;
    double getRadius() const;
    double getDistance() const;

    // Setterek
    void setName(const std::string& newName);
    void setMass(double newMass);
    void setRadius(double newRad);
    void setDistance(double newDist);

    // Kiírás
    void printData() const;
    friend std::ostream& operator<<(std::ostream& os, const Moon& moon);

    // Operátorok
    bool operator==(const Moon& other) const;
    bool operator!=(const Moon& other) const;

    // Másolás/mozgatás
    Moon(const Moon&) = default;
    Moon& operator=(const Moon&) = default;
    Moon(Moon&&) = default;
    Moon& operator=(Moon&&) = default;
};

#endif // MOON_H
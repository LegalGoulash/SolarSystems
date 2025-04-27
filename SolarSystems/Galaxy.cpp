#include "Galaxy.h"
#include "Sun.h"
#include <algorithm>
#include <cctype>


//seged fvk 
bool Galaxy::caseInsensitiveCompare(const std::string& a, const std::string& b) {
	return a.size() == b.size() &&
		std::equal(a.begin(), a.end(), b.begin(),
			[](char x, char y) { return std::tolower(x) == std::tolower(y); });
}

bool Galaxy::isValidGalaxyNameChar(char c) {
	return std::isalnum(static_cast<unsigned char>(c)) ||
		c == ' ' || c == '-' || c == '_' || c == '.';
}
// checker kiszervezese
void Galaxy::validateSunName(const std::string& name) const {
	if (name.empty()) throw std::invalid_argument("Nev nem lehet ures");

	for (char c : name) {
		if (!isValidGalaxyNameChar(c)) {
			throw std::invalid_argument("Ervenytelen karakter: " + std::string(1, c));
		}
	}

	if (std::any_of(suns.begin(), suns.end(),
		[&name](const auto& sun) { return caseInsensitiveCompare(sun->getName(), name); })) {
		throw std::invalid_argument("Mar letezo nap: " + name);
	}
}

void Galaxy::validateSunParameters(double mass, double radius, double temp) const {
	if (mass <= Sun::MIN_MASS) throw std::invalid_argument("Tomeg tul kicsi");
	if (radius <= Sun::MIN_RADIUS) throw std::invalid_argument("Sugar tul kicsi");
	if (temp <= Sun::MIN_TEMP) throw std::invalid_argument("Homerseklet tul alacsony");
}
//konstruktor


Galaxy::Galaxy(const std::string& name) : name(name.empty() ? "Ismeretlen Galaxis" : name) {
	for (char c : this->name) {
		if (!isValidGalaxyNameChar(c)) {
			throw std::invalid_argument("Ervenytelen karakter a galaxis neveben: " + std::string(1, c));
		}
	}
}
//getterek
const std::string& Galaxy::getName() const
{
	return name;
}

const std::vector<std::unique_ptr<Sun>>& Galaxy::getSuns() const
{
	return suns;
}

void Galaxy::setName(const std::string& newName)
{
	if (newName.empty()) {
		std::cout << "A galaxis neve ures, a neve :Ismeretlen Galaxis lesz!";
	}

	for (char c : newName) {
		if (!isValidGalaxyNameChar(c)) {
			throw std::invalid_argument("Ervenytelen karakter a galaxis neveben: " + std::string(1, c));
		}
	}
	name = newName;
}

void Galaxy::addSun(std::unique_ptr<Sun> sun) {
	if (!sun) throw std::invalid_argument("Null pointer");

	validateSunName(sun->getName());
	validateSunParameters(sun->getMass(), sun->getRadius(), sun->getTemperature());

	suns.push_back(std::move(sun));
}

void Galaxy::addSun(const std::string& name, double mass, double radius, double temperature) {
	validateSunName(name);
	validateSunParameters(mass, radius, temperature);

	suns.push_back(std::make_unique<Sun>(name, mass, radius, temperature));
}

bool Galaxy::removeSun(const std::string& name) {
	auto it = std::remove_if(suns.begin(), suns.end(),
		[&name](const auto& sun) {
			return caseInsensitiveCompare(sun->getName(), name);
		});

	if (it != suns.end()) {
		suns.erase(it, suns.end());
		return true;
	}
	return false;
}

Sun* Galaxy::findSun(const std::string& name) const {
    auto it = std::find_if(suns.begin(), suns.end(),
        [&name](const auto& sun) {
            return caseInsensitiveCompare(sun->getName(), name);
        });
    return (it != suns.end()) ? it->get() : nullptr;
}

bool Galaxy::hasSun(const std::string& name)
{
	return findSun(name) != nullptr;
}

size_t Galaxy::sunCount() const
{
	return suns.size();
}

//kiiras
void Galaxy::printData() const
{
	std::cout << std::left
		<< std::setw(15) << "Sun Name: " << name << "\n";
}

void Galaxy::printSuns() const
{
	std::cout << "Suns of " << name << " Galaxy\n";
	for (const auto& sun : suns) {
		sun->printData();
		std::cout << "--------------------\n";
	}
}

//operatorok

bool Galaxy::operator==(const Galaxy& other) const
{
	return name == other.name;
}

bool Galaxy::operator!=(const Galaxy& other) const
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Galaxy& galaxy)
{
	os << galaxy.name << " (Systems: ";
	//vegre kesz
	const auto& suns = galaxy.getSuns();
	bool first = true;
	for (const auto& sun : suns) {
		if (!first) {
			os << ", ";
		}
		os << sun->getName() << " system";
		first = false;
	}

	os << ")";
	return os;
}

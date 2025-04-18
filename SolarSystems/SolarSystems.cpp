#include "Galaxy.h"
#include "SolarSystemLoader.h"
#include <iostream>
#include <limits>
#include <memory>

using namespace std;

void displayMainMenu();
void handleGalaxyMenu(Galaxy& galaxy);
void handleSunMenu(Sun& sun);
void handlePlanetMenu(Planet& planet);
void displayGalaxy(const Galaxy& galaxy);

int main() {
    unique_ptr<Galaxy> galaxy;
    int choice;

    do {
        displayMainMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
            case 1: { // Uj galaxis letrehozasa
                string name;
                cout << "Adja meg a galaxis nevet: ";
                getline(cin, name);
                galaxy = make_unique<Galaxy>(name);
                cout << "Galaxis sikeresen letrehozva!\n";
                break;
            }
            case 2: { // Galaxis betoltese fajlbol
                string sunFile, planetFile, moonFile;
                cout << "Napok fajlneve: ";
                getline(cin, sunFile);
                cout << "Bolygok fajlneve: ";
                getline(cin, planetFile);
                cout << "Holdak fajlneve: ";
                getline(cin, moonFile);

                galaxy = SolarSystemLoader::loadGalaxy(sunFile, planetFile, moonFile);
                cout << "Galaxis sikeresen betoltve!\n";
                break;
            }
            case 3: { // Galaxis mentese fajlba
                if (!galaxy) {
                    cout << "Nincs betoltott galaxis!\n";
                    break;
                }
                string sunFile, planetFile, moonFile;
                cout << "Napok fajlneve: ";
                getline(cin, sunFile);
                cout << "Bolygok fajlneve: ";
                getline(cin, planetFile);
                cout << "Holdak fajlneve: ";
                getline(cin, moonFile);

                if (SolarSystemLoader::SaveGalaxy(*galaxy, sunFile, planetFile, moonFile)) {
                    cout << "Galaxis sikeresen elmentve!\n";
                }
                else {
                    cout << "Hiba tortent a mentes soran!\n";
                }
                break;
            }
            case 4: { // Galaxis kezelese
                if (!galaxy) {
                    cout << "Nincs betoltott galaxis!\n";
                    break;
                }
                handleGalaxyMenu(*galaxy);
                break;
            }
            case 5: { // Galaxis megjelenitese
                if (!galaxy) {
                    cout << "Nincs betoltott galaxis!\n";
                    break;
                }
                displayGalaxy(*galaxy);
                break;
            }
            case 0: // exit
                cout << "Kilepes...\n";
                break;
            default:
                cout << "Ervenytelen valasztas!\n";
            }
        }
        catch (const exception& e) {
            cout << "Hiba tortent: " << e.what() << "\n";
        }

    } while (choice != 0);

    return 0;
}

void displayMainMenu() {
    cout << "\n=== Fomenu ===\n";
    cout << "1. Uj galaxis letrehozasa\n";
    cout << "2. Galaxis betoltese fajlbol\n";
    cout << "3. Galaxis mentese fajlba\n";
    cout << "4. Galaxis kezelese\n";
    cout << "5. Galaxis megjelenitese\n";
    cout << "0. Kilepes\n";
    cout << "Valasztas: ";
}

void handleGalaxyMenu(Galaxy& galaxy) {
    int choice;

    do {
        cout << "\n=== Galaxis Kezeles ===\n";
        cout << "1. Galaxis nevenek modositasa\n";
        cout << "2. Nap hozzaadasa\n";
        cout << "3. Nap eltavolitasa\n";
        cout << "4. Nap kezelese\n";
        cout << "5. Napok listazasa\n";
        cout << "0. Vissza a fomenube\n";
        cout << "Valasztas: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
            case 1: { // nev modositasa
                string newName;
                cout << "Uj galaxisnev: ";
                getline(cin, newName);
                galaxy.setName(newName);
                cout << "Nev sikeresen modositva!\n";
                break;
            }
            case 2: { // Nap add
                string name;
                double mass, radius, temp;

                cout << "Nap neve: ";
                getline(cin, name);
                cout << "Tomeg (kg): ";
                cin >> mass;
                cout << "Sugar (km): ";
                cin >> radius;
                cout << "Homerseklet (K): ";
                cin >> temp;
                cin.ignore();

                galaxy.addSun(name, mass, radius, temp);
                cout << "Nap sikeresen hozzaadva!\n";
                break;
            }
            case 3: { // Nap remove
                string name;
                cout << "Nap neve: ";
                getline(cin, name);

                if (galaxy.removeSun(name)) {
                    cout << "Nap sikeresen eltavolitva!\n";
                }
                else {
                    cout << "Nem talalhato ilyen nevu nap!\n";
                }
                break;
            }
            case 4: { // Nap kezelese
                string name;
                cout << "Nap neve: ";
                getline(cin, name);

                Sun* sun = galaxy.findSun(name);
                if (sun) {
                    handleSunMenu(*sun);
                }
                else {
                    cout << "Nem talalhato ilyen nevu nap!\n";
                }
                break;
            }
            case 5: // Napok listazasa
                galaxy.printSuns();
                break;
            case 0: // Vissza
                break;
            default:
                cout << "Ervenytelen valasztas!\n";
            }
        }
        catch (const exception& e) {
            cout << "Hiba tortent: " << e.what() << "\n";
        }
    } while (choice != 0);
}

void handleSunMenu(Sun& sun) {
    int choice;

    do {
        cout << "\n=== Nap Kezeles: " << sun.getName() << " ===\n";
        cout << "1. Nap adatainak modositasa\n";
        cout << "2. Bolygo hozzaadasa\n";
        cout << "3. Bolygo eltavolitasa\n";
        cout << "4. Bolygo kezelese\n";
        cout << "5. Bolygok listazasa\n";
        cout << "0. Vissza\n";
        cout << "Valasztas: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
            case 1: { // Nap adatainak modositasa
                string name;
                double mass, radius, temp;

                cout << "Uj napnev (jelenlegi: " << sun.getName() << "): ";
                getline(cin, name);
                cout << "Uj tomeg (kg) (jelenlegi: " << sun.getMass() << "): ";
                cin >> mass;
                cout << "Uj sugar (km) (jelenlegi: " << sun.getRadius() << "): ";
                cin >> radius;
                cout << "Uj homerseklet (K) (jelenlegi: " << sun.getTemperature() << "): ";
                cin >> temp;
                cin.ignore();

                sun.setName(name);
                sun.setMass(mass);
                sun.setRadius(radius);
                sun.setTemperature(temp);
                cout << "Nap adatai sikeresen modositva!\n";
                break;
            }
            case 2: { // Bolygo hozzaadasa
                string name;
                double mass, distance, radius;

                cout << "Bolygo neve: ";
                getline(cin, name);
                cout << "Tomeg (kg): ";
                cin >> mass;
                cout << "Tavolsag (millio km): ";
                cin >> distance;
                cout << "Sugar (km): ";
                cin >> radius;
                cin.ignore();

                sun.addPlanet(name, mass, distance, radius);
                cout << "Bolygo sikeresen hozzaadva!\n";
                break;
            }
            case 3: { // Bolygo eltavolitasa
                string name;
                cout << "Bolygo neve: ";
                getline(cin, name);

                if (sun.removePlanet(name)) {
                    cout << "Bolygo sikeresen eltavolitva!\n";
                }
                else {
                    cout << "Nem talalhato ilyen nevu bolygo!\n";
                }
                break;
            }
            case 4: { // Bolygo kezelese
                string name;
                cout << "Bolygo neve: ";
                getline(cin, name);

                Planet* planet = sun.findPlanet(name);
                if (planet) {
                    handlePlanetMenu(*planet);
                }
                else {
                    cout << "Nem talalhato ilyen nevu bolygo!\n";
                }
                break;
            }
            case 5: // Bolygok listazasa
                sun.printPlanets();
                break;
            case 0: // Vissza
                break;
            default:
                cout << "Ervenytelen valasztas!\n";
            }
        }
        catch (const exception& e) {
            cout << "Hiba tortent: " << e.what() << "\n";
        }
    } while (choice != 0);
}

void handlePlanetMenu(Planet& planet) {
    int choice;

    do {
        cout << "\n=== Bolygo Kezeles: " << planet.getName() << " ===\n";
        cout << "1. Bolygo adatainak modositasa\n";
        cout << "2. Hold hozzaadasa\n";
        cout << "3. Hold eltavolitasa\n";
        cout << "4. Holdak listazasa\n";
        cout << "0. Vissza\n";
        cout << "Valasztas: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
            case 1: { // Bolygo adatainak modositasa
                string name;
                double mass, distance, radius;

                cout << "Uj bolygonev (jelenlegi: " << planet.getName() << "): ";
                getline(cin, name);
                cout << "Uj tomeg (kg) (jelenlegi: " << planet.getMass() << "): ";
                cin >> mass;
                cout << "Uj tavolsag (millio km) (jelenlegi: " << planet.getDistance() << "): ";
                cin >> distance;
                cout << "Uj sugar (km) (jelenlegi: " << planet.getRadius() << "): ";
                cin >> radius;
                cin.ignore();

                planet.setName(name);
                planet.setMass(mass);
                planet.setDistance(distance);
                planet.setRadius(radius);
                cout << "Bolygo adatai sikeresen modositva!\n";
                break;
            }
            case 2: { // Hold hozzaadasa
                string name;
                double mass, distance, radius;

                cout << "Hold neve: ";
                getline(cin, name);
                cout << "Tomeg (kg): ";
                cin >> mass;
                cout << "Tavolsag (km): ";
                cin >> distance;
                cout << "Sugar (km): ";
                cin >> radius;
                cin.ignore();

                planet.addMoon(name, mass, radius, distance);
                cout << "Hold sikeresen hozzaadva!\n";
                break;
            }
            case 3: { // Hold eltavolitasa
                string name;
                cout << "Hold neve: ";
                getline(cin, name);

                if (planet.removeMoon(name)) {
                    cout << "Hold sikeresen eltavolitva!\n";
                }
                else {
                    cout << "Nem talalhato ilyen nevu hold!\n";
                }
                break;
            }
            case 4: // Holdak listazasa
                planet.printMoons();
                break;
            case 0: // Vissza
                break;
            default:
                cout << "Ervenytelen valasztas!\n";
            }
        }
        catch (const exception& e) {
            cout << "Hiba: " << e.what() << "\n";
        }
    } while (choice != 0);
}

void displayGalaxy(const Galaxy& galaxy) {
    cout << "\n=== Galaxis: " << galaxy.getName() << " ===\n";
    cout << "Napok szama: " << galaxy.sunCount() << "\n\n";

    for (const auto& sun : galaxy.getSuns()) {
        cout << "Nap: " << sun->getName() << "\n";
        cout << "  Bolygok szama: " << sun->planetCount() << "\n";

        for (const auto& planet : sun->getPlanets()) {
            cout << "  Bolygo: " << planet->getName() << "\n";
            cout << "    Holdak szama: " << planet->moonCount() << "\n";
        }
        cout << "\n";
    }
}
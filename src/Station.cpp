//
// Created by luis on 18-03-2023.
//

#include "Station.h"

Station::Station() {
    this->name = "";
    this->district = "";
    this->municipality = "";
    this->township = "";
    this->line = "";
}

Station::Station(
        const std::string &name,
        const std::string &district,
        const std::string &municipality,
        const std::string &township,
        const std::string &line
) {
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

std::string Station::getName() const {
    return this->name;
}

std::string Station::getDistrict() const {
    return this->district;
}

std::string Station::getMunicipality() const {
    return this->municipality;
}

std::string Station::getTownship() const {
    return this->township;
}

std::string Station::getLine() const {
    return this->line;
}

bool Station::operator==(const Station &station) const {
    return this->name == station.name;
}

#include <sstream>
#include <iostream>
#include "airport.h"

//pass a line in the airport.dat
//parse with delimiter ",", store each attribute of the data
//to the current airport
Airport::Airport(string info) {
    // delimiter ","
    istringstream iss(info);
    // string to double or int
    stringstream ss;
    string buffer;

    // delimite in order
    getline(iss, buffer, ',');
    ss << buffer;
    ss >> airportId;
    ss.clear();
    
    getline(iss, buffer, ',');
    if (buffer.empty()) {
        name = "";
    }
    else {
        // remove quote """
        name = buffer.substr(1, buffer.length() - 2);
    }
    
    getline(iss, buffer, ',');
    if (buffer.empty()) {
        city = "";
    }
    else {
        city = buffer.substr(1, buffer.length() - 2);
    }
    
    getline(iss, buffer, ',');
    if (buffer.empty()) {
        country = "";
    }
    else {
        country = buffer.substr(1, buffer.length() - 2);
    }
    
    getline(iss, buffer, ',');
    if (buffer.empty()) {
        iata = "";
    }
    else {
        iata = buffer.substr(1, buffer.length() - 2);
    }
    
    getline(iss, buffer, ',');
    if (buffer.empty()) {
        icao = "";
    }
    else {
        icao = buffer.substr(1, buffer.length() - 2);
    }
    
    getline(iss, buffer, ',');
    ss << buffer;
    ss >> latitude;
    ss.clear();
    
    getline(iss, buffer, ',');
    ss << buffer;
    ss >> longitude;
    ss.clear();
    
    getline(iss, buffer, ',');
    ss << buffer;
    ss >> altitude;
    ss.clear();
    
    getline(iss, buffer, ',');
    ss << buffer;
    ss >> timezone;
    ss.clear();

    getline(iss, buffer, ',');
    if (buffer.empty()) {
        dst = "";
    }
    else {
        dst = buffer.substr(1, buffer.length() - 2);
    }
        
    getline(iss, buffer, ',');
    if (buffer.empty()) {
        type = "";
    }
    else {
        type = buffer.substr(1, buffer.length() - 2);
    }
    
    getline(iss, buffer, ',');
    if (buffer.empty()) {
        source = "";
    }
    else {
        source = buffer.substr(1, buffer.length() - 2);
    }
}

int Airport::getAirportId() {
    return airportId;
}

string Airport::getName() {
    return name;
}

string Airport::getCity() {
    return city;
}

string Airport::getCountry() {
    return country;
}

string Airport::getIata() {
    return iata;
}

string Airport::getIcao() {
    return icao;
}

double Airport::getLatitude() {
    return latitude;
}

double Airport::getLongitude() {
    return longitude;
}

int Airport::getAltitude() {
    return altitude;
}

double Airport::getTimezone() {
    return timezone;
}

string Airport::getDst() {
    return dst;
}

string Airport::getDatabaseTimeZone() {
    return databaseTimeZone;
}

string Airport::getType() {
    return type;
}

string Airport::getSource() {
    return source;
}

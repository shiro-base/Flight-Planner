
#pragma once
#include <string>
#include <iostream>
using namespace std;

class Airport {
    
public:
    Airport(string info);

    int getAirportId();
    string getName();
    string getCity();
    string getCountry();
    string getIata();
    string getIcao();
    double getLatitude();
    double getLongitude();
    int getAltitude();
    double getTimezone();
    string getDst();
    string getDatabaseTimeZone();
    string getType();
    string getSource();
    
private:
    int airportId;
    string name;
    string city;
    string country;
    string iata;
    string icao;
    double latitude;
    double longitude;
    int altitude;
    double timezone;
    string dst;
    string databaseTimeZone;
    string type;
    string source;
};



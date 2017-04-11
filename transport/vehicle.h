
#pragma once

#include <global.h>
#include <vector>

class IWay;

struct TRANSPORT_API Info
{
	Info();
	Info operator+( const Info& );

	double time;     // in seconds
	double distance; // in meters
	double fuel;     // in kg
};

class TRANSPORT_API Vehicle
{
public:
	enum MODE { ACCEL=0, CRUISE, LAND, _END };

	Info info( MODE theMode, double theDistance ) const;
	Info complete( double theDistanceKM ) const;
	Info complete( const IWay& ) const;

	double mass() const;
	double cost( double theDistanceKM,
							 double theTimeH,
							 double theCapacity ) const;
	double cost( const IWay& theWay, double theCapacity ) const;

public:
	double              MA; //mass in kg
	std::vector<double> A;  //acceleration, m/s2
	std::vector<double> FC; //fuel consumption (part of nominal), dimless
	double              GT; //hour fuel consumption in nominal,   kg/h
	double              CV; //cruise velocity                     km/h
	int                 NP; //number of passengers
	std::vector<Entity> EQ; //equipage;
};

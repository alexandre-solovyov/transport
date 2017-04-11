
#pragma once

#include <decl.h>
#include <vector>

struct TRANSPORT_API Info
{
	Info();
	Info operator+( const Info& );

	double time;
	double distance;
	double fuel;
};

class TRANSPORT_API Vehicle
{
public:
	enum MODE { ACCEL=0, CRUISE, LAND, _END };

	Info info( MODE theMode, double theDistance ) const;
	Info complete( double theDistanceKM ) const;

public:
	std::vector<double> A;  //acceleration, m/s2
	std::vector<double> FC; //fuel consumption (part of nominal), dimless
	double              GT; //hour fuel consumption in nominal,   kg/h
	double              CV; //cruise velocity                     km/h
};

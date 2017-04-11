
#pragma once

#include <global.h>
#include <vector>
#include <idynamic.h>

class IWay;

struct TRANSPORT_API Info
{
	Info();
	Info operator+( const Info& );

	double time;     // in seconds
	double distance; // in meters
	double fuel;     // in kg
};

class TRANSPORT_API VehicleInfo
{
public:
	enum MODE { STOP=0, ACCEL, CRUISE, LAND, _END };

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

class TRANSPORT_API Vehicle : public IDynamic
{
public:
	Vehicle( const VehicleInfo& );

	IWay* way() const;
	void setWay( IWay* );

	double position() const;
	double velocity() const;

	void go();
	void print();

	virtual void next( double dt ) override;

private:
	VehicleInfo myInfo;
	VehicleInfo::MODE myMode;
	IWay* myWay;

	double myDistance;
	double myLDistance;
	double myPosition;
	double myVelocity;
};

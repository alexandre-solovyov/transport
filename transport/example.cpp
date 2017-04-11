
#include <vehicle.h>
#include <string>
#include <cities.h>
#include <tools.h>
#include <stdway.h>
#include <windows.h>

int main( int argc, char** argv )
{
	VehicleInfo boeing;

	boeing.MA = 30000;
	boeing.A.resize(4);
	boeing.A[0] = 0;
	boeing.A[1] = 0.75*G;
	boeing.A[2] = 0;
	boeing.A[3] = -0.03*G;
	boeing.FC.resize(4);
	boeing.FC[0] = 0.0;
	boeing.FC[1] = 11.0;
	boeing.FC[2] = 1.0;
	boeing.FC[3] = 0.25;
	boeing.GT = 2600;
	boeing.CV = 915;
	boeing.NP = 200;
	boeing.EQ.push_back( H_AIR_COM );
	boeing.EQ.push_back( H_AIR_PIL );
	boeing.EQ.push_back( H_AIR_STE );
	boeing.EQ.push_back( H_AIR_STE );
	boeing.EQ.push_back( H_AIR_STE );
	boeing.EQ.push_back( H_AIR_STE );

	std::string DATA_DIR = std::string( getenv( "DATA_DIR" ) ) + "/";
	Cities cc;
  cc.load( DATA_DIR + "cities_test.dat" );
	City nn = cc.find( toW( "Nizhniy Novgorod" ) );
	City p = cc.find( toW( "Paris" ) );
	City m = cc.find( toW( "Moscow" ) );



	/*StdWay w( nn, p );

	int dt = 5;
	Vehicle v( boeing );
	v.setWay( &w );
	v.go();
	int t = 0;
	for( int i=0; i<2400; i++ )
	{
		if( t%30==0 )
		{
			printf( "%i min: ", t/60 );
			v.print();
			Sleep(250);
		}
		v.next( dt );
		t += dt;
	}*/

	StdWay w( nn, m );

	int dt = 6;
	Vehicle v( boeing );
	v.setWay( &w );
	v.go();
	int t = 0;
	for( int i=0; i<350; i++ )
	{
		if( t%6==0 )
		{
			printf( "%i min: ", t/60 );
			v.print();
			//Sleep(250);
		}
		v.next( dt );
		t += dt;
	}

	return 0;
}

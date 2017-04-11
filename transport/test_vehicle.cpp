
#include <gtest/gtest.h>
#include <vehicle.h>
#include <stdway.h>
#include <tools.h>

extern std::string DATA_DIR;

Vehicle boeing;
class VehiclesTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		boeing.MA = 30000;
		boeing.A.resize(3);
		boeing.A[0] = 0.75*G;
		boeing.A[1] = 0;
		boeing.A[2] = -0.03*G;
		boeing.FC.resize(3);
		boeing.FC[0] = 11.0;
		boeing.FC[1] = 1.0;
		boeing.FC[2] = 0.25;
		boeing.GT = 2600;
		boeing.CV = 915;
		boeing.NP = 200;
		boeing.EQ.push_back( H_AIR_COM );
		boeing.EQ.push_back( H_AIR_PIL );
		boeing.EQ.push_back( H_AIR_STE );
		boeing.EQ.push_back( H_AIR_STE );
		boeing.EQ.push_back( H_AIR_STE );
		boeing.EQ.push_back( H_AIR_STE );
	}
	virtual void TearDown() {}
};


TEST_F( VehiclesTest, info_is_ok )
{
	Info i = boeing.complete( 2884 );
	EXPECT_NEAR( 2884, i.distance/1000, 1E-3 ); //km
	EXPECT_NEAR( 3.276, i.time/3600, 1E-3 );    //hours
	EXPECT_NEAR( 8.301, i.fuel/1000, 1E-3 );    //tons

	EXPECT_NEAR( 2412.0, boeing.cost( 2884, 3.276, 0.75 ), 1E0 );
}

TEST_F( VehiclesTest, way_is_ok )
{
	Cities cc;
  ASSERT_TRUE( cc.load( DATA_DIR + "cities_test.dat" ) );

	City m = cc.find( toW( "Moscow" ) );
	City nn = cc.find( toW( "Nizhniy Novgorod" ) );
	City p = cc.find( toW( "Paris" ) );

	StdWay w( nn, p );
	Info i = boeing.complete( w );
	EXPECT_NEAR( 2884, w.distance(), 1E0 );
	EXPECT_NEAR( 2884, i.distance/1000, 1E0 );
	EXPECT_NEAR( 3.277, i.time/3600, 1E-3 );
	EXPECT_NEAR( 8.303, i.fuel/1000, 1E-3 );
	EXPECT_NEAR( 3813, boeing.cost( w, 0.50 ), 1E0 );
	EXPECT_NEAR( 2542, boeing.cost( w, 0.75 ), 1E0 );
	EXPECT_NEAR( 2118, boeing.cost( w, 0.90 ), 1E0 );
}
